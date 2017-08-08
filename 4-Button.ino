#include<EEPROM.h>
int data[] = {0, 0, 0, 0};
String data1 = "";
int data2 = 0;
byte count1 = 0;
byte count2 = 0;
byte count3 = 0;
byte count4 = 0;
byte br = 0;
bool b1 = false;
bool b2 = false;
bool b3 = false;
bool b4 = false;
byte address1 = 1;
int ccount = 0;
bool statee = false;
bool sstate = false;
void setup()
{
  //EEPROM.write(address1,202);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
}
void loop()
{
  if (digitalRead(4) == HIGH && digitalRead(5) == HIGH) {
    delay(500);
    Serial.println("By pass on");
    br += 1;

  }
  if (br == 1) {
    digitalWrite(13, HIGH);
    buttonUpdate();

  }
  if (br == 2)
  {
    digitalWrite(13, LOW);
    Serial.println("By pass off");
  }
  if (br >= 2) {
    br = 0;
  }

  if (digitalRead(4) == HIGH) {
    delay(250);
    ccount += 1;
    Serial.println("Button Triggered");
  }
  if (ccount == 1) {
    if (button() == EEPROM.read(address1)) {
      digitalWrite(12, HIGH);
      Serial.println("Fingerprint by passed");
      ccount -= 1;
    }
  }
  if (ccount > 1) {
    ccount = 0;
  }
}
int button() {
  int a = 0;
  if (digitalRead(8) == HIGH)
  {
    delay(250);
    b1 = true;
    Serial.println("Button - 1");
    count1 += 1;
    if (count1 == 1) {
      data[0] = 1;
    }
    if (count1 == 2) {
      data[0] = 0;
    }
    if (count1 >= 2) {
      count1 = 0;
    }
  }
  if (digitalRead(9) == HIGH)
  {
    delay(250);
    b2 = true;
    Serial.println("Button - 2");
    count2 += 1;
    if (count2 == 1) {
      data[1] = 1;
    }
    if (count2 == 2) {
      data[1] = 0;
    }
    if (count2 >= 2) {
      count2 = 0;
    }
  }
  if (digitalRead(10) == HIGH)
  {
    delay(250);
    b3 = true;
    Serial.println("Button - 3");
    count3 += 1;
    if (count3 == 1) {
      data[2] = 1;
    }
    if (count3 == 2) {
      data[2] = 0;
    }
    if (count3 >= 2) {
      count3 = 0;
    }
  }
  if (digitalRead(11) == HIGH)
  {
    delay(250);
    b4 = true;
    Serial.println("Button - 4");
    count4 += 1;
    if (count4 == 1) {
      data[3] = 1;
    }
    if (count4 == 2) {
      data[3] = 0;
    }
    if (count4 >= 2) {
      count4 = 0;
    }

  }
  if (b1 && b2 && b3 && b4) {

    data1 += String(data[0]) + String(data[1]) + String(data[2]) + String(data[3]);
    Serial.print("Binary Data : ");
    Serial.println(data1);
    data2 = data1.toInt();
    Serial.print("Encoded Data : ");
    a = String(data2, 16).toInt();
    Serial.println(a);
    if (a >= 256) {
      a -= 255;
    }
    Serial.print("Byte Value : ");
    Serial.println(a);
    data1 = "";
    b1 = false;
    b2 = false;
    b3 = false;
    b4 = false;
    count1 = 0;
    count2 = 0;
    count3 = 0;
    count4 = 0;
  }
  return a;
}
int buttonUpdate() {

ep: int b = 0;
  if (digitalRead(8) == HIGH)
  {
    delay(250);
    b1 = true;
    Serial.println("Button - 1");
    count1 += 1;
    if (count1 == 1) {
      data[0] = 1;
    }
    if (count1 == 2) {
      data[0] = 0;
    }
    if (count1 >= 2) {
      count1 = 0;
    }
  }
  if (digitalRead(9) == HIGH)
  {
    delay(250);
    b2 = true;
    Serial.println("Button - 2");
    count2 += 1;
    if (count2 == 1) {
      data[1] = 1;
    }
    if (count2 == 2) {
      data[1] = 0;
    }
    if (count2 >= 2) {
      count2 = 0;
    }
  }
  if (digitalRead(10) == HIGH)
  {
    delay(250);
    b3 = true;
    Serial.println("Button - 3");
    count3 += 1;
    if (count3 == 1) {
      data[2] = 1;
    }
    if (count3 == 2) {
      data[2] = 0;
    }
    if (count3 >= 2) {
      count3 = 0;
    }
  }
  if (digitalRead(11) == HIGH)
  {
    delay(250);
    b4 = true;
    Serial.println("Button - 4");
    count4 += 1;
    if (count4 == 1) {
      data[3] = 1;
    }
    if (count4 == 2) {
      data[3] = 0;
    }
    if (count4 >= 2) {
      count4 = 0;
    }

  }
  if (b1 && b2 && b3 && b4) {
    data1 += String(data[0]) + String(data[1]) + String(data[2]) + String(data[3]);
    Serial.print("Binary Data : ");
    Serial.println(data1);
    data2 = data1.toInt();
    Serial.print("Encoded Data : ");
    int a = String(data2, 16).toInt();
    Serial.println(a);
    if (a >= 256) {
      a -= 255;
    }
    data1 = "";
    b1 = false;
    b2 = false;
    b3 = false;
    b4 = false;
    count1 = 0;
    count2 = 0;
    count3 = 0;
    count4 = 0;
    Serial.print("Byte Value : ");
    Serial.println(a);
    if (a == EEPROM.read(address1)) {
      Serial.println("EEPROM Update");
      statee = true;
      goto ep;
    }
    if (statee) {
      EEPROM.update(address1, a);
      Serial.print("EEPROM Data : ");
      Serial.println(EEPROM.read(address1));
      Serial.println("EEPROM Updated");
      statee = false;
      br -= 1;
    }
  }
}
