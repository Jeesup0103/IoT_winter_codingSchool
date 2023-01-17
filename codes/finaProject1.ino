#include <DHT11.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define pinLight A0
#define pin D2
#define buzzer D5
#define redLED D8
#define bluLED D11
#define leftSwitch D12
int i,j;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
DHT11 dht11(pin);

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "iot-group2-4c96f-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "719CWShP5rxzPuCcsU6hj3NZUzjM7oauOpEdEAAL"
#define WIFI_SSID "" // 연결 가능한 wifi의 ssid
#define WIFI_PASSWORD "" // wifi 비밀번호

FirebaseData firebaseData;
FirebaseJson json;
 
void printResult(FirebaseData &data);

void setup()
{
  lcd.begin();
  lcd.backlight();
  pinMode(redLED,OUTPUT);
  pinMode(bluLED,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(leftSwitch,INPUT);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
  firebaseData.setBSSLBufferSize(1024, 1024);
  firebaseData.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

void alertBuzzer(){
  for(i=0;i<10;i++){
    for(j=0;j<3;j++){
      digitalWrite(redLED,HIGH);
      digitalWrite(bluLED,LOW);
      tone(buzzer,300);
      delay(150);
      digitalWrite(redLED,LOW);
      digitalWrite(bluLED,LOW);
      noTone(buzzer);
      delay(150);
    }
    delay(200);
  }
}

void alertNoBuzzer(){
  for(i=0;i<10;i++){
    for(j=0;j<3;j++){
      digitalWrite(redLED,HIGH);
      digitalWrite(bluLED,LOW);
      delay(150);
      digitalWrite(redLED,LOW);
      digitalWrite(bluLED,LOW);
      delay(150);
    }
    delay(200);
  }
}

void loop()
{
  int err;
  float temp,humi;
  if((err=dht11.read(humi,temp))==0)
  {
    //Firebase temp, humi send
    Firebase.setFloat(firebaseData, "temp", temp);
    Firebase.setFloat(firebaseData, "humi", humi);
    if(temp>=25&&humi>=70){
      lcd.setCursor(0,0);
      lcd.print("    ");
      lcd.setCursor(4,0);
      lcd.print("Beware of");
      lcd.setCursor(0,1);
      lcd.print("      ");
      lcd.setCursor(6,1);
      lcd.print("Bugs!");
      lcd.setCursor(11,1);
      lcd.print("  ");
      //Firebase BugNote send
      Firebase.setString(firebaseData, "BUGNOTE", "Beware of Bugs!");
    }
    else{
      lcd.setCursor(3,0);
      lcd.print("Temp:");
      lcd.setCursor(8,0);
      lcd.print(temp);
      lcd.setCursor(3,1);
      lcd.print("Humi:");
      lcd.setCursor(8,1);
      lcd.print(humi);
    }
  }
  delay(DHT11_RETRY_DELAY);

//----------벌레 출현 시 (왼쪽 버튼 클릭) 알람 반응----------

  digitalWrite(redLED, LOW);
  digitalWrite(bluLED, HIGH);

  int light=analogRead(pinLight);
  int readSwitch=digitalRead(leftSwitch);

  if(light<=900){
    if(readSwitch==LOW){
      //Firebase Bug send
      Firebase.setString(firebaseData, "BUG", "ON");
      alertBuzzer();
    }
  }
  else{
    //Firebase bug send
    if(readSwitch==LOW){
      Firebase.setString(firebaseData, "BUG", "ON");
      alertNoBuzzer();
    }
  }
}
