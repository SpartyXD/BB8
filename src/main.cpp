#include <Arduino.h>
#include <bluetoothApp.h>
#include <objects.h>

//Globals
MotorShield motors;
PassiveBuzzer speaker;

void setup(){
  Serial.begin(115200);
  motors.init(STNDBY_PIN, PWM_A, A1_PIN, A2_PIN, PWM_B, B1_PIN, B2_PIN);
  speaker.init(SPK);
}


void loop(){

}

