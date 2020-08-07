/*

*/
// include the library code: 
#include "Encoder.h"
#include <LiquidCrystal.h> 

const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

#define buzzerPin 1

// RGB LED pins
const int redPin = 6;
const int greenPin = 8;
const int bluePin = 7;
const int dotButton=14;
const int dashButton=13;
const int spaceButton=10;

//Initialize encoder input and output
String e_input;
String e_output;

//Initialize decoder input and output
String d_input;
String d_output

int unit_delay = 500;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  //set up led and buzzer pin
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(dotButton, INPUT);
  pinMode(dashButton, INPUT);
  pinMode(spaceButton, INPUT);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2); 
}

// the loop routine runs over and over again forever:
void loop() {
  while (Serial.available())
  {
    input = Serial.readString();
    Serial.println(e_input);
    output = string2Morse(e_input);
    Serial.println(e_output);
    // print out the value you read:
    morseResponse(e_output);
    Serial.println("\n");
    delay(1);        // delay in between reads for stability
  }
  if(digitalRead(dotButton) == HIGH)      // If button 1 pressed
  {
    Serial.println("Dot button pressed"); // Print "Button 1 pressed" on Serial Monitor
    d_input.concat(".");
  }

  if(digitalRead(dashButton) == HIGH)      // If button 2 pressed
  {
    Serial.println("Dash pressed"); // Print "Button 2 pressed" on Serial Monitor
    d_input.concat("-");
  }

  if(digitalRead(spaceButton) == HIGH)      // If button 3 pressed
  {
    Serial.println("Space pressed"); // Print "Button 3 pressed" on Serial Monitor
    d_input.concat(" ");
  }
    
}

void readButton(){
  buttonState = digitalRead(dotButton);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}

void morseResponse(String m_str){
  for (int i = 0; i <m_str.length(); i++){
    if (m_str.charAt(i) == '-'){
      dash();
    } else if (m_str.charAt(i) == '.'){
      dot();
    } else space();
  }
}

void dash() { 
  Serial.print("-");
  digitalWrite(redPin, HIGH);
  digitalWrite(buzzerPin, HIGH);
  delay(unit_delay * 3);
  digitalWrite(redPin, LOW);
  digitalWrite(buzzerPin, LOW);
  delay(unit_delay);
}
  
void dot() { 
  Serial.print("."); 
  digitalWrite(redPin, HIGH);
  digitalWrite(buzzerPin, HIGH);
  delay(unit_delay);
  digitalWrite(redPin, LOW);
  digitalWrite(buzzerPin, LOW);
  delay(unit_delay);
}

void space() { 
  Serial.print(" "); 
  delay(unit_delay *3);
}

