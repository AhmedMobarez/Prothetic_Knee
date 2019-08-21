/*
 * Timers_Library.c
 *
 * Created: 6/18/2018 8:15:41 PM
 *  Author: Ahmed
 */ 

 #include <avr/io.h>
 #include "Timers_Library.h"

 





  void Timer0_init( void)
  {
	  //Set Initial Timer value
	  TCNT0=0;
	  //Place TOP timer value to Output compare register
	  OCR0A=62	; // Compare match at frequency 250 Hz
	  //Set CTC mode
	  //and make toggle PD6/OC0A pin on compare match
	  TCCR0A |=(1<<COM0A0)|(1<<WGM01);

	  //Set prescaler 1024 and start timer
	  TCCR0B |=(1<<CS00) | (1<<CS02);
  }		