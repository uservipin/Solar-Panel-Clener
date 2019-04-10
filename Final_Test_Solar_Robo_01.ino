//.........NOTE...NOTE......NOTE.......NOTE.......CASE OF ZERO DISTANCE IN ULTROSONIC SENSOR ,ROBOT WILL STOP...........NOTE......NOTE......NOTE.......NOTE....



// READ VALUES FROM ULTRASONIC SENSOR distance measued by ultrasonic sensor.

int check_distance = 7;
int front_Ultrasonic_Sensor_Distance;
int back_Ultrasonic_Sensor_Distance;

// defines pins numbers


//Pins for Cleaner Brush
int DC_01 = 22;
int DC_02 = 23;
int DC_PWM = 24;


//...............................Distance measured by UltraSonic sensor in CM (Centimeters)
//..................UltraSonic Sensor Pin
const int trigPin_Front_Sensor = 9;
const int echoPin_Front_Sensor = 10;
const int trigPin_Back_Sensor = 11;
const int echoPin_Back_Sensor = 12;

//  FIRST STEPPER MORTER CONFUGRATION             ............LEFT
const int dirPin = 2;
const int stepPin = 3;
const int enPin = 4;

// SECOND STEPPER MORTER CONFUGRATION            ............RIGHT
const int dirPin_02 = 5;
const int stepPin_02 = 6;
const int enPin_02 = 7;


//for stepper morter
int microsteps = 400;
int steps = 400;
// at end of panel first robot stop then move first 1000 steps (steps_for_end)
int steps_for_end = 1000;


// defines variables                                         ................................................WHY   WHY
long duration_front;
int distance_front;

long duration_back;
int distance_back;


void setup() {

  //.......................................... FRINT Ultrasonic Sensor



  // Setup for Brush
  pinMode(DC_01, OUTPUT);
  pinMode(DC_02, OUTPUT);
  pinMode(DC_PWM, OUTPUT);



  pinMode(trigPin_Front_Sensor, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_Front_Sensor, INPUT); // Sets the echoPin as an Input

  //............................................................. BACK Ultrasonic Sensor
  pinMode(trigPin_Back_Sensor, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_Back_Sensor, INPUT); // Sets the echoPin as an Input



  // .....................Set Stepper Morter  two pins as Outputs
  // first Stepper Morter
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
  //  Second Stepper morter
  pinMode(stepPin_02, OUTPUT);
  pinMode(dirPin_02, OUTPUT);
  pinMode(enPin_02, OUTPUT);
  digitalWrite(enPin_02, LOW);

  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  front_Ultrasonic_Sensor_Distance = front_Ultrasonic_Sensor();
  Serial.print("Distance FRONT : ");
  Serial.println(front_Ultrasonic_Sensor_Distance);

  back_Ultrasonic_Sensor_Distance = back_Ultrasonic_Sensor();
  Serial.print("Distance BACK : ");
  Serial.println(back_Ultrasonic_Sensor_Distance);



  //.NOTE...NOTE......NOTE.......NOTE.......CASE OF ZERO DISTANCE IN ULTROSONIC SENSOR ,ROBOT WILL STOP...........NOTE......NOTE......NOTE.......NOTE....
  if (front_Ultrasonic_Sensor_Distance == 0 || back_Ultrasonic_Sensor_Distance == 0) {       //...........................................CHECK............

    //  STOP
    Serial.println("Robo is Stop due to distance Zero read by atleast one ultrasonic sensor");
    stop_Robot();
  }

  if (  front_Ultrasonic_Sensor_Distance <= check_distance && back_Ultrasonic_Sensor_Distance <= check_distance  ) {
    Serial.println("inside move forword");
    forward_motion_of_morter();
  }

  if (front_Ultrasonic_Sensor_Distance <= check_distance && back_Ultrasonic_Sensor_Distance > check_distance) {
    stop_Robot();
    //    forward_motion_of_morter();
    forward_motion_of_morter_at_end_corner();
    int back_distance = move_forword();
    Serial.println("Back Distance");
    Serial.println(back_distance);
  }

  if (front_Ultrasonic_Sensor_Distance > check_distance && back_Ultrasonic_Sensor_Distance <= check_distance) {
    stop_Robot();
    //    back();
    back_at_end_corner();
    delay(300);
    int front_distance = move_backword();
    Serial.print("Front Distance  :");
    Serial.println(front_distance);
  }
}


int move_forword() {
  while (1) {
    Serial.println("Inside Move forword  01");

    front_Ultrasonic_Sensor_Distance = front_Ultrasonic_Sensor();
    Serial.print("Distance FRONT inside MOVE FORWORD : ");
    Serial.println(front_Ultrasonic_Sensor_Distance);

    back_Ultrasonic_Sensor_Distance = back_Ultrasonic_Sensor();
    Serial.print("Distance BACK  INSIDE MOVE FORWORD: ");
    Serial.println(back_Ultrasonic_Sensor_Distance);

    if (  front_Ultrasonic_Sensor_Distance <= check_distance && back_Ultrasonic_Sensor_Distance <= check_distance  ) {
      forward_motion_of_morter();
      Serial.println("Inside Move forword  02");

    }
    //    if (front_Ultrasonic_Sensor_Distance > check_distance) {
    //          Serial.println("Inside Move forword  03");
    //
    //      return  front_Ultrasonic_Sensor_Distance;
    //    }
    else {
      Serial.println("Inside Move forword  03");

      return  front_Ultrasonic_Sensor_Distance;


    }
  }
}

int move_backword() {
  while (1) {
    Serial.println("Inside Move backword  01");
    front_Ultrasonic_Sensor_Distance = front_Ultrasonic_Sensor();
    Serial.print("Distance FRONT inside MOVE FORWORD : ");
    Serial.println(front_Ultrasonic_Sensor_Distance);

    back_Ultrasonic_Sensor_Distance = back_Ultrasonic_Sensor();
    Serial.print("Distance BACK  INSIDE MOVE FORWORD: ");
    Serial.println(back_Ultrasonic_Sensor_Distance);

    if (  front_Ultrasonic_Sensor_Distance <= check_distance && back_Ultrasonic_Sensor_Distance <= check_distance  ) {
      Serial.println("Inside Move backword  02");

      back();
    }

    //    if (front_Ultrasonic_Sensor_Distance > check_distance) {
    //       Serial.println("Inside Move backword  03");
    //
    //      return front_Ultrasonic_Sensor_Distance;
    //    }
    
    else {
      return front_Ultrasonic_Sensor_Distance;
      Serial.println("Inside Move backword  03");
    }
  }
}


int front_Ultrasonic_Sensor() {
  // Clears the trigPin
  digitalWrite(trigPin_Front_Sensor, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_Front_Sensor, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_Front_Sensor, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_front = pulseIn(echoPin_Front_Sensor, HIGH);
  // Calculating the distance
  distance_front = duration_front * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //  Serial.print("Distance FRONT : ");
  //  Serial.println(distance_front);
  return distance_front;
}
int  back_Ultrasonic_Sensor() {
  // Clears the trigPin

  digitalWrite(trigPin_Back_Sensor, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_Back_Sensor, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_Back_Sensor, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_back = pulseIn(echoPin_Back_Sensor, HIGH);
  // Calculating the distance
  distance_back = duration_back * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //
  //  Serial.print("         Distance BACK : ");
  //  Serial.println(distance_back);
  return distance_back;
}

void forward_motion_of_morter() {
  digitalWrite(dirPin, HIGH);                            // FOR FIRST MORTER
  digitalWrite(dirPin_02, HIGH);                         // FOR SECOND MORTER
  // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for (int x = 0; x < steps; x++) {
    //    ..............................................................FOR FIRST STEPPER MORTER
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(microsteps);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(microsteps);

    //  ................................................................FOR SECOND STEPPER MORTER

    digitalWrite(stepPin_02, HIGH);
    delayMicroseconds(microsteps);
    digitalWrite(stepPin_02, LOW);
    delayMicroseconds(microsteps);
    //    Serial.println(x);
  }
  // ..........................................................................delay is used for stop morter for tesring phase
  //  delay(100); // One second delay
}

void stop_Robot() {
  digitalWrite(enPin, HIGH);
  digitalWrite(enPin_02, HIGH);
  //  //Changes the rotations direction
  //  digitalWrite(dirPin, LOW);                            // FOR FIRST MORTER
  //  digitalWrite(dirPin_02, LOW);                         // FOR SECOND MORTER
  //
  //  // Makes 400 pulses for making two full cycle rotation
  //  for (int x = 0; x < steps; x++) {
  //
  //    //    ..............................................................FOR FIRST STEPPER MORTER
  //    digitalWrite(stepPin, HIGH);
  //    delayMicroseconds(microsteps);
  //    digitalWrite(stepPin, LOW);
  //    delayMicroseconds(microsteps);
  //
  //    //  ................................................................FOR SECOND STEPPER MORTER
  //
  //    digitalWrite(stepPin_02, HIGH);
  //    delayMicroseconds(microsteps);
  //    digitalWrite(stepPin_02, LOW);
  //    delayMicroseconds(microsteps);
  //    //    Serial.println(x);
  //  }
  // ..........................................................................delay is used for stop morter for tesring phase
  delay(100); // One second delay
  digitalWrite(enPin, LOW);
  digitalWrite(enPin_02, LOW);

}

void back() {
  //Changes the rotations direction
  digitalWrite(dirPin, LOW);                            // FOR FIRST MORTER
  digitalWrite(dirPin_02, LOW);                         // FOR SECOND MORTER

  // Makes 400 pulses for making two full cycle rotation
  for (int x = 0; x < steps; x++) {

    //    ..............................................................FOR FIRST STEPPER MORTER
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(microsteps);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(microsteps);

    //  ................................................................FOR SECOND STEPPER MORTER

    digitalWrite(stepPin_02, HIGH);
    delayMicroseconds(microsteps);
    digitalWrite(stepPin_02, LOW);
    delayMicroseconds(microsteps);
    //    Serial.println(x);
  }
  // ..........................................................................delay is used for stop morter for tesring phase
  //  delay(100); // One second delay

}

//change steps FOR  FORWORD AT END CORNER AND BACK AT END CORNER
//microsteps will be same FOR BOTH MOTIONS

void forward_motion_of_morter_at_end_corner() {

  digitalWrite(dirPin, HIGH);                            // FOR FIRST MORTER
  digitalWrite(dirPin_02, HIGH);                         // FOR SECOND MORTER
  // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for (int x = 0; x < steps_for_end; x++) {
    //    ..............................................................FOR FIRST STEPPER MORTER
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(microsteps);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(microsteps);

    //  ................................................................FOR SECOND STEPPER MORTER

    digitalWrite(stepPin_02, HIGH);
    delayMicroseconds(microsteps);
    digitalWrite(stepPin_02, LOW);
    delayMicroseconds(microsteps);
    //    Serial.println(x);
  }
  // ..........................................................................delay is used for stop morter for tesring phase
  //  delay(100); // One second delay
}


void back_at_end_corner() {
  //Changes the rotations direction
  digitalWrite(dirPin, LOW);                            // FOR FIRST MORTER
  digitalWrite(dirPin_02, LOW);                         // FOR SECOND MORTER

  // Makes 400 pulses for making two full cycle rotation
  for (int x = 0; x < steps_for_end; x++) {

    //    ..............................................................FOR FIRST STEPPER MORTER
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(microsteps);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(microsteps);

    //  ................................................................FOR SECOND STEPPER MORTER

    digitalWrite(stepPin_02, HIGH);
    delayMicroseconds(microsteps);
    digitalWrite(stepPin_02, LOW);
    delayMicroseconds(microsteps);
    //    Serial.println(x);
  }
  // ..........................................................................delay is used for stop morter for tesring phase
  //  delay(100); // One second delay

}

// for Brush (DC MORTER) Forword and Backword Motion
void froward() {
  digitalWrite(DC_01, HIGH);
  digitalWrite(DC_02, LOW);
  analogWrite(DC_PWM, 255) ;
  delay(1000);
}

void backward() {
  digitalWrite(DC_01, LOW);
  digitalWrite(DC_02, HIGH);
  analogWrite(DC_PWM, 255) ;
  //delay(1000);
}

