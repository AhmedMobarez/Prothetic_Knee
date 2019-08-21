#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "HX711.h"


void HX711_init(uint8_t gain)
{
    PD_SCK_SET_OUTPUT;
    DOUT_SET_INPUT;

    HX711_set_gain(gain);
}

int HX711_is_ready(void)
{
    return (DOUT_INPUT & (1 << DOUT_PIN)) == 0;
}

void HX711_set_gain(uint8_t gain)
{
	switch (gain)
	{
		case 128:		// channel A, gain factor 128
			GAIN = 1;
			break;
		case 64:		// channel A, gain factor 64
			GAIN = 3;
			break;
		case 32:		// channel B, gain factor 32
			GAIN = 2;
			break;
	}

	PD_SCK_SET_LOW;
	HX711_read();
}

uint32_t HX711_read(void)
{
	// wait for the chip to become ready
	while (!HX711_is_ready());

    unsigned long count; 
    unsigned char i;
 
    DOUT_SET_HIGH;
    
    _delay_us(1);
 
    PD_SCK_SET_LOW;
    _delay_us(1);
 
    count=0; 
    while(DOUT_READ); 
    for(i=0;i<24;i++)
    { 
        PD_SCK_SET_HIGH; 
        //NOP();
        //NOP();
        //NOP();
        count=count<<1; 
        PD_SCK_SET_LOW; 
		//NOP();
		//NOP();
        if(DOUT_READ)
            count++; 
    } 
   //count = count>>6;
    PD_SCK_SET_HIGH; 
    _delay_us(1);
    PD_SCK_SET_LOW; 
    count ^= 0x800000;
    return(count);
}
