#include "FirebaseESP8266.h" // 반드시 파이어베이스 라이브러리를 먼저 추가해야 합니다.
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "my-iot-1-14c79-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "c8Gi4AnVGqTfNR0pt6myY1zo2EPFo4qs9o289HyY"
#define WIFI_SSID "iot" // 연결 가능한 wifi의 ssid
#define WIFI_PASSWORD "15151515" // wifi 비밀번호

#define pinLED1 D4
#define pinLED2 D7
#define pinCDS  A0
 
FirebaseData firebaseData;
FirebaseJson json;
 
void printResult(FirebaseData &data);
void setup() // wifi 접속 과정.
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

  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
  firebaseData.setBSSLBufferSize(1024, 1024);
  firebaseData.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

void loop()
{
 if(Firebase.getString(firebaseData, "LED1")){
  String valStr = firebaseData.stringData();
  // write Code...
  if(valStr == "1") digitalWrite(pinLED1, HIGH);
  else digitalWrite(pinLED1, LOW);
 }
 /*
 if(Firebase.getBool(firebaseData,"LED1")) {
  bool valLED1 = firebaseData.boolData();
  digitalWrite(pinLED1, valLED1);
 }

 if(Firebase.getBool(firebaseData, "LED2")) {
  bool valLED2 = firebaseData.boolData();
  digitalWrite(pinLED2, valLED2);
 } 
 */
 

 
/* if(Firebase.getInt(firebaseData, "Int Data Tag")){
  int valInt = firebaseData.intData();
  // write Code...
 }
 if(Firebase.getFloat(firebaseData, "Float Data Tag")){
  float valFloat = firebaseData.floatData();
  // write Code...
 }
 if(Firebase.getString(firebaseData, "String Data Tag")){
  String valStr = firebaseData.stringData();
  // write Code...
 }*/

 

 //Firebase.setBool(firebaseData, "BoolData", /*Bool Data*/);
 Firebase.setInt(firebaseData, "Brightness", analogRead(pinCDS));
 //Firebase.setFloat(firebaseData, "FloatData", /*Float Data*/);
 Firebase.setString(firebaseData, "JSP", "HELLO");
 delay(1000); // 1초마다 반복
}
