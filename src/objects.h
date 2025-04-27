#ifndef MOTORS_H
#define MOTORS_H

#include <misc.h>


struct MotorShield{
    int enable_pin;
    int left_pwm_pin, left_a_pin, left_b_pin;
    int right_pwm_pin, right_a_pin, right_b_pin;
    int MAX_SPEED = 255;

    MotorShield(){}

    void init(int en, int pwm_A, int A1, int A2, int pwm_B, int B1, int B2, int max_speed=255){
        enable_pin = en;
        left_pwm_pin = pwm_A, left_a_pin=A1, left_b_pin=A2;
        right_pwm_pin = pwm_B, right_a_pin=B1, right_b_pin=B2;
        MAX_SPEED = max_speed;

        pinMode(enable_pin, OUTPUT);
        pinMode(left_pwm_pin, OUTPUT); pinMode(left_a_pin, OUTPUT); pinMode(left_b_pin, OUTPUT);
        pinMode(right_pwm_pin, OUTPUT); pinMode(right_a_pin, OUTPUT); pinMode(right_b_pin, OUTPUT);
        stopMotors();
    }

    void stopMotors(){
        controlMotors(0, 0);
        digitalWrite(enable_pin, LOW);
    }

    void setMotorSpeed(int motor, int speed){
        bool reverse = speed<0;
        speed = constrain(abs(speed), 0, MAX_SPEED);

        if(motor == 0){
            //Left
            analogWrite(left_pwm_pin, speed);
            digitalWrite(left_a_pin, !reverse);
            digitalWrite(left_b_pin, reverse);
        }
        else{
            //Right
            analogWrite(right_pwm_pin, speed);
            digitalWrite(right_a_pin, !reverse);
            digitalWrite(right_b_pin, reverse);
        }
    }

    void controlMotors(int left_speed, int right_speed){
        digitalWrite(enable_pin, HIGH);
        setMotorSpeed(0, left_speed);
        setMotorSpeed(1, right_speed);
    }

};


struct PassiveBuzzer{
    int pin = 0;

    PassiveBuzzer(){}

    void init(int pin){
        this->pin = pin;
        pinMode(pin, OUTPUT);    
    }

    void beep(unsigned int frec, unsigned int dur){
        tone(pin, frec);
        delay(dur);
        noTone(pin);
    }


    void startupBeep(){
        beep(700, 100);
        beep(900, 100);
    }

    void actionBeep(){
        beep(700, 100);
    }

    void alarmBeep(){
        beep(1000, 200);
        delay(100);
        beep(800, 300);
    }

    void successBeep(){
        beep(700, 100);
        delay(50);
        beep(1000, 100);
        delay(50);
        beep(1300, 100);
    }

    void gamblingBeep(){
        beep(700, 100);
        delay(50);
        beep(1000, 100);
        delay(200);
    }

    void sadBeep(){
        beep(1300, 100); 
        delay(50);
        beep(1000, 100); 
        delay(50);  
        beep(700, 100);
        delay(50);
        beep(500, 200);
    }

    void celebrationBeep(){
        beep(1000, 200);
        delay(300);
        beep(800, 300);
        delay(300);
        beep(600, 300);    
    }

    void angryBeep(){
        beep(600, 100);
        delay(50);
        beep(800, 100);
        delay(200);  
    }

};



#endif