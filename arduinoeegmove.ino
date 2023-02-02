//Code you can add to your project and manipulate to get the data from a bluetooth device to move your arduino robot.

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

void setup() {
  BTSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (BTSerial.available()){
    int data = BTSerial.read();

    if (data == 'w') {
      // move forward
    } else if (data == 's') {
      // move backward
    } else if (data == 'a') {
      // turn left
    } else if (data == 'd') {
      // turn right
    }
  }
}
