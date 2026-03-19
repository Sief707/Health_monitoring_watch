#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "twi.h"
#include "temp_sensor.h"
#include "lcd.h"

int main(void)
{
	float temperature;
	char temp_str[7];

	LCD_init();
	_delay_ms(50);
	TWI_init();
	Temp_Sensor_Init();

	LCD_clearScreen();
	_delay_ms(20);


	while(1)
	{
		 temperature = temp_reading();

		 int int_part = (int)temperature;
		 int dec_part = (int)((temperature - int_part) * 100); // 2 decimal digits

		 if(dec_part < 0)
		 dec_part = -dec_part;

		 snprintf(temp_str, sizeof(temp_str), "%d.%02d", int_part, dec_part);

		 LCD_clearScreen();
		 LCD_displayString("   Temp: ");
		 LCD_displayString(temp_str);
		 LCD_displayString(" C");

		 _delay_ms(1000);
	}
}
