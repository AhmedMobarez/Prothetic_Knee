/*
 * Prothetic_Knee.c
 *
 * Created: 7/9/2018 6:17:23 PM
 * Author : Ahmed
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC_Library.h"
#include "Motor_Control.h"
#include "uart.h"
#include "Timers_Library.h"

volatile uint16_t ADC_Reading=0;
volatile uint16_t Knee_Angle=0;
volatile uint16_t Motor_Angle=0;
volatile int32_t Strain_Reading=0; // To Do : Add code for strain gauge
volatile unsigned char Sensor =0;

ISR(ADC_vect)
{

 ADC_Reading = ADC_Read(); //Read and store ADC output

 //To Do : Check ADC channel before sensor calculations 

 Knee_Angle = ((double)360/1024)*ADC_Reading; // Calculate Knee angle

 //Motor_Angle = ((double)360/1024)*ADC_Reading; // Calculate Motor angle

}



ISR(USART_UDRE_vect)
{

switch(Sensor)
{
	case 0 : 
		UDR0 = Knee_Angle>>8;  //To Do : test transmission in that way
		UDR0 = Knee_Angle;
	break;

	case 1 :
		UDR0 = Strain_Reading>>8;
		UDR0 = Strain_Reading;
	break;

	case 2 :
		UDR0 = Motor_Angle>>8;
		UDR0 = Motor_Angle;
	break;

	default :
		UCSR0B &=~ (1<<UDRE0);  //Disable transmission interrupt
	break;

}
//Disable transmission interrupt
UCSR0B &=~ (1<<UDRE0);



}


int main(void)
{

	//initialize motor pins
	Motor_init();

	//initialize ADC
	ADC_init();

	//Select ADC Channel
	ADC_channel(1);

	// initialize UART
	USART_Init(MYUBRR);

	//Initialize timer
	Timer0_init();

	// Start ADC Conversion
	StartADC();
	Finite_State_Machine(1);
	//Enable global interrupt
	sei();
	
    
    while (1) 
    {
    }
}







void Finite_State_Machine (uint8_t State)
{

	if (State = 1)
	{
		if ()  			//c12
		State = 2;
		else if () 			//c13
		State = 3;
		else if ( )  		//c14
		State = 4;
		else
		State = 1;
	}
	else if (State = 2)
	{
		if ( )				//c23
		State = 3;
		else if ()		//c21
		State = 1;
		else if ()						//c24
		State = 4;
	}
	else if (State = 3)
	{
		if ()				//c34
		State = 4;
		else if ()			//c31
		State = 1;
	}
	else if (State = 4)
	{
		if ()								//c45
		State = 5;
		else if ()			//s41
		State = 1;
	}
	else if (State = 5)
	{
		if ()								//c51
		State = 1;
	}

}