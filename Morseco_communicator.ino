// ArduinoJson - Version: 5.13.5
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

/*
1 space = separation between letter
2 space = separation between word
3 space = send/ translate message
*/

// include the library code: 
#include "Translator.h"
#include "Melody.h"
#include <LiquidCrystal.h> 
#include "FTDebouncer.h"

#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
#include <RTCZero.h>
#include<WiFiSSLClient.h>
#include <TelegramBot.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
const char BotToken[] = SECRET_BOT_TOKEN; // you bot API token

int keyIndex = 0;                           // your network key Index number (needed only for WEP)

RTCZero rtc;
WiFiSSLClient client;
TelegramBot bot (BotToken, client);

unsigned long timer;

FTDebouncer buttonDebouncer(5);

//LCD configuration
const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

#define buzzerPin 1

// RGB LED pins
const int redPin = 6;
const int greenPin = 8;
const int bluePin = 7;
const int dotPin=14;
const int dashPin=13;
const int spacePin=10;

//Initialize encoder input and output
String e_input;
String e_output;

//Initialize decoder input and output
String d_input;
String d_output;

int lcd_flag = 0;
// flag 0 = reset second row for new morse code letter
// flag 1 = print out morse code as type in second row
int lcd_pointer = 0;
int unit_delay = 500;


int status = WL_IDLE_STATUS;

const int GMT = 1; //change this to adapt it to your time zone

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  //set up led and buzzer pin
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  buttonDebouncer.addPin(dotPin, LOW);
	buttonDebouncer.addPin(dashPin, LOW);
	buttonDebouncer.addPin(spacePin, LOW);
  buttonDebouncer.init();
  //LCD setup
  analogWrite(A3, 0); // Set the brightness to its maximum value 
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2); 
  
  // check if the WiFi module works
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the status:
  printWiFiStatus();

  rtc.begin();

  unsigned long epoch;
  int numberOfTries = 0, maxTries = 8;
  do {
    epoch = WiFi.getTime();
    numberOfTries++;
  }
  while ((epoch == 0) && (numberOfTries < maxTries));

  if (numberOfTries == maxTries) {
    Serial.print("NTP unreachable!!");
    while (1);
  }
  else {
    Serial.print("Epoch received: ");
    Serial.println(epoch);
    rtc.setEpoch(epoch);

    Serial.println();
  }
  play_jingle();
  bot.begin();
}

// the loop routine runs over and over again forever:
void loop() {
  buttonDebouncer.update();
  
  //printDate();
  //printTime();
  updateDisplay();
  
  //Encoding 
  while (Serial.available())
  {
    //get the text to be encoded from serial input
    e_input = Serial.readString();
    Serial.println("Type in the text sentence to translatee to Morse:");
    Serial.println(e_input);
    // encoded the text
    e_output = string2Morse(e_input);
    // print out the value you read:
    morseResponse(e_output);
    Serial.println("\n");
    delay(1);        // delay in between reads for stability
  }
   
}

void onPinActivated(int pinNr){
	if(pinNr == dotPin)      // If button 1 pressed
  {
    d_input.concat(".");
    lcd.setCursor(lcd_pointer, 1);
    lcd.print(".");
    lcd_pointer++;
  }

  if(pinNr == dashPin)      // If button 2 pressed
  {
     
    d_input.concat("-");
    lcd.setCursor(lcd_pointer, 1);
    lcd.print("-");
    lcd_pointer++;
  }

  if(pinNr==spacePin)      // If button 3 pressed
  {
    //check the amount of space in the store string, if end with one space means 
    //
    Serial.println(d_input);
    lcd.setCursor(lcd_pointer, 1);
    lcd.print(" ");
    lcd_pointer++;
    //if it is about to have 3 space pressed, which ends a sentence
    if (d_input.endsWith("  ")){
      d_output = morseDecoder(d_input);//decode d_input and send message
      Serial.println("The translated code is:");
      Serial.println(d_output);
      d_input = "";}
    else{
      d_input.concat(" ");
      //lcd_pointer++;
    }
    if (lcd_pointer>=10){
      lcd.setCursor(0, 1);
      lcd_pointer = 0;
      lcd.print("                ");
    } 
  }
	Serial.println(pinNr);
}

void onPinDeactivated(int pinNr){
	
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


void printTime()
{
  print2digits(rtc.getHours() + GMT);
  Serial.print(":");
  print2digits(rtc.getMinutes());
  Serial.print(":");
  print2digits(rtc.getSeconds());
  Serial.println();
}

void printDate()
{
  Serial.print(rtc.getDay());
  Serial.print("/");
  Serial.print(rtc.getMonth());
  Serial.print("/");
  Serial.print(rtc.getYear());

  Serial.print(" ");
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void print2digits(int number) {
  if (number < 10) {
    Serial.print("0");
  }
  Serial.print(number);
}
void print2digitslcd(int number) {
  if (number < 10) {
    lcd.print("0");
  }
  lcd.print(number);
}

void updateDisplay(){
  int d = rtc.getDay();
  int mo = rtc.getMonth();
  int y = rtc.getYear();
  lcd.setCursor(0, 0); // Set the cursor at the column zero, upper row...
  print2digitslcd(d);   // Display the current hour
  lcd.setCursor(2, 0); // Move to the next column
  lcd.print("/");  // And print the colon
  lcd.setCursor(3, 0); // Move to the next column
  print2digitslcd(mo);   // Display the current minute
  
 
  int h = rtc.getHours() + GMT; // Get the hours right now and store them in an integer called h
  int m = rtc.getMinutes(); // Get the minutes right now and store them in an integer called m
  int s = rtc.getSeconds(); // Get the seconds right now and store them in an integer called s
  lcd.setCursor(7, 0); // Set the cursor at the column zero, upper row...
  print2digitslcd(h);   // Display the current hour
  lcd.setCursor(9, 0); // Move to the next column
  lcd.print(":");  // And print the colon
  lcd.setCursor(10, 0); // Move to the next column
  print2digitslcd(m);   // Display the current minute
  lcd.setCursor(12, 0); // Move to the next column
  lcd.print(":");  // And print the colon
  lcd.setCursor(13, 0); // Move to the next column
  print2digitslcd(s);   // Display the current second
 
}

