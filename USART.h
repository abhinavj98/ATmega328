/*
 * USART.h
 *
 * Created: 1/24/2017 7:31:22 PM
 *  Author: Abhinav
 */ 
//8 bit, 1 stop bit   
#define F_CPU 1000000UL
#include <avr/io.h>
void USARTinit(int baud)
{
	int BAUDvalue = (F_CPU/(baud*16))-1;
  UCSR0C = (~(1<<UMSEL00))| (~(1<<UMSEL01)) | (~(1<<USBS0)) | (1<<UCSZ00) | (1<<UCSZ01); //Start Asynchronous USART,1 Stop Bit, 8 bit data
	UCSR0B = (~(1<<UCSZ02));
	UBRR0H = (BAUDvalue >> 8); //Set Baud
	UBRR0L = BAUDvalue; //Set Baud
}

char ReceiveChar()
{
	UCSR0B = (1 << RXEN0); //Receiver enable
	while(!(UCSR0A & (1 << RXC0 )));
	char data = UDR0;
	return data;
}

void TransmitChar(char send)
{
	UCSR0B = (1 << TXEN0) ; //Transmitter enable
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = send;
	return 0;
}




