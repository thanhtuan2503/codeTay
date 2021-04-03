#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "motor.h"
void motorSetup(){
    pinMode(IN1_1, OUTPUT);
    pinMode(IN2_1, OUTPUT);
    pinMode(IN3_1, OUTPUT);
    pinMode(IN4_1, OUTPUT);
    pinMode(IN1_2, OUTPUT);
    pinMode(IN2_2, OUTPUT);
    pinMode(IN3_2, OUTPUT);
    pinMode(IN4_2, OUTPUT);
}

void motor_Dung(int n) {
  switch (n){
    case 1:
      analogWrite(IN1_1, 0);
      analogWrite(IN2_1, 0);    
    break;
    case 2:
      analogWrite(IN3_1, 0);
      analogWrite(IN4_1, 0);    
    break;
    case 3:
      analogWrite(IN1_2, 0);
      analogWrite(IN2_2, 0);    
    break;
    case 4:
      analogWrite(IN3_2, 0);
      analogWrite(IN4_2, 0);    
    break;
  }
}
 
 
void motor_Tien(int n, int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  switch (n){
    case 1:
      analogWrite(IN1_1, speed);
      analogWrite(IN2_1, 0);    
    break;
    case 2:
      analogWrite(IN3_1, speed);
      analogWrite(IN4_1, 0);    
    break;
    case 3:
      analogWrite(IN1_2, speed);
      analogWrite(IN2_2, 0);    
    break;
    case 4:
      analogWrite(IN3_2, speed);
      analogWrite(IN4_2, 0);    
    break;
  }
}
 
void motor_Lui(int n, int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  switch (n){
    case 1:
      analogWrite(IN1_1, 0);
      analogWrite(IN2_1, speed);    
    break;
    case 2:
      analogWrite(IN3_1, 0);
      analogWrite(IN4_1, speed);    
    break;
    case 3:
      analogWrite(IN1_2, 0);
      analogWrite(IN2_2, speed);    
    break;
    case 4:
      analogWrite(IN3_2, 0);
      analogWrite(IN4_2, speed);    
    break;
  }
}