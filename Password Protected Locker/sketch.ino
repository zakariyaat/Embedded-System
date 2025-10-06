#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <Servo.h> 
#include <Keypad.h> 
Servo myServo;  // create servo object to control a servo 
const int servoPin = 10;  // connect the servo to pin 10 
const int buzzerPin = 11;  // connect the buzzer to pin 11 
const int ROW_NUM    
= 4; // four rows 
const int COLUMN_NUM = 4; // four columns 
char keys[ROW_NUM][COLUMN_NUM] = { 
{'1','2','3','A'}, 
{'4','5','6','B'}, 
{'7','8','9','C'}, 
{'*','0','#','D'} 

}; 
byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; // connect to the row pinouts of the keypad 
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; // connect to the column pinouts of the keypad 
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM); 
const char* correctPassword = "1234"; 
char enteredPassword[5];  // 4 digits + null terminator 
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD I2C address to 0x27 for a 16 chars and 2 line display 
void setup() { 
lcd.begin(16, 2); 
lcd.setCursor(0, 0); 
lcd.print("Enter password:"); 
myServo.attach(servoPin);  // attaches the servo on pin 10 to the servo object 
myServo.write(90);  // initialize servo position (90 degrees) 
pinMode(buzzerPin, OUTPUT); 
} 
void loop() { 
char key = keypad.getKey(); 
if (key) { 
if (key == '#') {  
      // Check the entered password when '#' is pressed 
      if (strcmp(enteredPassword, correctPassword) == 0) { 
        lcd.clear(); 
        lcd.setCursor(0, 0); 
        lcd.print("Password correct!"); 
        lcd.setCursor(0, 1); 
        lcd.print("Unlocking..."); 
        unlock(); 
        beep(); 
      } else { 
        lcd.clear(); 
        lcd.setCursor(0, 0); 
        lcd.print("Incorrect password"); 
        lcd.setCursor(0, 1); 
        lcd.print("Try again."); 
        alarm(); 
        delay(2000);  // Display the message for 2 seconds 
        lcd.clear(); 
        lcd.setCursor(0, 0); 
        lcd.print("Enter password:"); 
        resetPassword(); 
      } 
    } else { 
      // Append the pressed key to the entered password 
      appendPassword(key); 
      lcd.setCursor(0, 1); 
      lcd.print("Entered: "); 
      lcd.print(enteredPassword); 
    } 
  } 
} 
 
void unlock() { 
  myServo.write(0);  // move the servo to 0 degrees (unlock position) 
  delay(2000);  // keep the lock open for 2 seconds 
  myServo.write(90);  // return the servo to the locked position 
  delay(1000);  // Display the lock status for 1 second 
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Enter password:"); 
  resetPassword(); 
} 
 
void appendPassword(char key) { 
  if (strlen(enteredPassword) < 4) { 
    enteredPassword[strlen(enteredPassword)] = key; 
    enteredPassword[strlen(enteredPassword) + 1] = '\0';  // null terminator 
  } 
} 
 
void resetPassword() { 
  memset(enteredPassword, 0, sizeof(enteredPassword));  // clear the entered password 
} 
 
void beep() { 
  tone(buzzerPin, 1000, 200);  // play a 200ms beep for correct password 
} 
 
void alarm() { 
  tone(buzzerPin, 200, 1000);  // play a 1000ms alarm for incorrect password 
  delay(1000);  // additional delay to avoid overlap with LCD messages 
  noTone(buzzerPin);  // stop the buzzer 
} 