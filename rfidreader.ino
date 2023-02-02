// Arduino code to read and store RFID data, display it on an LCD screen, and save the data to a microSD card
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SD.h>

#define SS_PIN 10
#define RST_PIN 9
#define OLED_RESET 4
#define SD_CS_PIN 5

Adafruit_SSD1306 display(OLED_RESET);
MFRC522 mfrc522(SS_PIN, RST_PIN);

File myFile;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Card Mount Failed");
    return;
  }
  Serial.println("RFID reader ready");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("Card UID: ");
    myFile = SD.open("rfid.txt", FILE_WRITE);
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      display.setCursor(0, i * 8);
      display.println(mfrc522.uid.uidByte[i]);
      myFile.print(mfrc522.uid.uidByte[i]);
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    myFile.close();
    display.display();
    Serial.println();
  }
}
