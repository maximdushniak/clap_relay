#define NOISE_PIN 5   // пин датчика уровня шума
#define RELAY_PIN 4   // пин рэле
#define REACTION 100  // миллисекунд на реакцию (плюс минус)
#define MAX_KNOCK 5   // число запоминаемых "стуков"

// включенное состояние системы (1 - вкл., 0 - выкл.)
// bool state_on = false; // система выключена
bool write_start = false; // флаг начала записи
unsigned last_knock = 0; // время последнего хлопка
// unsigned knock_time;

unsigned wait_time[MAX_KNOCK], max_wait_time[MAX_KNOCK], min_wait_time[MAX_KNOCK];

volatile byte mode; // 0- ; 1- ; 2-.

void setup()
{
    Serial.begin(9600);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(NOISE_PIN, INPUT);

    knockWrite();
  
}


void test_knock() {

  if (!digitalRead(NOISE_PIN))
  {
    Serial.print(millis());
    Serial.println(": knock!!!");
  }
  
  //Serial.println(!digitalRead(NOISE_PIN));

}


void knockWrite() { // запись хлопков

  byte knock = 0;       // индекс (номер хлопка)  для записи в массив
  bool is_clap = false; // флаг удала
  unsigned knock_time;  // время между хлопками

  delay(1000);
  Serial.println("GO!");

  delay(500);  
  
  last_knock = millis();

  while (1)
  {

    if (millis() - last_knock > 10000)
    {
      write_start = false; // таймаут, запись остановлена
      break;
    }
    
    is_clap = !digitalRead(NOISE_PIN);

    if (is_clap) {
      Serial.println("Start write!!!");
      write_start = true; // зафиксирован первый удар => начать запись
      last_knock = millis();
      break;

    }
  }
  
  if (write_start)
  { 
    
    unsigned start_time = last_knock;
    while (1)
    { 
      //delay(50);
      is_clap = !digitalRead(NOISE_PIN);
      if (is_clap)
      {
        knock_time = millis() - last_knock;
        if (knock_time<50)
        {
          continue;
        }
        
        wait_time[knock] = knock_time;
        knock++;
        last_knock = millis();
        //is_clap = false;
        Serial.println("knock!");
        is_clap = false;
      
        if (knock == MAX_KNOCK
      )
        {
          break;
        }
      }
      if (millis()-start_time > 5000)
      {
        break;
      }
    // is_clap = !digitalRead(NOISE_PIN);
    }
    
  }

  Serial.println("Replay..");

  for (int i = 0; i < MAX_KNOCK
; i++)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(wait_time[i]);
  }
  

}

void loop()
{
  //test_knock();
}