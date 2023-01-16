#include "FirebaseESP8266.h" // 반드시 파이어베이스 라이브러리를 먼저 추가해야 합니다.
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "my-iot-1-14c79-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "c8Gi4AnVGqTfNR0pt6myY1zo2EPFo4qs9o289HyY"
#define WIFI_SSID "iot" // 연결 가능한 wifi의 ssid
#define WIFI_PASSWORD "15151515" // wifi 비밀번호

#define redLED D4
#define blueLED D7
#define lightSensor A0
#define buzzer D8
#define switch1 D2
#define switch2 D3

FirebaseData firebaseData;
FirebaseJson json;

void printResult(FirebaseData &data);

void setup() {
  
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
  firebaseData.setBSSLBufferSize(1024, 1024);
  firebaseData.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

void alert(){
  int repeatNum = 10;
  for(int j = 0; j < repeatNum; j++){
    for(int i = 0; i < 3; i++){
      digitalWrite(redLED, HIGH);
      tone(buzzer, 261);
      delay(100);
      digitalWrite(redLED, LOW);
      tone(buzzer, 0);
      delay(100);
    }
    delay(200);
  }
}

void alertNoBuzzer(){
  int repeatNum = 10;
  for(int j = 0; j < repeatNum; j++){
    for(int i = 0; i < 3; i++){
      digitalWrite(redLED, HIGH);
      delay(100);
      digitalWrite(redLED, LOW);
      delay(100);
    }
    delay(200);
  }
}

void loop() {
  digitalWrite(blueLED, HIGH);
  digitalWrite(redLED, LOW);
  int light = analogRead(lightSensor);
  int readSwitch = digitalRead(switch1);
 
  if(light <= 800){ //밝다 파랑색 켜짐
    //if 벌레 감지 == 스위치
    if(readSwitch == LOW){
      //핸드폰 알림
      Firebase.setString(firebaseData, "BUG", "ON");
      digitalWrite(blueLED, LOW);
      //빨간 LED 알림 + buzzer + 파랑색 꺼짐
      alert();
    }
  }
  else { //어둡다
    //if 벌레 감지 == 스위치
    if(readSwitch == LOW){
      Firebase.setString(firebaseData, "BUG", "ON");
      //빨간색 깜빡 3번 + 파랑색 꺼짐
      digitalWrite(blueLED, LOW);
      alertNoBuzzer();
    }
  }
}
