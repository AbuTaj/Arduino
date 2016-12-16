void setup() {
  pinMode(13,OUTPUT);
  pinMode(12,INPUT);
  pinMode(11,OUTPUT);
  pinMode(10,INPUT);
  pinMode(9,OUTPUT);
  pinMode(8,INPUT);
  digitalWrite(13,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(9,HIGH);
}
void loop() {
  if(digitalRead(12)==HIGH)
  {
    Serial.print("LED #01 ON");
    }
    if(digitalRead(10)==HIGH)
  {
    Serial.print("LED #02 ON");
    }
    if(digitalRead(8)==HIGH)
  {
    Serial.print("LED #03 ON");
  }
  if(digitalRead(12)==LOW)
  {
    Serial.print("LED #01 OFF");
    }
    if(digitalRead(10)==LOW)
  {
    Serial.print("LED #02 OFF");
    }
    if(digitalRead(8)==LOW)
  {
    Serial.print("LED #03 OFF");
    }

}
