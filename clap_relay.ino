#define NOISE_PIN 5     // пин датчика уровня шума
#define RELAY_PIN 4     // пин рэле
#define difficulty 100  // миллисекунд на реакцию (плюс минус)
#define max_knock 5    // число запоминаемых "стуков"

// включенное состояние системы (1 - вкл., 0 - выкл.)
bool state_on = false; // система выключена
bool write_start = false; // флаг начала записи
unsigned last_knock = 0; // время последнего хлопка
// unsigned knock_time;

unsigned wait_time[max_knock], max_wait_time[max_knock], min_wait_time[max_knock];

volatile byte mode; // 0- ; 1- ; 2-.

byte mode_1 = 0;

void setup() {
  
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(NOISE_PIN, INPUT);

  knockWrite();

}


void loop() {
  
  //bool is_clap = !digitalRead(NOISE_PIN);

  if (mode_1 == 0)
  {
    Serial.println("Write array:");
    for (byte i = 0; i < max_knock; i++)
    {
      Serial.println(wait_time[i]);
    }
    mode_1 = 1;
  }
  
  

   /* if(is_clap && !state_on) {

    state_on = true;
    digitalWrite(RELAY_PIN, HIGH);
    delay(500);
    
    Serial.println("ON!");
        
    } else if (state_on && is_clap){


    state_on = false;
    digitalWrite(RELAY_PIN, LOW);
    delay(500);
    
    Serial.println("OFF!");
      
    } */
  
}


void knockWrite() { // запись хлопков

  byte knock = 0; // индекс (номер хлопка)  для записи в массив
  bool is_clap = false;
  unsigned knock_time;

  delay(1000);
  Serial.println("Write start");
    
  
  last_knock = millis();

  while (1)
  {
    if (millis() - last_knock > 5000)
    {
      Serial.println("Timeout!");
      write_start = false;
      break;
    }
    
    is_clap = !digitalRead(NOISE_PIN);

    if (is_clap) {
      Serial.println("Start write!!!");
      write_start = true;
      last_knock = millis();
      break;

    }
  }
  
  if (write_start)
  {
    unsigned start_time = last_knock;
    while (1)
    { 
      delay(50);
      is_clap = !digitalRead(NOISE_PIN);
      if (is_clap)
      {
        knock_time = millis() - last_knock;
        wait_time[knock] = knock_time;
        knock++;
        last_knock = millis();
        is_clap = false;
        Serial.println("knock!");
        is_clap = false;
        if (knock == max_knock || millis()-start_time)
        {
          break;
        }
        /*if (millis() - last_knock > 3000)
        {
          break;
        } */
      }
    // is_clap = !digitalRead(NOISE_PIN);
    }
    
  }
}