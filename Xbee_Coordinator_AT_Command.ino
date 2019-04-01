int led = 13;

void setup (){

pinMode (led, OUTPUT);
Serial.begin(9600);
}

void loop (){
digitalWrite(led, HIGH); //turn the LED on
setRemoteState(0x5);
delay(7000);
Serial.println("HIGH");
digitalWrite (led,LOW);//turn off led
setRemoteState (0x4);
delay (7000);
Serial.println("LOW");

}

void setRemoteState(char value){
Serial.write (0X7E);            //11 start byte
Serial .write ( (byte) 0x0);     // high part of length (aluays zero)
Serial.write (0x10);            //low part of length (the number of bytes that follou, not including chec
Serial.write (0x17 );           //0x17 is a renote AT comnand
Serial.write ( (byte) 0x0);     // frame id set to zero for no reply  

//ID of recipient, or use 0xFFFF fo broadcast
//Serial.write ((byte) 0x0);
Serial.write((byte) 0x0);
Serial.write((byte) 0x0);
Serial.write((byte) 0x0);
Serial.write((byte) 0x0);
Serial.write((byte) 0x0);
Serial.write((byte) 0x0);
Serial.write (0xFF);//70xFF tor broadcast
Serial. write (0xFF); // 0xFf o brosdcast


//16 bit recipient or 0*FFFF if unknown

Serial.write(0XFF);
Serial.write(0XFE) ;

Serial.write(0x02); // 0x02 to apply changes iamediately on remote
//command name in ASCII characters
Serial.write('D');
Serial.write('3');



//command data in as many bytes as needed
Serial.write (value);
//check3um is all bytes after length bytes
long sum=0x17 +0XFF + 0XFF + 0XFF +0XFE + 0x02 +'D'+'3' +value;
Serial.write( 0xFF- (sum&0XFF));


}
