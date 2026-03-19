/******************************************************************************
 * File    : uart.h
 * Brief   : UART driver header file for AVR (ATmega32)
 * Author  : Marwa Mohamed
 ******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

#define INTERRUPT_MODE		0
#define POLLING_MODE		1

/* Data Bits Options */
typedef enum
{
	FIVE_BITS,      // 5 Data bits
	SIX_BITS,       // 6 Data bits
	SEVEN_BITS,     // 7 Data bits
	EIGHT_BITS,     // 8 Data bits
	NINE_BITS       // 9 Data bits
}UART_BitDataType;


/* Parity Options */
typedef enum
{
	DISABLED_PARITY,   // No parity
	RESERVED_PARITY,   // Not used
	EVEN_PARITY,       // Even parity
	ODD_PARITY         // Odd parity
}UART_ParityType;


/* Stop Bit Options */
typedef enum
{
	ONE_STOP_BIT,      // 1 Stop bit
	TWO_STOP_BITS      // 2 Stop bits
}UART_StopBitType;


/* Baud Rate Options */
typedef enum
{
	BAUD_2400 = 2400,
	BAUD_4800 = 4800,
	BAUD_9600 = 9600,
	BAUD_19200 = 19200
}UART_BaudRateType;


/* UART Configuration Structure */
typedef struct {
	UART_BitDataType bit_data;
	UART_ParityType parity;
	UART_StopBitType stop_bit;
	UART_BaudRateType baud_rate;
} UART_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize UART Module based on configuration passed from user.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Send 1 byte.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Receive 1 byte.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send string (NULL terminated).
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive string until '#' char is received.
 */
void UART_receiveString(uint8 *Str);
uint8 UART_available(void);

#endif /* UART_H_ */
