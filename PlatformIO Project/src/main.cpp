#include <Arduino.h>
#include <objects.h>
#include <BluetoothSerial.h>
#include <Preferences.h>

//Globals
MotorShield motors;
PassiveBuzzer speaker; 
BluetoothSerial server;
Preferences data;

#define NOMBRE_BLUETOOTH "R2D2 De Potro"
int LEFT_SPEED = 250;
int RIGHT_SPEED = 250;


//==========================================
//Functions
void handleCommand(String command);
void spin();
void handleConfig(String command);

//==========================================
//MAIN PROGRAM

void setup(){
  Serial.begin(115200);
  data.begin("R2D2");
  server.begin(NOMBRE_BLUETOOTH);
  delay(500);

  motors.init(STNDBY_PIN, PWM_A, A1_PIN, A2_PIN, PWM_B, B1_PIN, B2_PIN);
  speaker.init(SPK);

  LEFT_SPEED = data.getInt("L", 250);
  RIGHT_SPEED = data.getInt("R", 250);

  Serial.println("Systems ready!\n");
  speaker.startupBeep();
}


void loop(){
  while(server.available()){
    handleCommand(server.readStringUntil('\n'));
  }
}

//==========================================
//Implementations

void handleCommand(String command){
  if(command.length() > 1){
    handleConfig(command);
    return;
  }

  char letter = command[0];
  //STOP
  if(letter == 'S'){
      motors.stopMotors();
      Serial.println("STOP!\n");
      return;
  }

  switch (letter)
  {
  case 'F':
      motors.controlMotors(LEFT_SPEED, RIGHT_SPEED);
      Serial.println("Forward!\n");
      break;
    case 'B':
      motors.controlMotors(-LEFT_SPEED, -RIGHT_SPEED);
      Serial.println("Backwards!\n");
      break;
    case 'L':
      motors.controlMotors(-LEFT_SPEED, RIGHT_SPEED);
      Serial.println("Turning Left!\n");
      break;
    case 'R':
      motors.controlMotors(LEFT_SPEED, -RIGHT_SPEED);
      Serial.println("Turning right!\n");
      break;
    case 'X':
      speaker.alarmBeep();
      break;
    case 'Z':
      spin();
      break;
    case 'Y':
      speaker.successBeep();
      break;
  //------------------------
  default:
      break;
  }
}


void spin(){
  motors.controlMotors(LEFT_SPEED, -RIGHT_SPEED);
  delay(1250);
  motors.stopMotors();
}

void handleConfig(String command){
  char letter = command[0];
  int split = command.indexOf(" ");

  if(letter == 'M'){
    LEFT_SPEED = command.substring(1, split).toInt();
    RIGHT_SPEED = command.substring(split+1).toInt();

    data.putInt("L", LEFT_SPEED);
    data.putInt("R", RIGHT_SPEED);

    Serial.println("Received motor speeds: " + String(LEFT_SPEED) + " " + String(RIGHT_SPEED));
  }
}