/*
 * Motor_Control.c
 *
 * Created: 6/16/2018 5:11:03 PM
 *  Author: Ahmed
 */ 
 #include <avr/io.h>
 #include "Motor_Control.h"


 uint16_t Angle=0;
 uint16_t Current=0;
 uint16_t analog=0;
 uint16_t pot=0;
 uint16_t potangle=0;


uint16_t absolute(uint16_t N)
 {
	 return ((N<0)?(-N):(N));
 }

 void Motor_init(void) // Initialize motor driver pins
 {
 
 DDRB |= (1U<<PORTB2) | (1U<<PORTB4) | (1U<<PORTB5); // PB2 : Enable , PB4 : IN1 , PB5: IN2


 }

 void Turn_Direction(unsigned char direction) // 1=right , 0=left
 {
	switch(direction)
	{
	
	case 1: //turn right
		PORTB |= (1U<<PORTB4);
		PORTB &=~ (1U<<PORTB5);
		break;
	
	case 0: //turn left
		PORTB |= (1U<<PORTB5);
		PORTB &=~ (1U<<PORTB4);
		break;

	default:  // stop motor
	PORTB &=~ (1U<<PORTB2);
	break;
	}
 }

 void Switch_motor(unsigned char State) // start/stop motor
 {

	 if(State==1) // start motor
	{
		PORTB |= (1U<<PORTB2);
	}
	else // stop motor
	{
	PORTB &=~ (1U<<PORTB2);
	}
	

 }

 void Servo(uint16_t Angle) // Move to specified angle
 {	
	//Change ADC Channel
	ADC_channel(1); // Motor channel
	
	//Check current angle
		analog = ADC;	
	Current=((double)360/1024)*analog;

	//Check and set direction of rotation
	if(Current<Angle)
	{
		Turn_Direction(0);
	}

	else if(Current>Angle)
	{
		Turn_Direction(1);
	}


	//Rotate till you reach required value 
	while(absolute(Current-Angle)> 2)
	{
		Switch_motor(1);
		analog = ADC;
		Current=((double)360/1024)*analog;
	}

	//When required value is reached...Stop motor
	Switch_motor(0);


 }