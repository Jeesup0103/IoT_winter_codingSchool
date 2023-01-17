#include "FirebaseESP8266.h" // 반드시 파이어베이스 라이브러리를 먼저 추가해야 합니다.
#include <ESP8266WiFi.h>
#define FIREBASE_HOST "https://guardko99-e2e63-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "gUVlZqPSn510tUYaFDKOOyLBzF12hSbI7rMGXyVW"
#define WIFI_SSID "guardko99's Galaxy S21 5G" // 연결 가능한 wifi의 ssid
#define WIFI_PASSWORD "guardko99" // wifi 비밀번호

FirebaseData firebaseData;
FirebaseJson json;

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

void printResult(FirebaseData &data);

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

void setup()
{
  Serial.begin(9600);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  pinMode(redLED, OUTPUT);
  pinMode(bluLED, OUTPUT);
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
  firebaseData.setBSSLBufferSize(1024, 1024);
  firebaseData.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  lcd.begin();
  lcd.backlight();
  pinMode(redLED,OUTPUT);
  pinMode(bluLED,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(leftSwitch,INPUT);
}

void loop(){
  int err;
  float temp,humi;
  String condition, warning;
  bool appear=false;
  
  if((err=dht11.read(humi,temp))==0){
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
      warning="Beware of Bugs!";
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
      warning="No Warning.";
    }
  }
  
  delay(DHT11_RETRY_DELAY);

  digitalWrite(redLED, LOW);
  digitalWrite(bluLED, HIGH);
  
  int light=analogRead(pinLight);
  int readSwitch=digitalRead(leftSwitch);
  
  if(light<=900){
    condition="Bright";
    if(readSwitch==LOW){
      appear=true;
      Firebase.setBool(firebaseData, "Whether bugs appear", appear);
      alertBuzzer();
    }
  }
  
  else{
    condition="Dark";
    if(readSwitch==LOW){
      appear=true;
      Firebase.setBool(firebaseData, "Whether bugs appear", appear);
      alertNoBuzzer();
      }
  }
  appear=false;
  Firebase.setBool(firebaseData, "Whether bugs appear", appear);

  Firebase.setInt(firebaseData, "Brightness", light);
  Firebase.setFloat(firebaseData, "Temperature", temp);
  Firebase.setFloat(firebaseData, "Humidity", humi);
  Firebase.setString(firebaseData, "Condition in the Room", condition);
  Firebase.setString(firebaseData, "Warning", warning);
 
  delay(1000); // 1초마다 반복
}
