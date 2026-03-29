#define KNOB_PIN A0
#include "RichShieldTM1637.h"
#include <Wire.h>
#include "RichShieldDHT.h"
#define CLK 10
#define DIO 11
#define BUTTONK1 8
#define BUTTONK2 9
#define LED_RED 4
#define LED_GREEN 5
#define LED_BLUE 6
#define LED_YELLOW 7
TM1637 disp(CLK,DIO);
#include "RichShieldTM1637.h"
#include <Wire.h>
#include "RichShieldTM1637.h"
#include "RichShieldNTC.h"
#include "RichShieldPassiveBuzzer.h"
#define PassiveBuzzerPin 3
PassiveBuzzer buz(PassiveBuzzerPin);
#define NTC_PIN A1
NTC temper(NTC_PIN);  
DHT dht;
#define CLK 10//CLK of the TM1637 IC connect to D10 of OPEN-SMART UNO R3
#define DIO 11//DIO of the TM1637 IC connect to D11 of OPEN-SMART UNO R3


#define NOTE_L1  262
#define NOTE_L2  294
#define NOTE_L3  330
#define NOTE_L4  349
#define NOTE_L5  392
#define NOTE_L6  440
#define NOTE_L7  494
#define NOTE_M1  523
#define NOTE_M2  587
#define NOTE_M3  659
#define NOTE_M4  698
#define NOTE_M5  784
#define NOTE_M6  880
#define NOTE_M7  988
#define NOTE_H1  1046
#define NOTE_H2  1175
#define NOTE_H3  1318
#define NOTE_H4  1397
#define NOTE_H5  1568
#define NOTE_H6  1760
#define NOTE_H7  1976

int knobValue;

//-------------------------------------------
//musical notation of Two Tigers 
const static int doubleTiger[] = { 
NOTE_M1,NOTE_M2,NOTE_M3,NOTE_M1, 
NOTE_M1,NOTE_M2,NOTE_M3,NOTE_M1, 
NOTE_M3,NOTE_M4,NOTE_M5, 
NOTE_M3,NOTE_M4,NOTE_M5, 
NOTE_M5,NOTE_M6,NOTE_M5,NOTE_M4,
NOTE_M3,NOTE_M1, 
NOTE_M5,NOTE_M6,NOTE_M5,NOTE_M4,
NOTE_M3,NOTE_M1, 
NOTE_M2,NOTE_L5,
NOTE_M1,0,
NOTE_M2,NOTE_L5,
NOTE_M1,0
};
//-------------------------------------------
////note duration of Two Tigers, 2 is half a beat, 1 is a beat.
const static int tempo[] = { 
2,2,2,2, 
2,2,2,2, 
2,2,1, 
2,2,1,  
2,2,2,2,
1,1,
2,2,2,2,
1,1,
1,1,
1,1,
1,1,
1,1
};

const static int tiger[]=
{
  NOTE_L1, NOTE_L1,0, NOTE_L1, 0, NOTE_H2, NOTE_L1,
  0, NOTE_M1, 0, NOTE_M5, 0, NOTE_H2, 0, NOTE_M5, 0,
  NOTE_L3, 0, NOTE_M3, 0, NOTE_H3


};
 const static int buzzer[]= 
{
  80,80,80,80,80,80,80,80,80,
  240,80,240,80,160,80,160,80,
  160,80,80,80

};
void displayHumidity(int8_t humi)  // humidity sensor
{
  int8_t temp[4];
  if(humi < 100)temp[0] = INDEX_BLANK;
  else temp[0] = humi/100;
  humi %= 100;
  temp[1] = humi / 10;
  temp[2] = humi % 10;
  temp[3] = 18;	          //index of 'H' for celsius degree symbol.
  disp.display(temp);
}


void displayTemperature(int8_t temperature) // NTC Temperature sensor
{
  int8_t temp[4];
  if(temperature < 0)
	{
		temp[0] = INDEX_NEGATIVE_SIGN;
		temperature = abs(temperature);
	}
	else if(temperature < 100)temp[0] = INDEX_BLANK;
	else temp[0] = temperature/100;
	temperature %= 100;
	temp[1] = temperature / 10;
	temp[2] = temperature % 10;
	temp[3] = 12;	          //index of 'C' for celsius degree symbol.
  disp.display(temp);
}
void sing() {
  // iterate over the notes of the melody:
    int size = sizeof(doubleTiger) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      int noteDuration = 500 / tempo[thisNote];//a beat for 0.5 second

      buz.playTone(doubleTiger[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 0.30;
      delay(pauseBetweenNotes);
    }
}

void setup()
 {
  

disp.init();
dht.begin();
pinMode(BUTTONK1,INPUT_PULLUP);
pinMode (LED_RED,OUTPUT);
pinMode (LED_GREEN,OUTPUT);
pinMode (LED_BLUE,OUTPUT);
pinMode (LED_YELLOW,OUTPUT);
pinMode (BUTTONK2,INPUT_PULLUP);
Serial.begin(9600);

}



void loop(){
float h = dht.readHumidity();



knobValue = analogRead(KNOB_PIN);

  
  if(knobValue >= 800) // tilting potentiometer to get the results from humidity sensor 
  {
   
    displayHumidity((int8_t)h);
    delay(1000);
    Serial.println(h);
  }
  else if(knobValue < 800){
    disp.clearDisplay();
    if (digitalRead(BUTTONK1) == 0){
    timer();
   }
   if (digitalRead(BUTTONK2)==0){          //Using button K2 to get the results from temperature sensor
   float celsius;
   celsius = temper.getTemperature()*10;//get temperature
   disp.display(celsius);
   displayTemperature((int8_t)celsius);
   delay(500);//delay 1000ms
   Serial.print((int8_t)celsius);  // getting the graphs in serial plotter
   Serial.print(",");
   Serial.println((int8_t)h);
  if(celsius > 33){
    sing();
  }
 
 
  }


  }

}

void timer(void) // stopwatch for shower period
{
 
   delay(300);
   double i;
    for(i=0; i<=20; i+=0.5)
    {
      disp.display(i);
      delay(1000); // 2 sec : 1 min
    if(i>=0&&i<=5) // blue light turns on during this range
 {
 digitalWrite(6,HIGH); 
 digitalWrite(4,LOW);
 digitalWrite(5,LOW);
 digitalWrite(7,LOW);




 }   
 else if(i>=5&&i<=10){  //green light turns on during this range
  digitalWrite(5,HIGH);
 digitalWrite(4,LOW);
 digitalWrite(6,LOW);
 digitalWrite(7,LOW);



 }
 else if(i>=10&&i<=15)  //yellow light turns on during this range
 {
  digitalWrite(7,HIGH);
 digitalWrite(4,LOW);
 digitalWrite(5,LOW);
 digitalWrite(6,LOW);

 }


 
 else if(i>=15&&i<20)  // red light and the buzzer turns on during this range
 {
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
 }

else if(i=20)
 {
  int m;
 disp.clearDisplay();
 digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  for(m=0;m<22;m++)
  {
    buz.playTone(tiger[m],buzzer[m]);
    delay(5);
  }
 
  }
 
 }

 

}


 












