//Humidity and temperature sensor

#include "DHT.h"
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

#define DHTPIN 7     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor for normal 16mhz Arduino
//DHT dht(DHTPIN, DHTTYPE);
// NOTE: For working with a faster chip, like an Arduino Due or Teensy, you
// might need to increase the threshold for cycle counts considered a 1 or 0.
// You can do this by passing a 3rd parameter for this threshold.  It's a bit
// of fiddling to find the right value, but in general the faster the CPU the
// higher the value.  The default for a 16mhz AVR is a value of 6.  For an
// Arduino Due that runs at 84mhz a value of 30 works.
// Example to initialize DHT sensor for Arduino Due:
DHT dht(DHTPIN, DHTTYPE, 7);

char str[10];

void drawTest(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 20, "Sensor de temper");
  u8g.drawStr( 0, 40, "atura i humitat");
   u8g.drawStr ( 0, 60, "by Juliars");
}

void setup() {
  Serial.begin(9600); 
  Serial.println("Sensor de temperatura i humitat by Juliars");
 
  dht.begin();
  u8g.firstPage();  
  do {
    drawTest();
  } while( u8g.nextPage() );
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("No es pot llegir del sensor. Comprova les connexions.");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humitat: "); 
  Serial.print(h);
  Serial.print(" %\t");
  
  Serial.print("Temperatura: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  
  Serial.print("Sensacio: ");
  Serial.print(hi);
  Serial.println(" *F");
  
  // picture loop
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB08);
    
    u8g.drawStr( 0, 15, "Humitat:");
    u8g.drawStr( 80, 15, dtostrf(h, 5, 2, str));
    u8g.drawStr( 120, 15, "%");
    
    u8g.drawStr( 0, 30, "Temperatura:");
    u8g.drawStr( 80, 30, dtostrf(t, 5, 2, str));
    u8g.drawStr( 120, 30, "\260C");
    
    u8g.drawStr( 80, 45, dtostrf(f, 5, 2, str));
    u8g.drawStr( 120, 45, "\260F");
    
    u8g.drawStr( 0, 60, "Sensacio :");
    u8g.drawStr( 80, 60, dtostrf(hi, 5, 2, str));
    u8g.drawStr( 120, 60, "\260F");
    
  } while( u8g.nextPage() );
}
