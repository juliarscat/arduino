  //Sample code to control a fan using a PWM Module
#include <Wire.h>

const int fanPin = 9;  // Pin that the fan is connected to
const int pwmPin = 6;  // Pin that the PWM module is connected to
int speed = 0;         // Speed of the fan (0-255)

void setup() {
  pinMode(fanPin, OUTPUT);  // Set the fan pin as an output
  pinMode(pwmPin, OUTPUT);  // Set the PWM pin as an output

  // Initialize the I2C communication with the PWM module
  Wire.begin();
  Wire.beginTransmission(0x40);
  Wire.write(0x00);  // Send the register address
  Wire.write(0x00);  // Send the data to set the frequency
  Wire.endTransmission();
}

void loop() {
  // Increase the fan speed
  for (speed = 0; speed < 256; speed++) {
    analogWrite(pwmPin, speed);
    delay(15);
  }

  // Decrease the fan speed
  for (speed = 255; speed >= 0; speed--) {
    analogWrite(pwmPin, speed);
    delay(15);
  }
}
