String ph1="75******92"; //Enter your phone number to call #01
String ph2="89******25";   //Enter your phone number to call #02
int inputPin = 8;
int val=0;
bool flag=false;
void setup() {
Serial.begin(9600);
Serial.print("AT+CMGF=1\r\n"); //Text SMS mode in GSM
pinMode(inputPin, INPUT);
digitalWrite(inputPin,LOW);
//System Calibration
for(int i=0;i<10;i++)
{
  delay(1000);
}
}
void loop(){   
val = digitalRead(inputPin); 
if (val == HIGH) {
  flag=true;
  digitalWrite(inputPin,LOW);
}
else if(val==LOW) {
  digitalWrite(inputPin,HIGH);
}
if (flag) {
  message1();    //Generate the Alert Message First Mobile
  delay(1000);
  message2();   //Generate the Alert Message Second Mobile
  delay(60000); //1 minute delay
  call1();      //Call to First mobile
  delay(1000);
  call2();      //call to Second mobile
  }
  flag=false;
 }
void message1()  //Method to send message #01
{
    Serial.print("AT+CMGS=\"");
    Serial.print(ph1);
    Serial.print("\"\r\n");
    delay(2000);
    Serial.print("---ALERT---\n Human Trace Detected");
    Serial.write(0x1A);
}
void message2()   //Method to send message #02
{
    Serial.print("AT+CMGS=\"");
    Serial.print(ph2);
    Serial.print("\"\r\n");
    delay(2000);
    Serial.print("---ALERT---\n Human Trace Detected");
    Serial.write(0x1A);
}
void call1()   //Method to get call #01
{
  Serial.print("ATD");
  Serial.print(ph1);
  Serial.print(";\r\n");
  delay(15000);
  Serial.println("ATH");
}
void call2()   //Method to get call #02
{
  Serial.print("ATD");
  Serial.print(ph2);
  Serial.print(";\r\n");
  delay(15000);
  Serial.println("ATH");
}
