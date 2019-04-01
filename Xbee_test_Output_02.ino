
/* Input-side (button) Arduino code */
#include "SoftwareSerial.h"
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
SoftwareSerial XBee(2, 3);
int BUTTON = 8;

void setup()
{
  // Baud rate MUST match XBee settings (as set in XCTU)
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
  XBee.begin(9600);
}

void loop()
{

 send_data();
}

void send_data(){
  
   if (Serial.available() > 0) {
    char data = Serial.read();
    Serial.print(data);
    XBee.write('H');
    
    delay(50);
    

  }
  
  
  }

