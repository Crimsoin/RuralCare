#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9    // Configurable, see typical pin layout above
#define SS_PIN 10    // Configurable, see typical pin layout above
#define BUZZER_PIN 2 // Pin where the buzzer is connected

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Initialize serial communications
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
  Serial.println("Scan an RFID tag to see the UID...");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Print the UID of the card
  Serial.print("UID tag: ");
  String uidString = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    uidString += String(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Beep the buzzer
  beepBuzzer(100); // Beep for 100 ms

  delay(1000); // Wait a second before scanning again
}

void beepBuzzer(int duration) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
}
