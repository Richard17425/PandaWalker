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
int speed_straight = 450;
int speed_turn_F = 500;
int speed_turn_L = 333;
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
  myStepperL.setMaxSpeed(1000);
  myStepperR.setMaxSpeed(1000);
  myStepperL.setAcceleration(50);
  myStepperR.setAcceleration(50);
  //myStepper.setSpeed(200);
  //myStepper.moveTo(200);
}

void loop() {

    //Forward();
    myStepperL.setSpeed(2*speed_straight-400);//this is right side
    myStepperR.setSpeed(-speed_straight);
    state = 0;
    STATE = ble_val;

  //myStepperL.setSpeed(200);
  //myStepperR.setSpeed(200);
  myStepperL.runSpeed();
  myStepperR.runSpeed();
}

void Forward(){
  myStepperL.setSpeed(-speed_straight); //In steps per second +CW -CCW
  myStepperR.setSpeed(speed_straight);
}
void Left(){
  myStepperL.setSpeed(-speed_turn_L);
  myStepperR.setSpeed(speed_turn_F);  //200:133
}
void Right(){
  myStepperL.setSpeed(-speed_turn_F);
  myStepperR.setSpeed(speed_turn_L);
}
void Left_only(){
  myStepperL.setSpeed(-speed_turn_L);
  myStepperR.setSpeed(0);
}
void Right_only(){
  myStepperR.setSpeed(speed_turn_L);
  myStepperL.setSpeed(0);
}
void TurnAround(){
  myStepperL.setSpeed(200);
  myStepperR.setSpeed(-100);
}
void Back(){
  myStepperL.setSpeed(speed_straight);
  myStepperR.setSpeed(-speed_straight);
}
void Stop(){
  myStepperL.setSpeed(0);
  myStepperR.setSpeed(0);
}

void Accelerate(){
  if(state==0){
    speed_straight += 100;
    speed_turn_F += 100;
    speed_turn_L += 66;
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
    speed_turn_F -= 100;
    speed_turn_L -= 66;
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
    speed_turn_F = 500;
    speed_turn_L = 333;
    STATE = 'N';
}
