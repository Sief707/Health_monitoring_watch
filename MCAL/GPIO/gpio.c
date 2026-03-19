/******************************************************************************
 * File    : gpio.c
 * Brief   : GPIO driver implementation for AVR
 * Author  : Marwa Mohamed
 ******************************************************************************/
#include<avr/io.h>
#include"gpio.h"


void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Invalid input: Do Nothing */
		return;
	}

	volatile uint8 *ddr_reg = NULL;

	/* Select the correct DDR register based on port_num */
	switch(port_num)
	{
	case PORTA_ID:
		ddr_reg = &DDRA;
		break;
	case PORTB_ID:
		ddr_reg = &DDRB;
		break;
	case PORTC_ID:
		ddr_reg = &DDRC;
		break;
	case PORTD_ID:
		ddr_reg = &DDRD;
		break;
	default:
		return;
	}

	if(direction == PIN_OUTPUT)
	{
		SET_BIT(*ddr_reg, pin_num);
	}
	else
	{
		CLEAR_BIT(*ddr_reg, pin_num);
	}
}
/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value){
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Invalid input: Do Nothing */
		return;
	}

	volatile uint8 *port_reg = NULL;

	/* Select the correct PORT register based on port_num */
	switch(port_num)
	{
	case PORTA_ID:
		port_reg = &PORTA;
		break;
	case PORTB_ID:
		port_reg = &PORTB;
		break;
	case PORTC_ID:
		port_reg = &PORTC;
		break;
	case PORTD_ID:
		port_reg = &PORTD;
		break;
	default:
		return;
	}
	if(value == LOGIC_HIGH)
	{
		SET_BIT(*port_reg,pin_num);
	}
	else
	{
		CLEAR_BIT(*port_reg,pin_num);
	}
}
/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num){
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Invalid input: Do Nothing */
		return LOGIC_LOW;
	}

	volatile uint8 *pin_reg = NULL;

	/* Select the correct PIN register based on port_num */
	switch(port_num)
	{
	case PORTA_ID:
		pin_reg = &PINA;
		break;
	case PORTB_ID:
		pin_reg = &PINB;
		break;
	case PORTC_ID:
		pin_reg = &PINC;
		break;
	case PORTD_ID:
		pin_reg = &PIND;
		break;
	default:
		return LOGIC_LOW;
	}
	if(BIT_IS_CLEAR(*pin_reg,pin_num))
	{
		return LOGIC_LOW;
	}
	else
	{
		return LOGIC_HIGH;
	}

}
/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}

	/* Setup the port direction as required */
	switch(port_num)
	{
	case PORTA_ID:
		DDRA = direction;
		break;
	case PORTB_ID:
		DDRB = direction;
		break;
	case PORTC_ID:
		DDRC = direction;
		break;
	case PORTD_ID:
		DDRD = direction;
		break;
	}

}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}

	/* Setup the port direction as required */
	switch(port_num)
	{
	case PORTA_ID:
		PORTA = value;
		break;
	case PORTB_ID:
		PORTB = value;
		break;
	case PORTC_ID:
		PORTC = value;
		break;
	case PORTD_ID:
		PORTD = value;
		break;
	}


}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		return 0;
	}

	/* Setup the port direction as required */
	switch(port_num)
	{
	case PORTA_ID:
		return PINA;
	case PORTB_ID:
		return PINB;
	case PORTC_ID:
		return PINC;
	case PORTD_ID:
		return PIND;
	default:
		return LOGIC_LOW;
	}

}


