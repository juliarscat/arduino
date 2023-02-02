// In this code, the IR signals are received by the IR receiver connected to pin 11, and then sent using the IR LED connected to pin 13. The code also includes a button connected to pin 2, which can be used to send the last received IR signal.
#include <IRremote.h>

int RECV_PIN = 11;
int LED_PIN = 13;
int BUTTON_PIN = 2;

IRrecv irrecv(RECV_PIN);
IRsend irsend(LED_PIN);

decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irsend.sendRaw(results.raw, results.rawlen, 38);
    irrecv.resume(); // Receive the next value
  }

  if (digitalRead(BUTTON_PIN) == LOW) {
    irsend.sendRaw(results.raw, results.rawlen, 38);
    delay(200);
  }
