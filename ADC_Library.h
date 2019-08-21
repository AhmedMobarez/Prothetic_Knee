/*
 * ADC_Library.h
 *
 * Created: 6/16/2018 1:29:00 PM
 *  Author: Ahmed
 */ 


#ifndef ADC_LIBRARY_H_
#define ADC_LIBRARY_H_


void ADC_init(void);

void ADC_channel(unsigned char channel);

uint16_t ADC_Read(void);

void StartADC(void);


#endif /* ADC_LIBRARY_H_ */