#include <iarduino_IR_RX.h>

const int pinServo[6] = {5,6,7,8,9,10};
const int pinSound = 11;
const int pinIk = 12;
long DEGREE_START = 110;        //угол начального положения серво (висит объект)
long DEGREE_NORM = 90;          //угол крайнего положения серво, когда объект еще не падает
long DEGREE_DROP = 0;           //угол падения объекта
long DROP_DELAY_MAX = 1000;    //максимальное время ожидания следующего броска
iarduino_IR_RX IR(pinIk);

int modeGame;                         //Режим игры
unsigned long timer_last_drop;        //время последнего сброса
int countDrops;                       //счетчик бросков
int dropList[6]={-1,-1,-1,-1,-1,-1}; //последовательность сбросов
long delayBeforeNextDrop;             //текущее время до сброса
long degree_cur = 0;                  //угол текущего состояния

void setup() 
{
  Serial.begin(9600);
  IR.begin();
  IR.protocol(IR_CLEAN);
  pinMode(pinSound, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 5; i <= 10; ++i){
    pinMode(i, OUTPUT);
  }
  modeGame = 0;
  countDrops = 0;
  playMusic(2);
  Serial.println("HELLO! WAS STARTED...");

}
//1=8160
//2=2064
//3=1040
//4=3088
//5=528
//6=2576
void loop() 
{
  if(IR.check()){
    int irData = IR.data;
    if(irData == 528){//5 начальное положение
      blinkDiod();
      setPositionAll(DEGREE_START);
      modeGame = 0;
      Serial.println("SET START POSITION");
    }
    if(irData == 8160){//1 начало игры 1
      blinkDiod();
      newGame();
    }
  }
  if(modeGame == 0){
    return;
  }
  if(countDrops == 6){
    modeGame = 0;
    Serial.println("GAME OVER!");
    return;
  }
  if(isIntervalPassed(timer_last_drop, delayBeforeNextDrop)){
    drop();
  } else{
    //sway();
  }
  delay(10);
}
void newGame(){
  //setPositionAll(DEGREE_START);
  degree_cur = DEGREE_START;
  countDrops = 0;
  timer_last_drop = millis();
  fillDropList();
  delayBeforeNextDrop = random(1000, DROP_DELAY_MAX);
  playMusic(2);
  modeGame = 1;
  Serial.println("New Game");
}
void sway(){
  //Serial.println("SWAY! ");
  if(degree_cur == DEGREE_START){
    degree_cur = DEGREE_NORM;
  } else {
    degree_cur = DEGREE_START;
  }
  for(int i = 0; i < countDrops; ++i){
    servoPulse(pinServo[dropList[i]], degree_cur);
    delay(500);
  }
}
void drop(){
    Serial.println("DROP!");
    servoPulse(pinServo[dropList[countDrops]], DEGREE_DROP);
    delay(2000);
    ++countDrops;
    delayBeforeNextDrop = random(1000, DROP_DELAY_MAX);
    timer_last_drop = millis();
}
void servoPulse(int pinServo, long angle) {
  for (int i = 0; i <= 50; i++){
    int pulseWidth = (angle * 11) + 500; 
    digitalWrite(pinServo, HIGH); // set the level of servo pin as high
    delayMicroseconds(pulseWidth); // delay microsecond of pulse width
    digitalWrite(pinServo, LOW); // set the level of servo pin as low
    delay(20 - pulseWidth / 1000);
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
  Serial.println("START FILLED DROP LIST");
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
  Serial.println("DROP LIST WAS FILLED");
}
bool valueIsExistsInDropList(int value){
  for(int i = 0; i < 6; ++i){
    if(dropList[i]==value){
      return true;
    }
  }
  return false;
}
void playMusic(int countRepeat){
  /* todo open
  for(int i = 0; i < countRepeat; ++i){
    analogWrite(pinSound, 500);
    delay(300);
    analogWrite(pinSound, 0);
    delay(300);
  }
  */
}


//============================================================================================
void blinkDiod(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
/*
void testServo(){
  for(int i = 0; i < 6; ++i){
    //pinServo[i].write(100);
    delay(2000);
    //pinServo[i].write(0);
    delay(2000);
    //pinServo[i].write(100);
    delay(2000);
  }
}
void testIkServo(){
  if(IR.check()){
    int irData = IR.data;
    if(irData == 8160){
      blinkDiod();
      setPositionAll(DEGREE_DROP);
    }
    if(irData == 2064){
      blinkDiod();
      setPositionAll(DEGREE_START);
    }
    if(irData == 1040){
      blinkDiod();
      setPositionAll(DEGREE_NORM);
    }
   // Serial.println(IR.data);
  } else{
  }
  delay(10);
}
}
*/
