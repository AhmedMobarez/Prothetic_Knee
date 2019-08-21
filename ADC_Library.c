/*
 * ADC_Library.c
 *
 * Created: 6/16/2018 1:28:39 PM
 *  Author: Ahmed
 */ 
 #include <avr/io.h>
 #include "ADC_Library.h"

 
 void ADC_init(void)
 {
 // Select Vref=AVcc
 ADMUX |= (1<<REFS0);
 //set prescaler to 128 and enable ADC/Autotriggering/Interrupt
  ADMUX |= (1<<MUX0);
ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADATE) | (1<<ADIE) | (1<<ADEN);

//set ADC trigger source - Timer0 compare match A
ADCSRB |= (1<<ADTS1)|(1<<ADTS0);

 }

 void ADC_channel(unsigned char channel)
 {
	 if(channel==1)
	 {
	
		 ADMUX |= (1<<MUX0);
		 
	 }//ADC1

	 else if(channel==)
	 {
		 ADMUX &=~ ((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3) );
		 ADMUX ;
	 }


 }

 
 void StartADC(void)
 {
	 ADCSRA |= (1<<ADSC);
 }


 uint16_t ADC_Read(void)
 {

 return (ADC);

 }


