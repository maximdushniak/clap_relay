// TEST

#define NOISE_PIN 5     // пин датчика уровня шума
#define RELAY_PIN 4     // пин рэле
#define difficulty 100  // миллисекунд на реакцию (плюс минус)
#define max_knock 5    // число запоминаемых "стуков"

// включенное состояние системы (1 - вкл., 0 - выкл.)
bool state_on = false; // система выключена
bool write_start = false; // флаг начала записи
unsigned last_knock = 0; // время последнего хлопка
unsigned knock_time;

int wait_time[max_knock];

void setup() {
  
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(NOISE_PIN, INPUT);

}


void loop() {
  
  bool is_clap = !digitalRead(NOISE_PIN);

  
  if(is_clap && !state_on) {

    state_on = true;
    digitalWrite(RELAY_PIN, HIGH);
    delay(500);
    
    Serial.println("ON!");
        
    } else if (state_on && is_clap){


    state_on = false;
    digitalWrite(RELAY_PIN, LOW);
    delay(500);
    
    Serial.println("OFF!");
      
    }
  
}


void knockWrite() { // запись хлопков
  last_knock = millis();

  bool is_clap = !digitalRead(NOISE_PIN);
  while (1)
  {
    if (millis() - last_knock > 5000)
    {
      write_start = false;
      break;
    }
    
    if (is_clap) {

      write_start = true;
      last_knock = millis();
      break;

    }
  }
  
  if (write_start)
  {
    while (1)
    {
      is_clap = !digitalRead(NOISE_PIN);
      if (is_clap)
      {
        knock_time = millis() - last_knock;
        
      }
      
    }
    
  }
  

  
}