#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
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
byte cccount = 0;
bool statee = false;
byte address  = 0;
uint8_t id = 0;
byte count = 0;
int getFingerprintIDez();
bool state = false;
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()
{
  //EEPROM.write(address,0);
  //EEPROM.write(address1,202);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  Serial.begin(9600);
  Serial.println("Adafruit finger detect test");
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Waiting for valid finger...");
}

void loop()
{
  if (digitalRead(4) == HIGH)
  {
    digitalWrite(13, 1);
    delay(250);
    cccount += 1;
    digitalWrite(13, 0);
  }
  if (cccount == 1) {
    if (button() == EEPROM.read(address1)) {
      Serial.print("Enroll ID # "); Serial.println(EEPROM.read(address));
      delay(50);
      getFingerprintEnroll();
    }

  }
  if (cccount > 1) {
    cccount = 0;
  }
  if (digitalRead(5) == HIGH) {
    digitalWrite(13, 1);
    delay(100);
    digitalWrite(13, 0);
    count += 1;
    state = true;
    delay(150);
    //Serial.println(state);
  }
  if (count == 1 && state) {
    Serial.println("Place the finger you want delete...");
    delay(150);
    if (getFingerprintIDez() != -1) {
      deleteFingerprint(finger.fingerID);
    }
  }

  if (getFingerprintIDez() != -1) {
    digitalWrite(11, HIGH);
    delay(1000);
    digitalWrite(11, LOW);
  }
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

  if (digitalRead(6) == HIGH) {
    delay(250);
    ccount += 1;
    Serial.println("Button Triggered");
  }
  if (ccount == 1) {
    digitalWrite(0, LOW);
    if (button() == EEPROM.read(address1)) {
      digitalWrite(12, HIGH);
      Serial.println("Fingerprint by passed");
      ccount -= 1;
      digitalWrite(0, HIGH);
    }
  }
  if (ccount > 1) {
    ccount = 0;
  }
  delay(50);
}

uint8_t getFingerprintEnroll() {
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(EEPROM.read(address));
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Finger Already Found");
    goto add;
  }


  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(EEPROM.read(address));
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  Serial.print("Creating model for #");  Serial.println(EEPROM.read(address));

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  Serial.print("ID "); Serial.println(EEPROM.read(address));
  p = finger.storeModel(EEPROM.read(address));
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
    EEPROM.update(address, ++id);
    Serial.println(EEPROM.read(address));
    digitalWrite(12, 1);
    delay(2500);
    digitalWrite(12, 0);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
add: int a = 0;
    return p;
  }
}
uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;

  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
    count = 0;
    EEPROM.update(address, id--);
    Serial.println(EEPROM.read(address));
    digitalWrite(12, 1);
    delay(1000);
    digitalWrite(12, 0);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }
}
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();

  if (p != FINGERPRINT_OK) {
    Serial.println("Finger Not Found");
    state = false;
    count = 0;
    return -1;
  }
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
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
      //br -= 1;
    }
  }
}
