/* 
 * Sound Detection AC lamp Sequencer
 * This program was written by AbuTaj
 * Electronics & Electrical Techy
 * https://electricaltechy.blogspot.in/
 * Like. Comment.. Share...
 * Serial Monitor is used for Identification purpose only. Not necessary in deployement
 */

int counter=0;
byte soundPin=6;
void setup() {
  pinMode(2,OUTPUT);  //Output Initialization  pin 2
  pinMode(3,OUTPUT);  //Output Initialization  pin 3
  pinMode(4,OUTPUT);  //Output Initialization  pin 4
  pinMode(5,OUTPUT);  //Output Initialization  pin 5
  pinMode(6,INPUT);   //Input Initialization  pin 6
  Serial.begin(9600); //Serial actions
  Serial.println("AC-Lamp Sequencer\n AbuTaj");
  delay(1000);        //System stability wait
}

void loop() {
  if(soundDetection()>1000)   //Input Detection
  {
    counter+=1;
    Serial.println("Input Detected");
    Serial.println(counter);
    }
    switch(counter)
    {
      case 1:
      digitalWrite(2,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      Serial.println("Run #01");
      break;
      case 2:
      digitalWrite(3,HIGH);
      digitalWrite(2,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      Serial.println("Run #02");
      break;
      case 3:
      digitalWrite(4,HIGH);
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(5,LOW);
      Serial.println("Run #03");
      break;
      case 4:
      digitalWrite(5,HIGH);
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      Serial.println("Run #04");
      break;
      case 5:{
      for(int i=0;i<11;i++){
        digitalWrite(2,HIGH);
        delay(250);
        digitalWrite(2,LOW);
        digitalWrite(3,HIGH);
        delay(250);
        digitalWrite(3,LOW);
        digitalWrite(4,HIGH);
        delay(250);
        digitalWrite(4,LOW);
        digitalWrite(5,HIGH);
        delay(250);
        digitalWrite(5,LOW);   
        delay(500);
        digitalWrite(5,HIGH);
        delay(125);
        digitalWrite(5,LOW);
        digitalWrite(4,HIGH);
        delay(125);
        digitalWrite(4,LOW);
        digitalWrite(3,HIGH);
        delay(125);
        digitalWrite(3,LOW);
        digitalWrite(2,HIGH);
        delay(125);
        digitalWrite(2,LOW); 
        Serial.println("Run #05");
        if(soundDetection()>1000){
        counter+=1;
        break;
        }
       }
      }
      break;
      default:
        digitalWrite(2,LOW);
        digitalWrite(3,LOW);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        Serial.println("All OFF");
    }
     if(counter>5)
     {
       counter=0;
     }
   }
  int soundDetection(){
  delay(25);
  int soundIn=pulseIn(soundPin,HIGH);  //wait for the pin to get HIGH and returns measurement
  return soundIn;
}
