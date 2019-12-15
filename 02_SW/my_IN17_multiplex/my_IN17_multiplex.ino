#include <Time.h>
#include "RTClib.h"

#define PIN_TUBE_HOUR_x0 PD5 //hardware 9 - arduino 5
#define PIN_TUBE_HOUR_0x PD4 //hardware 2 - arduino 4

#define PIN_TUBE_MIN_x0 PD3 //hardware 1 - arduino 3
#define PIN_TUBE_MIN_0x PD2 //hardware 32 - arduino 2

#define PIN_TUBE_SEC_x0 PD1 //hardware 31 - arduino 1
#define PIN_TUBE_SEC_0x PD0 //hardware 30 - arduino 0

#define PIN_A PC0//hardware 23 - arduino 14
#define PIN_B PC1//hardware 24 - arduino 15
#define PIN_C PC2//hardware 25 - arduino 16
#define PIN_D PC3//hardware 26 - arduino 17

RTC_DS3231 RTC;
DateTime now;
DateTime now_btn;
#define SWITCH_HOUR_SUMM_WINTER    PB0   //hw 12    // the pin that the pushbutton is attached to
const int  buttonPin_1 = PB1;  //hw 13    // the pin that the pushbutton is attached to

int lastButtonState = 0;     // previous state of the button
int buttonState = 0;         // current state of the button
/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int address = 0;
byte RTC_setup = 0x00;

void setup() {
  
  RTC.begin();
  RTC.use_summertime_EU = true;
  // put your setup code here, to run once:
  DDRB = 0b00000001; // PB0 is used
  DDRC = 0b11111111; // PC0 - PC5 are used
  DDRD = 0b00111111; // PD0 - PD5 are used

// initialize the button pin as a input:
  pinMode(PB0, INPUT);
  
  //Serial.println("RTC lost power, lets set the time!");
  // following line sets the RTC to the date & time this sketch was compiled
  //RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  delay(500);
}

int counter = 0;
ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)

  if(counter==10)
  {counter = 0;}
  counter++;
}

/*
#define PIN_A PC0//hardware 23 - arduino 14
#define PIN_B PC1//hardware 24 - arduino 15
#define PIN_C PC2//hardware 25 - arduino 16
#define PIN_D PC3//hardware 26 - arduino 17
*/
void Write_0(){PORTC = PORTC | 0b00001001;}//IN17 ok
void Write_1(){PORTC = PORTC | 0b00000001;}//IN17 ok
void Write_2(){PORTC = PORTC | 0b00000111;}//IN17 ok
void Write_3(){PORTC = PORTC | 0b00000011;}//IN17 ok
void Write_4(){PORTC = PORTC | 0b00000000;}//IN17 ok
void Write_5(){PORTC = PORTC | 0b00000100;}//IN17 ok
void Write_6(){PORTC = PORTC | 0b00000101;}//IN17 ok
void Write_7(){PORTC = PORTC | 0b00000110;}//IN17 ok
void Write_8(){PORTC = PORTC | 0b00000010;}//IN17 ok
void Write_9(){PORTC = PORTC | 0b00001000;}//IN17 ok

/* Select a digit 0-9 and call the appropriate send function */
void selectDigit(int d)  
{
 switch(d)
 {
  case 0: Write_0(); break;
  case 1: Write_1(); break;
  case 2: Write_2(); break;
  case 3: Write_3(); break;
  case 4: Write_4(); break;
  case 5: Write_5(); break;
  case 6: Write_6(); break;
  case 7: Write_7(); break;
  case 8: Write_8(); break;
  case 9: Write_9(); break;
  default: Write_0(); break;
 } 
}
 
void display_clock(int pin, int digit)
{
  digitalWrite(pin, HIGH);
  selectDigit(digit);
  delay(2);    
  digitalWrite(pin, LOW);
  delay(1);       
  PORTC = PORTC & 0b11110000;
}

void loop() 
{
  
  // Read from the real time clock
  now = RTC.now();

  //check button press
  //switch_Winter_Summer_Hour();


  //PIN_TUBE_SEC_0x
  display_clock(PD0, (now.second())%10); 
  //PIN_TUBE_SEC_x0
  display_clock(PD1, (now.second())/10);

  //PIN_TUBE_MIN_0x
  display_clock(PD2, (now.minute())%10);
  //PIN_TUBE_MIN_x0
  display_clock(PD3, (now.minute())/10);

  //PIN_TUBE_HOUR_0x
  display_clock(PD4, (now.hour())%10);
  //PIN_TUBE_HOUR_x0
  display_clock(PD5, (now.hour())/10);
}
  
