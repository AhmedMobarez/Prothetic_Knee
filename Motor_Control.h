/*
 * Motor_Control.h
 *
 * Created: 6/16/2018 5:11:30 PM
 *  Author: Ahmed
 */ 


#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

extern uint16_t Angle;
extern uint16_t Current;
extern uint16_t analog;
extern uint16_t pot;
extern uint16_t potangle;

void Motor_init(void); // initialize motor driver pins

void Turn_Direction(unsigned char direction); // 1=right , 0=left

void Switch_motor(unsigned char State); // start/stop motor

void Servo(uint16_t Angle); // Move to specified angle

uint16_t absolute(uint16_t N); // Calculate absolute value of an integer

#endif /* MOTOR_CONTROL_H_ */