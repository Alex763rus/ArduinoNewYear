#include <Servo.h>
#include <iarduino_IR_RX.h>

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
int pinSound = 11;
int pinIk = 12;

iarduino_IR_RX IR(pinIk);

Servo dropsQueue[6] = {};
long DEGREE_START = 135;
long DEGREE_NORM = 90;
long DEGREE_DROP = 0;
long DROP_DELAY_MAX = 10000; //Максимальное время ожидания следующего броска

unsigned long timer_last_drop;    //Таймер, время последнего сброса
int countDrops;                   //Счетчик бросков
int dropList[6]={-1,-1,-1,-1,-1,-1};                //Последовательность сбросов
long delayBeforeNextDrop;             //Текущее время до сброса

void setup() 
{
  Serial.begin (9600);
  Serial.println("HELLO");
//  IR.begin();
 // IR.protocol(IR_CLEAN);

  servo0.attach(5);
  servo1.attach(6);
  servo2.attach(7);
  servo3.attach(8);
  servo4.attach(9);
  servo5.attach(10);
  dropsQueue[0] = servo0;
  dropsQueue[1] = servo1;
  dropsQueue[2] = servo2;
  dropsQueue[3] = servo3;
  dropsQueue[4] = servo4;
  dropsQueue[5] = servo5;

  pinMode(pinSound, OUTPUT);
  
  //setPositionAll(DEGREE_START);
  countDrops = 0;
  timer_last_drop = millis();
  fillDropList();
  delayBeforeNextDrop = random(1000, DROP_DELAY_MAX);

  playMusic(2);
/*
for(int i = 0; i < 6; ++i){
  dropsQueue[i].write(100);
  delay(2000);
  dropsQueue[i].write(0);
  delay(2000);
    dropsQueue[i].write(100);
  delay(2000);
}
  
     */
}

void loop() 
{
/*    if(IR.check()){
  playMusic(2);
  Serial.println("+++++HELLO");
    }
  */
  /*
  if(countDrops == 6){
    return;
  }
  if(isIntervalPassed(timer_last_drop, delayBeforeNextDrop)){
    Serial.println("YES");
    dropsQueue[dropList[countDrops]].write(DEGREE_DROP);
    delay(2000);
    ++countDrops;
    delayBeforeNextDrop = random(1000, DROP_DELAY_MAX);
    timer_last_drop = millis();
  } else{
    for(int i = 0; i < countDrops; ++i){
      if(dropsQueue[dropList[i]].read() == DEGREE_START){
        dropsQueue[dropList[i]].write(DEGREE_NORM);
      } else{
        dropsQueue[dropList[i]].write(DEGREE_START);
      }
      delay(500);
    }
    delay(500);
  }

*/
}

void setPositionAll(long degree){
  for(int i = 0; i < 6; ++i){
    dropsQueue[i].write(degree);
    delay(500);
  }
}

bool isIntervalPassed(long t1, long interval){
  return ((millis() - t1) > interval);
}

void fillDropList(){
  int nextValue = 0;
  randomSeed(micros());
  for(int i = 0; i < 6; ++i){
    while(true){
      nextValue = random(0, 6);
      Serial.println(nextValue);
      if(!valueIsExistsInDropList(nextValue)){
        break;
      }
    }
    dropList[i] = nextValue;
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
void playMusic(int countRepeat){
  for(int i = 0; i < countRepeat; ++i){
    analogWrite(pinSound, 500);
    delay(300);
    analogWrite(pinSound, 0);
    delay(300);
  }
}
