#include <Servo.h>

Servo servoMotor1;  // Create servo objects for each motor
Servo servoMotor2;
Servo servoMotor3;

int angle1 = 90;    // Initial angles for each servo motor
int angle2 = 90;
int angle3 = 110;

void setup() {
  Serial.begin(9600);  // Start serial communication
  servoMotor1.attach(5); // Attach servo motor 1 to pin 5
  servoMotor2.attach(6); // Attach servo motor 2 to pin 6
  servoMotor3.attach(7); // Attach servo motor 3 to pin 7
  
  servoMotor1.write(angle1); // Set initial angles for each servo motor
  servoMotor2.write(angle2);
  servoMotor3.write(angle3);
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available to read
    String input = Serial.readStringUntil('\n');  // Read the input from serial monitor
    
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
      default:
        Serial.println("Invalid input. Please enter a number from 1 to 5.");
        break;
    }
  }
}

// Define functions for each medication
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
