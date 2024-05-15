#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN 9    // Configurable, see typical pin layout above
#define SS_PIN 10    // Configurable, see typical pin layout above
#define BUZZER_PIN 2 // Pin where the buzzer is connected

Servo servoMotor1;  // Create servo objects for each motor
Servo servoMotor2;
Servo servoMotor3;

int angle1 = 90;    // Initial angles for each servo motor
int angle2 = 90;
int angle3 = 110;

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
bool loggedIn = false; // Variable to track login state

void setup() {
  Serial.begin(9600);   // Initialize serial communications
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522

  servoMotor1.attach(5); // Attach servo motor 1 to pin 5
  servoMotor2.attach(6); // Attach servo motor 2 to pin 6
  servoMotor3.attach(7); // Attach servo motor 3 to pin 7
  
  servoMotor1.write(angle1); // Set initial angles for each servo motor
  servoMotor2.write(angle2);
  servoMotor3.write(angle3);

  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
  Serial.println("Scan an RFID tag to log in...");
  Serial.println("Type '6' in the Serial Monitor to log out.");
}

void loop() {
  if (loggedIn) {
    if (Serial.available() > 0) { // Check if data is available to read
      String input = Serial.readStringUntil('\n');  // Read the input from serial monitor
      input.trim(); // Remove any whitespace characters
      Serial.print("Received input: ");
      Serial.println(input); // Debugging output to verify input
      
      // Call functions based on user input
      switch (input.toInt()) {
        case 1:
          Med1();
          break;
        case 2:
          Med2();
          break;
        case 3:
          Med3();
          break;
        case 4:
          Med4();
          break;
        case 5:
          Med5();
          break;
        case 6:
          LOGOUT();
          break;
        default:
          Serial.println("Invalid input. Please enter a number from 1 to 6.");
          break;
      }
    }
    return; // Skip the rest of the loop when logged in
  }

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

  // Set logged in state
  loggedIn = true;
  Serial.println("Logged in. Type '6' in the Serial Monitor to log out.");
  
  delay(1000); // Wait a second before allowing another scan
  while (Serial.available() > 0) {
    Serial.read(); // Clear the Serial buffer
  }
}

void beepBuzzer(int duration) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
}

void Med1() {
  servoMotor2.write(10); // Set angles for each servo motor
  delay(2000); // Wait for the servo to move
  servoMotor1.write(180); // Return to initial position
  delay(2000);
  servoMotor1.write(90);
  Serial.println("Medication 1 dispensed.");
}

void Med2() {
  servoMotor2.write(85); // Set angles for each servo motor
  delay(2000); // Wait for the servo to move
  servoMotor1.write(180); // Return to initial position
  delay(2000);
  servoMotor1.write(90);
  Serial.println("Medication 2 dispensed.");
}

void Med3() {
  servoMotor2.write(162); // Set angles for each servo motor
  delay(2000); // Wait for the servo to move
  servoMotor1.write(180); // Return to initial position
  delay(2000);
  servoMotor1.write(90);
  Serial.println("Medication 3 dispensed.");
}

void Med4() {
  servoMotor2.write(48); 
  delay(2000); 
  servoMotor3.write(17); 
  delay(2000);
  servoMotor3.write(110);
  Serial.println("Medication 4 dispensed.");
}

void Med5() {
  servoMotor2.write(125); 
  delay(2000); 
  servoMotor3.write(11); 
  delay(2000);
  servoMotor3.write(110);
  Serial.println("Medication 5 dispensed");
}

void LOGOUT() {
  loggedIn = false;
  Serial.println("Logged out. Scan an RFID tag to log in...");
}
