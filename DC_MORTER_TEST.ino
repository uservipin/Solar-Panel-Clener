int DC_01=22;
int DC_02=23;
int DC_PWM=24;

void setup() {
  // put your setup code here, to run once:
pinMode(DC_01,OUTPUT);
pinMode(DC_02,OUTPUT);
pinMode(DC_PWM,OUTPUT);
Serial.begin(9600);
}

void loop() {
//  froward();
  backward();
  // put your main code here, to run repeatedly:

}

void froward(){
digitalWrite(DC_01,HIGH);
digitalWrite(DC_02,LOW); 
analogWrite(DC_PWM,255) ;
delay(1000);
}

void backward(){
digitalWrite(DC_01,LOW);
digitalWrite(DC_02,HIGH);
analogWrite(DC_PWM,255) ; 
//delay(1000);
}
