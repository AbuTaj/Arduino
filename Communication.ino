#include <SoftwareSerial.h>//Serial communication header
SoftwareSerial a(6, 7); // RX | TX
void setup()
{ 
  Serial.begin(9600);//begin serial monitor with 9600 baud
  Serial.println("Type message");
  a.begin(38400);  // HC-05 default baud
}
void loop()
{
  if (a.available())
    Serial.write(a.read());//reads data from BT
  if (Serial.available())
    a.write(Serial.read());//reads data from serial monitor
}
