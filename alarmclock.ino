#include <Wire.h>           
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <virtuabotixRTC.h> 

#define DHTTYPE DHT11

 
//CLK -> 9 , DAT -> 4, Reset -> 5
 
virtuabotixRTC zeit(9, 4, 5); 

LiquidCrystal_I2C lcd(0x3F,16,2); //maxi
//LiquidCrystal_I2C lcd(0x27,16,2); //lukas

int dhtpin = 8;

int now_minutes;
int now_hours;

DHT dht(dhtpin, DHTTYPE);

void setup(void) {
  //zeit.setDS1302Time(15, 51, 18, 7, 27, 10, 2021); // Setze Zeit beim Setup. Entfernen nach Einstellung
  lcd.init();   
  lcd.backlight();
  Serial.begin(9600);
 
  dht.begin();

}

void loop() {
  zeit.updateTime();
  now_minutes = zeit.minutes;
  now_hours = zeit.hours;

  String time_now = now_hours + ":" + now_minutes;
  Serial.println(time_now);
  delay(2000);
  
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
