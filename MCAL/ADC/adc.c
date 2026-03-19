/******************************************************************************
 * File    : adc.c
 * Brief   : ADC driver implementation for AVR
 * Author  : Marwa Mohamed
 ******************************************************************************/

#include<avr/io.h>
#include"common_macros.h"
#include"adc.h"

void ADC_init(void){

	/*Select VREF = AVCC & 	initialize channel_num = 0*/
	ADMUX = 0X40;

	/*set ADC enable on*/
	SET_BIT(ADCSRA,ADEN);

	/*set ADC interrupt enable off*/
	CLEAR_BIT(ADCSRA,ADIE);

	/*set prescaler => N = 128 */
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);


}
uint16 ADC_readChannel(uint8 channel_num){

	ADMUX = (ADMUX & (0XE0)) | (channel_num & (0X1F));
	SET_BIT(ADCSRA,ADSC);
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	SET_BIT(ADCSRA,ADIF);
	return ADC;

}
