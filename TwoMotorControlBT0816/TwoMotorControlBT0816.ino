#include <SoftwareSerial.h>
// more details and instructions:https://github.com/Richard17425/PandaWalker
// Include the AccelStepper Library
#include <AccelStepper.h>
SoftwareSerial mySerial(0,1);
char ble_val;
// Define pin connections
const int dirPinL = 5;
const int stepPinL = 2;
const int dirPinR = 6;
const int stepPinR = 3;
int speed_straight = 380;     // this the right side straight speed
int speed_straight_L = 720; //this side(left side now) speed should set higher
int speed_turn_right_F = 1100;    
int speed_turn_right_L = -300;
int speed_turn_left_F = 700;
int speed_turn_left_L = -700;
int acceleration = 100;
int acceleration_L = 66;
bool state = 0;    // state of speed Accelerate
char STATE = 'N';  //char get from the Bluetooth
// Define motor interface type
#define motorInterfaceType 1

// Creates an instance
AccelStepper myStepperL(motorInterfaceType, stepPinL, dirPinL);
AccelStepper myStepperR(motorInterfaceType, stepPinR, dirPinR);

void setup() {
  Serial.begin(9600);
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  myStepperL.setMaxSpeed(2300);
  myStepperR.setMaxSpeed(1200);
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
    if(ble_val == 'A'){ // turn around from left side
    TurnAround_Leftside();
    state = 0;
    STATE = ble_val;
  }
  if(ble_val == 'B'){ // accelerate
    Accelerate();
  }
  if(ble_val == 'Y'){  // turn around from right side
    TurnAround();
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

  myStepperL.runSpeed();
  myStepperR.runSpeed(); //use this function to let the motor run at the constant speed
}

void Forward(){
  myStepperL.setSpeed(speed_straight_L); //In steps per second +CW -CCW
  myStepperR.setSpeed(-speed_straight);
}
void Left(){
  myStepperL.setSpeed(700);
  myStepperR.setSpeed(-700);
}
void Right(){
  myStepperL.setSpeed(1100);
  myStepperR.setSpeed(-300);
}
void Left_only(){        // only for test
  myStepperL.setSpeed(speed_turn_left_F);
  myStepperR.setSpeed(speed_turn_right_F);
}
void Right_only(){      // only for test
  myStepperR.setSpeed(-speed_turn_right_F);
  myStepperL.setSpeed(-speed_turn_left_F);
}
void TurnAround(){
  myStepperL.setSpeed(720);
  myStepperR.setSpeed(380);
}
void TurnAround_Leftside(){
  myStepperL.setSpeed(-720);
  myStepperR.setSpeed(-380);
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
    TurnAround_Leftside();
    break;
  case 'Y':
    TurnAround();
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
    speed_straight = 380;
    speed_straight_L = 720;
    speed_turn_right_F = 1100;    
    speed_turn_right_L = -300;
    speed_turn_left_F = 700;
    speed_turn_left_L = -700;
    STATE = 'N';
}
