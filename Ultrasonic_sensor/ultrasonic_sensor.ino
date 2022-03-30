
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3f, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

const int pingPin = 6; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7; // Echo Pin of Ultrasonic Sensor

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   // Initiate the LCD:
   lcd.init();
   lcd.backlight();
//   lcd.setCursor(0, 0);
//   lcd.print("inches:");
//   lcd.setCursor(0, 1);
//   lcd.print("cm:");
}

void loop() {
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);

   lcd.clear();
   
   lcd.setCursor(0, 0);
   lcd.print(inches);
   lcd.setCursor(0,1);
   lcd.print(cm);

   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   
   delay(100);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
