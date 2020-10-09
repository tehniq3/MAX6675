// this example is public domain. enjoy!
// https://learn.adafruit.com/thermocouple/
// add thermostat function with potentiometer adjust by Nicu FLORICA (niq_ro) - Craiova, 7-Oct-2020
// changed value for 100..450 degree Celsius instead 0..250 degree Celsius, see lines 77,78

#include <max6675.h> // https://github.com/adafruit/MAX6675-library
#include <LiquidCrystal.h>
#include <Wire.h>

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// make a cute degree symbol
uint8_t degree[8]  = {140,146,146,140,128,128,128,128};

#define pincursor A0
float temperatura;
float temperaturadorita;
float histerezis = 2.5;
#define pinreleu 3

#define atras HIGH
#define repaus LOW

/*
#define atras LOW
#define repaus HIGH 
*/


void setup() {
  Serial.begin(9600);
  pinMode(pinreleu, OUTPUT);   // use Arduino pins 
  digitalWrite(pinreleu, repaus);
  
  lcd.begin(16, 2);
  lcd.createChar(0, degree);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Thermostat   ");
  lcd.setCursor(0, 0);
  lcd.print("  with MAX6675  ");  
  delay(3000);  // wait 
  lcd.clear();
   if (temperatura > temperaturadorita)
   {
    digitalWrite(pinreleu, repaus);
    lcd.setCursor(11,0);  
    lcd.print("Relay");
    lcd.setCursor(11,0);  
    lcd.print(" OFF ");   
   }
   else
   {
    digitalWrite(pinreleu, atras);
    lcd.setCursor(11,0);  
    lcd.print("Relay");
    lcd.setCursor(11,0);  
    lcd.print(" ON  ");   
   }
}

void loop() {
  temperatura = thermocouple.readCelsius();
  lcd.setCursor(1,0); 
  if (temperatura < 100) lcd.print(" ");
  if (temperatura < 10) lcd.print(" ");  
  lcd.print(temperatura,1);
  lcd.write((byte)0);
  lcd.print("C ");

 temperaturadorita = map(analogRead(pincursor), 0, 255, 200, 450); // map(value, fromLow, fromHigh, toLow, toHigh)
 // https://www.arduino.cc/reference/en/language/functions/math/map/
  
  lcd.setCursor(0,1);  
  lcd.print("[");
  if (temperaturadorita < 100) lcd.print(" ");
  if (temperaturadorita < 10) lcd.print(" ");  
  lcd.print(temperaturadorita,1);
  lcd.write((byte)0);
  lcd.print("C]");

 if (temperatura > temperaturadorita)
 {
    digitalWrite(pinreleu, repaus);
    lcd.setCursor(11,0);  
    lcd.print("Relay");
    lcd.setCursor(11,0);  
    lcd.print(" OFF ");   
 }
 if (temperatura < temperaturadorita - histerezis)
 {
    digitalWrite(pinreleu, atras);
    lcd.setCursor(11,0);  
    lcd.print("Relay");
    lcd.setCursor(11,0);  
    lcd.print(" ON  ");   
 }
  
  delay(1000);
}
