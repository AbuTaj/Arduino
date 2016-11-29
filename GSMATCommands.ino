#include <SoftwareSerial.h>
char ic_char=0; //Will hold the incoming character from the Serial Port.
SoftwareSerial gsm(10,11); //Create a 'fake' serial port. Pin 11 is the Rx pin, pin 10 is the Tx pin.
void setup()
{//Initialize serial ports for communication.
 Serial.begin(9600);
 gsm.begin(9600);
 Serial.println("Starting Serial Communication...");
}
 
void loop()
{
 //If a character comes in from the cellular module...
 if(gsm.available() >0)
 {
 ic_char=gsm.read();//Get the character from the cellular serial port.
 Serial.print(ic_char); //Print the incoming character to the terminal.
 }
 //If a character is coming from the terminal to the Arduino...
 if(Serial.available() >0)
 {
 ic_char=Serial.read(); //Get the character coming from the terminal
 gsm.print(ic_char); //Send the character to the cellular module.
 }
}
