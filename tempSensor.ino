int sensor = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float adcVal = analogRead(sensor);
  float temp = adcVal*330/1024 -50;
  Serial.println(temp);
  delay(100);

  
}
