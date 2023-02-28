#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define soilWet 500   
#define soilDry 750   
// Sensor pins
#define sensorPower 7
#define sensorPin A0
//Pump pin
#define pumpPin 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(sensorPower, OUTPUT);
  pinMode(pumpPin, OUTPUT); 
 
  digitalWrite(sensorPower, LOW);
  digitalWrite(pumpPin, HIGH);
  
  Serial.begin(9600);
  lcd.begin ();
  
}

void loop() {
  
  int moisture = readSensor();
  
  Serial.println(moisture);
 
  lcd.backlight();
  lcd.setCursor(0, 0);
 
  if (moisture < soilWet) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Soil is too wet");
    digitalWrite(pumpPin, HIGH);
    Serial.println("Status: Soil is too wet");
  } 
  else if (moisture >= soilWet && moisture < soilDry) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Soil moisture is");
    lcd.setCursor(4, 1);
    lcd.print("perfect");
    digitalWrite(pumpPin, HIGH);
    Serial.println("Soil moisture is perfect");
  } 
  else if(moisture > soilDry){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Soil is too dry ");
    lcd.setCursor(0, 1);
    lcd.print("Time to water!");
    Serial.println("Soil is too dry - time to water!");
    digitalWrite(pumpPin, LOW); 
  
  }
  
  delay(1000);  
  Serial.println();
}


int readSensor() {
  digitalWrite(sensorPower, HIGH); 
  delay(10);              
  int val = analogRead(sensorPin);  
  digitalWrite(sensorPower, LOW);   
  return val;             
}
