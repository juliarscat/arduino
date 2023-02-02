// Sample code to create a simple EMF detector with arduino, some leds and some pins
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

#define NUMREADINGS 15

int senseLimit = 15; 
int probePin = 3;
int val = 0;

int LED1 = 2;
int LED2 = 3;
int LED3 = 4;
int LED4 = 5;

char str[10];

void drawTest(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 20, "Detector EMF");
}

int buzzer = 9;

int buzzerTone = 0;

unsigned long previousMillis = 0; const long interval = 1000;

int readings[NUMREADINGS];
int index = 0;
int total = 0;
int average = 0;

void setup() {

pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);


  u8g.firstPage();  
  do {
    drawTest();
  } while( u8g.nextPage() );

Serial.begin(9600);

for (int i = 0; i < NUMREADINGS; i++) readings[i] = 0;

}

void loop() {

val = analogRead(probePin);

if(val >= 1){

val = constrain(val, 1, senseLimit); val = map(val, 1, senseLimit, 1, 1023);

total -= readings[index]; readings[index] = val; total += readings[index]; index = (index + 1);

if (index >= NUMREADINGS) index = 0;

average = total / NUMREADINGS;

if (average > 100) {digitalWrite(LED1, HIGH);} else {digitalWrite(LED1, LOW);}

if (average > 300) {digitalWrite(LED2, HIGH);} else {digitalWrite(LED2, LOW);}

if (average > 500) {digitalWrite(LED3, HIGH);} else {digitalWrite(LED3, LOW);}

if (average > 700) {digitalWrite(LED4, HIGH); tone(buzzer, 1000);} else {digitalWrite(LED4, LOW); noTone(buzzer);}

Serial.println(val); // use output to aid in calibrating }

 // picture loop
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB08);
    
    u8g.drawStr( 0, 15, "Valor EMF:");
    u8g.drawStr( 70, 15, dtostrf(val, 5, 2, str));
    
    
  } while( u8g.nextPage() );

}
}
