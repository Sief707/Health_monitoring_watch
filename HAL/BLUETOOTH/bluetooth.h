#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_
#include "std_types.h"
#include"common_macros.h"
#include <stdint.h> // Using standard types to avoid conflict

#define NUMBER_OF_TRIES 5
#define CONFIRM_BYTE 0x0D
#define CONFIRM_STRING "OK"

void Bluetooth_init(void);
void Bluetooth_sendByte(uint8_t data);
uint8_t Bluetooth_receiveByte(void);
void Bluetooth_sendString(const char *str);
void Bluetooth_receiveString(char *str, uint8_t max_length);
uint8_t Bluetooth_isDataAvailable(void);
void Bluetooth_sendData(const char *data);
#endif /* BLUETOOTH_H_ */
