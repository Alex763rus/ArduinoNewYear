
#include <Servo.h> //используем библиотеку для работы с сервоприводом

#define OCTAVE_OFFSET 0

#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951

#define TONE_PIN 9

int notes[] = { 0,
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};
char *song1 = "LastReso:d=4,o=5,b=45:32f,32g#,32g,32g#,32c6,32g#,32g,32g#,32d#,32g#,32g,32g#,32c6,32g#,32g,32g#,32c#,32g#,32g,32g#,32c6,32g#,32g,32g#,32c,32g#,32g,32g#,32c6,32g#,32g,32g#,32f,32g#,32g,32g#,32c6,32g#,32g,32g#,32d#,32g#,32g,32g#,32c6,32g#,32g,32g#,32c#,32g#,32g,32g#,32c6,32g#,32g,32g#,32c,32g#,32g,32g#,32c6,32g#,32g,32g#";
char *song2 = "countdown:d=4,o=5,b=125:p,8p,16b,16a,b,e,p,8p,16c6,16b,8c6,8b,a,p,8p,16c6,16b,c6,e,p,8p,16a,16g,8a,8g,8f#,8a,g.,16f#,16g,a.,16g,16a,8b,8a,8g,8f#,e,c6,2b.,16b,16c6,16b,16a,1b";
char *song3 = "Macarena:d=4,o=5,b=180:f,8f,8f,f,8f,8f,8f,8f,8f,8f,8f,8a,8c,8c,f,8f,8f,f,8f,8f,8f,8f,8f,8f,8d,8c,p,f,8f,8f,f,8f,8f,8f,8f,8f,8f,8f,8a,p,2c.6,a,8c6,8a,8f,p,2p";
char *song4 = "PinkPanther:d=4,o=5,b=160:8d#,8e,2p,8f#,8g,2p,8d#,8e,16p,8f#,8g,16p,8c6,8b,16p,8d#,8e,16p,8b,2a#,2p,16a,16g,16e,16d,2e";
char *song5 = "Back to the Future:d=16,o=5,b=200:4g.,p,4c.,p,2f#.,p,g.,p,a.,p,8g,p,8e,p,8c,p,4f#,p,g.,p,a.,p,8g.,p,8d.,p,8g.,p,8d.6,p,4d.6,p,4c#6,p,b.,p,c#.6,p,2d.6";
char *song6 = "Jingle Bells:d=4,o=5,b=170:b,b,b,p,b,b,b,p,b,d6,g.,8a,2b.,8p,c6,c6,c6.,8c6,c6,b,b,8b,8b,b,a,a,b,2a,2d6";
char *song7 = "smb_under:d=4,o=6,b=100:32c,32p,32c7,32p,32a5,32p,32a,32p,32a#5,32p,32a#,2p,32c,32p,32c7,32p,32a5,32p,32a,32p,32a#5,32p,32a#,2p,32f5,32p,32f,32p,32d5,32p,32d,32p,32d#5,32p,32d#,2p,32f5,32p,32f,32p,32d5,32p,32d,32p,32d#5,32p,32d#";
char *song8 = "Teenage Turtles:d=8,o=6,b=100:g5,a5,g5,a5,g5,16a5,g.5,a5,a#5,c,a#5,c,a#5,16c,a#.5,c,d#,f,d#,f,d#,16f,d#.,f,16c,16c,16c,16c,a#5,4c,16c7,16c7,16c7";
char *song9 = "HarryPotter:d=8,o=6,b=100:b5,e.,16g,f#,4e,b,4a.,4f #.,e.,16g,f#,4d,f,2b5,p,b5,e.,16g,f#,4e,b,4d7,c#7,4c7,g#,c.7,16b,a#,4a#5,g,2e";
char *song10 = "Amerika:d=4,o=5,b=125:d,d,8d,8d,8d,8f,a,8a,a.,8p,8a,g,8g,g.,8p,8g,g,8e,2e,8p,d,d,8d,8d,8d,8f,a,8a,a.,8p,8c6,c6,8e,e.,8p,8c6,c6,8e,e.,p,d,d,8d,8d,8d,8f,a,8a,a.,8p,8a,g,8g,g.,8p,8g,g,8e,2e,8p,d,d,8d,8d,8d,8f,a,8a,a.,8p,8c6,c6,8e,e.,8p,8c6,c6,8e,e";

const int pinServo = 10;//порт сервопривода
const int pinButtonPlay = 11;//кнопка запуска
Servo servo; //объявляем переменную servo типа Servo

long countSteps;
long randDegree;
long stepServo;

void setup(void)
{ 
  Serial.begin(9600);
  // инициализируем пин, подключенный к кнопке, как вход
  pinMode(pinButtonPlay, INPUT_PULLUP); 
  servo.attach(pinServo); //привязываем привод к порту 10
  countSteps = 0;
  randDegree = 0;

  //servo.write(0);
}

#define isdigit(n) (n >= '0' && n <= '9')


void loop(void)
{
  
   if(digitalRead(pinButtonPlay) == 0){//нажата кнопка
      // servo.write(180);
      stepServo = 2;
      countSteps = random(4, 10);
      Serial.print("=============");
      Serial.println(countSteps);
      play_rtttl(song9);
   }
   myDelay(millis(), 100);
}


bool servoRun(){
  if(stepServo > 0){
    --stepServo;
    return false;
  }
  stepServo = 2;
  if(countSteps == 0){
     return true;
     //return false;
  }
  --countSteps;
  
  randDegree = random(1,5);
  if(randDegree == 1){
    servo.write(23);
  }
  if(randDegree == 2){
    servo.write(68);
  }
  if(randDegree == 3){
    servo.write(113);
  }
  if(randDegree == 4){
    servo.write(157);
  }
  Serial.println(randDegree);
  return false;
}

void play_rtttl(char *p)
{
  // Absolutely no error checking in here

  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  while(*p != ':') p++;    // ignore name
  p++;                     // skip ':'

  // get default duration
  if(*p == 'd')
  {
    p++; p++;              // skip "d="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    if(num > 0) default_dur = num;
    p++;                   // skip comma
  }

 // Serial.print("ddur: "); Serial.println(default_dur, 10);

  // get default octave
  if(*p == 'o')
  {
    p++; p++;              // skip "o="
    num = *p++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   // skip comma
  }


  // get BPM
  if(*p == 'b')
  {
    p++; p++;              // skip "b="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;                   // skip colon
  }

//  Serial.print("bpm: "); Serial.println(bpm, 10);

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

 // Serial.print("wn: "); Serial.println(wholenote, 10);


  // now begin note loop
  while(*p)
  {
    if(servoRun()){
      return;
    }
    // first, get note duration, if available
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    
    if(num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

    // now get the note
    note = 0;

    switch(*p)
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    // now, get optional '#' sharp
    if(*p == '#')
    {
      note++;
      p++;
    }

    // now, get optional '.' dotted note
    if(*p == '.')
    {
      duration += duration/2;
      p++;
    }
  
    // now, get scale
    if(isdigit(*p))
    {
      scale = *p - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if(*p == ',')
      p++;       // skip comma for next note (or we may be at the end)

    // now play the note

    if(note)
    {
      tone(TONE_PIN, notes[(scale - 4) * 12 + note]);
      //delay(duration);
      myDelay(millis(),duration);
      noTone(TONE_PIN);

    }
    else
    {
     // delay(duration);
     myDelay(millis(),duration);
    }
  }
}
void myDelay(long timerStart, long duration){
  while(!isIntervalPassed(timerStart, duration)){
  }
}
bool isIntervalPassed(long t1, long interval){
  return ((millis() - t1) > interval);
}
//------------------------------------------
