/*
 * uart.c
 *
 * Created: 6/17/2018 7:15:54 PM
 *  Author: Ahmed
 */ 
 #include <avr/io.h>
 #include <util/delay.h>

void USART_Init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	/* Enable receiver and transmitter */
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	
	/* Set frame format: 8data, 1stop bit */
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);

	//Enable receiver and transmitter interrupts
	UCSR0B |= (1<<RXCIE0) | (1<<UDRE0)| (1<<TXCIE0);
}
void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	{
		
	}
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	{
		
	}
	/* Get and return received data from buffer */
	return UDR0;
} 