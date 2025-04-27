#include <Arduino.h>
#include <objects.h>
#include <BluetoothSerial.h>

//Globals
MotorShield motors;
PassiveBuzzer speaker; 
BluetoothSerial server;

#define NOMBRE_BLUETOOTH "BB8 De Potro"
#define SPEED 200


//==========================================
//Functions
void handleCommand(char command);


//==========================================
//MAIN PROGRAM

void setup(){
  Serial.begin(115200);
  server.begin(NOMBRE_BLUETOOTH);
  delay(500);

  motors.init(STNDBY_PIN, PWM_A, A1_PIN, A2_PIN, PWM_B, B1_PIN, B2_PIN);
  speaker.init(SPK);

  Serial.println("Systems ready!\n");
  speaker.startupBeep();
}


void loop(){
  while(server.available()){
    handleCommand(server.read());
  }
}

//==========================================
//Implementations

void handleCommand(char letter){
  //STOP
  if(letter == 'S'){
      motors.stopMotors();
      Serial.println("STOP!\n");
      return;
  }

  switch (letter)
  {
  case 'F':
      motors.controlMotors(SPEED, SPEED);
      Serial.println("Forward!\n");
      break;
    case 'B':
      motors.controlMotors(-SPEED, -SPEED);
      Serial.println("Backwards!\n");
      break;
    case 'L':
      motors.controlMotors(-SPEED, SPEED);
      Serial.println("Turning Left!\n");
      break;
    case 'R':
      motors.controlMotors(SPEED, -SPEED);
      Serial.println("Turning right!\n");
      break;
  //------------------------
  default:
      break;
  }
}