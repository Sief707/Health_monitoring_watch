#define F_CPU 16000000UL
#include "bluetooth.h"
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "uart.h"
#define BLUETOOTH_BAUD 9600
// Improved formula: Rounds to the nearest integer instead of truncating
#define UBRR_VALUE (((F_CPU) + 8UL * (BLUETOOTH_BAUD)) / (16UL * (BLUETOOTH_BAUD)) - 1)

/* ================= UART INIT ================= */
void Bluetooth_init(void)
{
    /* Set baud rate */
    UBRRH = (uint8_t)(UBRR_VALUE >> 8);
    UBRRL = (uint8_t)UBRR_VALUE;

    /* Enable RX and TX */
    UCSRB = (1 << RXEN) | (1 << TXEN);

    /* 8 data bits, 1 stop bit, no parity */
    /* ATmega32 CRITICAL FIX: You must set the URSEL bit to 1 to write to UCSRC */
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

/* ================= SEND BYTE ================= */
void Bluetooth_sendByte(uint8_t data)
{
    while (!(UCSRA & (1 << UDRE)));  // Wait for empty transmit buffer
    UDR = data;
}

/* ================= RECEIVE BYTE ================= */
uint8_t Bluetooth_receiveByte(void)
{
    while (!(UCSRA & (1 << RXC)));  // Wait for incoming data
    return UDR;
}

/* ================= SEND STRING ================= */
void Bluetooth_sendString(const char *str)
{
    while (*str != '\0')
    {
        Bluetooth_sendByte(*str++);
    }
}

/* ================= RECEIVE STRING ================= */
// IMPROVEMENT: Added max_length to prevent memory corruption if '#' is missed
void Bluetooth_receiveString(char *str, uint8_t max_length)
{
    uint8_t i = 0;
    char ch;

    // Leave room for the null terminator
    while (i < max_length - 1)
    {
        ch = Bluetooth_receiveByte();

        if (ch == '#')   // End character
            break;

        str[i++] = ch;
    }

    str[i] = '\0'; // Properly terminate the string
}

/* ================= CHECK DATA AVAILABLE ================= */
uint8_t Bluetooth_isDataAvailable(void)
{
    return (UCSRA & (1 << RXC));
}
void Bluetooth_sendData(const char *data) {
    // We just pass the data down to the UART driver
    UART_sendString("BT: ");
    UART_sendString(data);
    UART_sendString("\r\n");
}
