/*
Alarm Clock with Temperature and Humidity Measuring Feature

DONT USE THIS YET. DEVELOPMENT PHASE

*/
//Librarys
#include <Wire.h> // IIC-Bibliothek            
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <virtuabotixRTC.h> 

#define DHTTYPE DHT11

 
//CLK -> 9 , DAT -> 4, Reset -> 5
 
virtuabotixRTC zeit(9, 4, 5); 

LiquidCrystal_I2C lcd(0x3F,16,2); //maxi
//LiquidCrystal_I2C lcd(0x27,16,2); //lukas

int button1 = 3;
int button2 = 7;
int dhtpin = 8;
int piezo = 2;

int now_minutes;
int now_hours;

DHT dht(dhtpin, DHTTYPE);

String wake_at = "7:00";

bool alarm = false;

bool pressed = true;

void setup(void) {
  //zeit.setDS1302Time(15, 06, 10, 7, 13, 11, 2021); // Setze Zeit beim Setup. Entfernen nach Einstellung [Sekunden, Minuten, Stunden, Tage, Datumtag , Monat, Jahr]
  lcd.init();   
  lcd.backlight();
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(piezo, OUTPUT);
  Serial.begin(9600);
 
  dht.begin();

}

void loop() {
  if (digitalRead(button1) == HIGH){
    if (alarm == false){
      alarm = true;             
    }   
  }
  else {
    alarm = false;
  }
  

  if(alarm == true){
    lcd.setCursor(8,1);
    lcd.print("O");
    lcd.setCursor(6,0); 
  }

  else {
    lcd.setCursor(8,1);
    lcd.print("");
    lcd.setCursor(6,0); 
  }
  Serial.println(alarm);
  zeit.updateTime();
  now_minutes = zeit.minutes;
  now_hours = zeit.hours;

  String time_now = now_hours + ":" + now_minutes;
  Serial.println(time_now);
  delay(2000);
  
  if (digitalRead(button1) == HIGH){
    if (alarm == false){
      alarm = true;             
    }   
  }
  else {
    alarm = false;
  }

  if(alarm == true){
    lcd.setCursor(8,1);
    lcd.print("O");
    lcd.setCursor(6,0); 
  }

  else {
    lcd.setCursor(8,1);
    lcd.print("");
    lcd.setCursor(6,0); 
  }
  Serial.println(alarm);
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  lcd.setCursor(6,0); 

  if (now_hours < 10){
    lcd.print("0");
  }

  lcd.print(zeit.hours);
  lcd.print(":");
  if (now_minutes < 10){
    lcd.print("0");
  }
  lcd.print(zeit.minutes);
  lcd.setCursor(0,1);  
  lcd.print(String(t) + char(223) +"C         " + String(h) + "%");
}
