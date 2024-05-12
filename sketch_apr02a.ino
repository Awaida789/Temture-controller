#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
int val=0;
int pot=A0;
float cel;
// Define keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal_I2C lcd(0x27, 16, 2); 
#define RELAY1_PIN 12
#define RELAY2_PIN 11
float setpoint = 100.0; 
void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.backlight();
  lcd.clear();
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("Setpoint: ");
  lcd.print(cel);
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
}
void loop() {
  
char key = keypad.getKey();
   val=analogRead(pot);
 float myval=(val/1024.0)*5000;
 float cel=myval/10;
 Serial.print("Tempture= ");
 Serial.print(cel);
 Serial.print(" c");
 Serial.println();
 delay(200);
  // Check for keypad input
  if (key != NO_KEY) {
    if (key == '#') {
      // Increase setpoint
      setpoint += 1.0;
      lcd.setCursor(10, 1);
      lcd.print("    "); // Clear previous setpoint
      lcd.setCursor(10, 1);
      lcd.print(setpoint);
    } else if (key == '*') {
      // Decrease setpoint
      setpoint -= 1.0;
      lcd.setCursor(10, 1);
      lcd.print("    "); // Clear previous setpoint
      lcd.setCursor(10, 1);
      lcd.print(setpoint);
    }
  }

  // Read temperature
  
  
  // Display temperature
  lcd.setCursor(6, 0);
  lcd.print("    "); // Clear previous temperature
  lcd.setCursor(6, 0);
  lcd.print(cel);
  lcd.print(" C  ");
if (key == 'D') {
  // Control relays based on temperature
  if ( setpoint > cel) {
    digitalWrite(RELAY1_PIN, HIGH);
    digitalWrite(RELAY2_PIN, LOW);
  } else {
    digitalWrite(RELAY1_PIN, LOW);
    digitalWrite(RELAY2_PIN, HIGH);
  }}

  delay(200); // Delay for stability
}
