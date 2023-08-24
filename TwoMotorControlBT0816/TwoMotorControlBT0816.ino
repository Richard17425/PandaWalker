#include <SoftwareSerial.h>

// Include the AccelStepper Library
#include <AccelStepper.h>
SoftwareSerial mySerial(0,1);
char ble_val;
// Define pin connections
const int dirPinL = 5;
const int stepPinL = 2;
const int dirPinR = 6;
const int stepPinR = 3;
int speed_straight = 650;
int speed_straight_L = 1400; //this side(left side now) speed should set higher
int speed_turn_right_F = 600;
int speed_turn_right_L = 300;
int speed_turn_left_F = 1200;
int speed_turn_left_L = 600;
int acceleration = 100;
int acceleration_L = 66;
bool state = 0;
char STATE = 'N';
// Define motor interface type
#define motorInterfaceType 1

// Creates an instance
AccelStepper myStepperL(motorInterfaceType, stepPinL, dirPinL);
AccelStepper myStepperR(motorInterfaceType, stepPinR, dirPinR);

void setup() {
  Serial.begin(9600);
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  myStepperL.setMaxSpeed(1500);
  myStepperR.setMaxSpeed(1500);
  myStepperL.setAcceleration(50);
  myStepperR.setAcceleration(50);
  //myStepper.setSpeed(200);
  //myStepper.moveTo(200);
}

void loop() {
  if(Serial.available() > 0)
    {
    ble_val = Serial.read(); //Read character transmitted by bluetooth app and print it
    Serial.println(ble_val);
    }
  if(ble_val == 'F'){ //If A go forward
    Forward();
    state = 0;
    STATE = ble_val;
  }
  if(ble_val == 'R'){ // turn right
    Right();
    state = 0;
    STATE = ble_val;
  }
  if(ble_val == 'L'){ // turn left
    Left();
    state = 0;
    STATE = ble_val;
  }
  if(ble_val == 'D'){ // back
    Back();
    state = 0;
    STATE = ble_val;
  }
    if(ble_val == 'A'){ // only left side motor
    Left_only();
    state = 0;
    STATE = ble_val;
  }
  if(ble_val == 'B'){ // accelerate
    Accelerate();
  }
  if(ble_val == 'Y'){  // only right side motor
    Right_only();
    state = 0;
    STATE = ble_val;
  }
  if(ble_val == 'X'){ //slow down
    Slowdown();
  }
  if(ble_val == 'C'){ //(select) stop
    Stop();
    state = 0;
  }
    if(ble_val == 'S'){ //(start) reset speed
    Reset();
  }
  //myStepperL.setSpeed(200);
  //myStepperR.setSpeed(200);
  myStepperL.runSpeed();
  myStepperR.runSpeed(); //use this function to let the motor run at the constant speed
}

void Forward(){
  myStepperL.setSpeed(speed_straight_L); //In steps per second +CW -CCW
  myStepperR.setSpeed(-speed_straight);
}
void Left(){
  myStepperL.setSpeed(speed_turn_left_L);
  myStepperR.setSpeed(-speed_turn_right_F);  //200:133
}
void Right(){
  myStepperL.setSpeed(speed_turn_left_F);
  myStepperR.setSpeed(-speed_turn_right_L);
}
void Left_only(){
  myStepperL.setSpeed(speed_turn_left_F);
  myStepperR.setSpeed(speed_turn_right_F);
}
void Right_only(){
  myStepperR.setSpeed(-speed_turn_right_F);
  myStepperL.setSpeed(-speed_turn_left_F);
}
void TurnAround(){
  myStepperL.setSpeed(200);
  myStepperR.setSpeed(-100);
}
void Back(){
  myStepperL.setSpeed(-speed_straight_L);
  myStepperR.setSpeed(speed_straight);
}
void Stop(){
  myStepperL.setSpeed(0);
  myStepperR.setSpeed(0);
}

void Accelerate(){
  if(state==0){
    speed_straight += 100;
    speed_straight_L += 200;
    speed_turn_right_F += 100;
    speed_turn_right_L += 66;
    speed_turn_left_F += 200;
    speed_turn_left_L += 130;
    state = 1;
  }      
  switch (STATE){
  case 'F':
    Forward();
    break;
  case 'R':
    Right();
    break;
  case 'L':
    Left();
    break;
  case 'D':
    Back();
    break;
  case 'A':
    Left_only();
    break;
  case 'Y':
    Right_only();
    break;
  default:
  
    break;
  }
  // myStepperL.setSpeed(speed_straight);
  // myStepperR.setSpeed(-speed_straight);
}

void Slowdown(){
  if(state==0){
    speed_straight -= 100;
    speed_straight_L -= 200;
    speed_turn_right_F -= 100;
    speed_turn_right_L -= 66;
    speed_turn_left_F -= 100;
    speed_turn_left_L -= 66;
    state = 1;
  }  
  switch (STATE){
  case 'F':
    Forward();
    break;
  case 'R':
    Right();
    break;
  case 'L':
    Left();
    break;
  case 'D':
    Back();
    break;
  case 'A':
    Left_only();
    break;
  case 'Y':
    Right_only();
    break;
  default:
    
    break;
  }
}

void Reset(){
    state=0;
    speed_straight = 650;
    speed_turn_right_F = 500;
    speed_turn_right_L = 333;
    speed_turn_left_F = 1000;
    speed_turn_left_L = 650;
    STATE = 'N';
}
