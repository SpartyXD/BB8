#ifndef MISC_H
#define MISC_H

#include <Arduino.h>

//=====================================
//PINS
#define SPK 22 //Buzzer

//Left motor
#define PWM_A 21 
#define A1_PIN 18
#define A2_PIN 19

//Right motor
#define PWM_B 16
#define B1_PIN 5
#define B2_PIN 17

//=====================================
//MACROS / PARAMETERS / AUX FUNCTIONS
#define rep(i, n) for(int i=0; i<n; i++)
#define MAX_ARDUINO_TIME 3294967295

unsigned long get_time(){
    return (millis()%MAX_ARDUINO_TIME);
}


//=====================================




#endif