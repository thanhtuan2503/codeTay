#ifndef MOTOR_H
#define MOTOR_H
#define IN1_1 2
#define IN2_1 3
#define IN3_1 4
#define IN4_1 5
#define IN1_2 6
#define IN2_2 7
#define IN3_2 8
#define IN4_2 9

#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0

void motorSetup();
void motor_Tien(int n, int speed);
void motor_Lui(int n, int speed);
void motor_Dung(int n);
#endif
