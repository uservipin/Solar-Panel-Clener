/* Output-side (LED) Arduino code */
#include "SoftwareSerial.h"
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
SoftwareSerial XBee(2, 3);
int LED = 9;

void setup()
{
  // Baud rate MUST match XBee settings (as set in XCTU)
  XBee.begin(9600);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}




void Xbee(){
 if (XBee.available())  
  { 
       Serial.println("hello inside xbee");


    char c = XBee.read();
    if (c == 'H')
    {
      digitalWrite(LED, HIGH);
      delay(500);
    }
    else
    {
      digitalWrite(LED, LOW);
    }
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  
}


void loop()
{
 Xbee();
// Serial.println("Hello World");
}


