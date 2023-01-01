#include <iarduino_IR_RX.h>

const int pinServo[6] = {5,6,7,8,9,10};
const int pinIk = 12;
long DEGREE_START = 110;        //угол начального положения серво (висит объект)
long DEGREE_DROP = 0;           //угол падения объекта
long DROP_DELAY_MAX = 10000;    //максимальное время ожидания следующего броска
iarduino_IR_RX IR(pinIk);

int modeGame;                         //Режим игры
unsigned long timer_last_drop;        //время последнего сброса
int countDrops;                       //счетчик бросков
int dropList[6]={-1,-1,-1,-1,-1,-1};  //последовательность сбросов
long delayBeforeNextDrop;             //текущее время до сброса

//коды кнопок пк:
const int button_1 = 8160;
const int button_2 = 2064;
const int button_3 = 1040;
const int button_4 = 3088;
const int button_5 = 528;
const int button_6 = 2576;

void setup() 
{
  IR.begin();
  IR.protocol(IR_CLEAN);
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 0; i < 6; ++i){
    pinMode(pinServo[i], OUTPUT);
  }
  resetState();
}
void loop() 
{
  if(IR.check(true)){
    if(modeGame == 0){
      switch(IR.data){
        case button_1: initGame(1); break;
        case button_2: initGame(2); break;
        case button_3: initGame(3); break;
        case button_5: resetState(); break;
      }
    }
  }
  if(modeGame > 0){
    logicGame();
  }
  delay(10);
}
void resetState(){
  blinkDiod();
  modeGame = 0;
  countDrops = 0;
  setPositionAll(DEGREE_START);
  blinkDiod();
}
void initGame(int modeGameIn){
  blinkDiod();
  timer_last_drop = millis();
  fillDropList();
  delayBeforeNextDrop = random(3000, DROP_DELAY_MAX);
  modeGame = modeGameIn;
}
void logicGame(){
  if(countDrops == 6){
    resetState();
    return;
  }
  if(isIntervalPassed(timer_last_drop, delayBeforeNextDrop)){
    servoMultiPulseFromDropList(modeGame, DEGREE_DROP);
    countDrops = countDrops + modeGame;
    delayBeforeNextDrop = random(3000, DROP_DELAY_MAX);
    timer_last_drop = millis();
    delay(2000);
  } 
}

void servoMultiPulseFromDropList(int countDropsIn, long angle) {
  int dropFinish = countDrops + countDropsIn;
  for (int i = 0; i <= 50; i++){
    for(int s = countDrops; s < dropFinish; s++){
      nextServoTick(pinServo[dropList[s]], angle);
    }
  }
}

void nextServoTick(int pinServo, long angle){
  int pulseWidth = (angle * 11) + 500; 
  digitalWrite(pinServo, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(pinServo, LOW);
  delay(20 - pulseWidth / 1000);
}
void servoPulse(int pinServo, long angle) {
  for (int i = 0; i <= 50; i++){
    nextServoTick(pinServo, angle);
  }
}

void setPositionAll(long degree){
  for(int i = 0; i < 6; ++i){
    servoPulse(pinServo[i], degree);
    delay(2000);
  }
}

bool isIntervalPassed(long t1, long interval){
  return ((millis() - t1) > interval);
}

void fillDropList(){
  for(int i = 0; i < 6; ++i){
    dropList[i]=-1;
  }
  int nextValue = 0;
  randomSeed(micros());
  for(int i = 0; i < 6; ++i){
    while(true){
      nextValue = random(0, 6);
      if(!valueIsExistsInDropList(nextValue)){
        dropList[i] = nextValue;
        break;
      }
    }
  }
}
bool valueIsExistsInDropList(int value){
  for(int i = 0; i < 6; ++i){
    if(dropList[i]==value){
      return true;
    }
  }
  return false;
}
void blinkDiod(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
