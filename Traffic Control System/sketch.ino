#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <Servo.h> 
 
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address, columns, rows 
Servo gateServo; 
 
// Define the pins for your LEDs 
int redPin = 2; 
int yellowPin = 3; 
int greenPin = 4; 
 
int redDuration = 5000;  // Red light duration in milliseconds 
int yellowDuration = 2000;  // Yellow light duration 
int greenDuration = 5000;  // Green light duration 
 
void setup() { 
  // Initialize the LCD 
  lcd.init(); 
  lcd.backlight(); 
 
  // Set the LED pins as output 
  pinMode(redPin, OUTPUT); 
  pinMode(yellowPin, OUTPUT); 
  pinMode(greenPin, OUTPUT); 
 
  // Attach the servo to a pin 
  gateServo.attach(9); // Use any available PWM pin 
 
  // Set the gate to 0 degrees initially 
  gateServo.write(0); 
} 
 
void loop() { 
  // Red light 
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("STOP"); 
  int remainingTime = redDuration / 1000; // Convert to seconds 
  gateServo.write(0); // Gate closed 
  for (int i = 0; i < remainingTime; i++) { 
    lcd.setCursor(0, 1); 
    lcd.print("Remaining: " + String(remainingTime - i) + " sec "); 
    digitalWrite(redPin, HIGH); 
    delay(1000); 
  } 
  digitalWrite(redPin, LOW); 
 
  // Yellow light 
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("GET READY"); 
  remainingTime = yellowDuration / 1000; 
  for (int i = 0; i < remainingTime; i++) { 
    lcd.setCursor(0, 1); 
    lcd.print("Remaining: " + String(remainingTime - i) + " sec "); 
    digitalWrite(yellowPin, HIGH); 
    delay(1000); 
} 
digitalWrite(yellowPin, LOW); 
// Green light 
lcd.clear(); 
lcd.setCursor(0, 0); 
lcd.print("GO"); 
remainingTime = greenDuration / 1000; 
gateServo.write(90); // Gate open 
for (int i = 0; i < remainingTime; i++) { 
lcd.setCursor(0, 1); 
lcd.print("Remaining: " + String(remainingTime - i) + " sec "); 
digitalWrite(greenPin, HIGH); 
delay(1000); 
} 
digitalWrite(greenPin, LOW); 
gateServo.write(0); // Gate closed after green phase 
}