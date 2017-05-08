 //Written by Nick Hogan
// Date: 6th May 2017

#include <Wire.h>
#include <LCD.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>


// I2C Screen Config
#define I2C_ADDR 0x27

// I2C Screen Mapout (differs between models)
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

// Initialize the screen
LiquidCrystal_I2C
lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);


// Map the keypad
char keys[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

char colPin[4] = {46,48,50,52};
char rowPin[4] = {53,47,51,49};

Keypad keypad=Keypad(makeKeymap(keys),rowPin,colPin,4,4);

// Relay pinout
#define Sw_pin 11

// Code entry
String code;
String entry;


void setup() {
  
  // Setup LCD
  lcd.begin(16,2);
  
  // Setup GPIO Relay
  pinMode(Sw_pin, OUTPUT);
  digitalWrite(Sw_pin, 0);
  
  // Define an entry pin
  code = "14";
  
}


void loop() {
  
  // Set a message
  lcd.setCursor(0,0);
  lcd.print("ENTER CODE");
  lcd.setCursor(0,1);
 
  // When a button is pressed
  char pressed=keypad.getKey();

  // When the keypad is active
  if (pressed){

    // Check the active character
    if (pressed == '*') {
      // Active the lock...
 
      // Allow or deny access
      if (entry == code) {

       // Access Granted
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("SOLVED");
       
       // Open the door
       digitalWrite(Sw_pin, 1);
       
       // Reset
       delay(5000);
       digitalWrite(Sw_pin, 0);
       lcd.clear();
       entry = "";
       
      } else {
        
        // Access Denied 
        lcd.clear();
        entry = "";  // Clear any entered digits
      
      }
    
    // Lock was not activated
    } else {
      
      // Add a digit to the code sequence
      
      // Add a digit to the entry field
      entry.concat(pressed);
        
      // Print each number on the screen
      lcd.setCursor(0,1);
      lcd.print(entry);
      
    }
  }
}
