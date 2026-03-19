/******************************************************************************
 * File    : uart.c
 * Brief   : UART driver implementation for AVR (ATmega32)
 * Author  : Marwa Mohamed
 ******************************************************************************/

#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void UART_init(const UART_ConfigType * Config_Ptr){

	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/* Enable RX & TX */
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/* Select UCSRC register */
	UCSRC = (1<<URSEL);

	/* ---------- Data Bits ---------- */
	if(Config_Ptr -> bit_data == NINE_BITS)
	{
		/* 9-bit mode */
		UCSRB |= (1<<UCSZ2);
		UCSRC |= (1<<UCSZ1) | (1<<UCSZ0);

	}
	else
	{
		UCSRB &= ~(1<<UCSZ2);    /* Ensure UCSZ2 = 0 */
		UCSRC |= (((Config_Ptr -> bit_data) & 0x03) << 1);
	}

	/* ---------- Parity ---------- */
	UCSRC &= ~((1<<UPM1) | (1<<UPM0));   /* Clear parity bits */

	if(Config_Ptr->parity == EVEN_PARITY)
		UCSRC |= (1<<UPM1);
	else if(Config_Ptr->parity == ODD_PARITY)
		UCSRC |= (1<<UPM1) | (1<<UPM0);

	/* ---------- Stop Bit ---------- */
	UCSRC &= ~(1<<USBS);
	if(Config_Ptr->stop_bit == TWO_STOP_BITS)
		UCSRC |= (1<<USBS);

	/* ---------- Baud Rate ---------- */
	ubrr_value = (uint16)((F_CPU / (8UL * Config_Ptr->baud_rate)) - 1);

	UBRRL = ubrr_value;
	UBRRH = ubrr_value >> 8;
}


/*
 * Send one byte
 */
void UART_sendByte(const uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE)){} /* Wait until UDR is empty */
	UDR = data;
}


/*
 * Receive one byte
 */
uint8 UART_recieveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){} /* Wait until data is received */
	return UDR;
}


/*
 * Send string
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}


/*
 * Receive string until '#'
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	Str[i] = UART_recieveByte();

	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	Str[i] = '\0';
}
