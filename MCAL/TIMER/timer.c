/******************************************************************************
 * File    : timer.c
 * Brief   : Timer Driver for AVR (Timer0, Timer1, Timer2) with Interrupt & Callback
 * Author  : Marwa Mohamed
 ******************************************************************************/
#include "timer.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* -------------------------------------------------------------------------
 *                      Global Callback Pointers
 * -------------------------------------------------------------------------*/
static volatile void (*g_Timer0_CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer1_CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer2_CallBackPtr)(void) = NULL_PTR;

/* -------------------------------------------------------------------------
 *                      ISR - Overflow
 * -------------------------------------------------------------------------*/
ISR(TIMER0_OVF_vect)
{
	if(g_Timer0_CallBackPtr != NULL_PTR)
		(*g_Timer0_CallBackPtr)();
}

ISR(TIMER1_OVF_vect)
{
	if(g_Timer1_CallBackPtr != NULL_PTR)
		(*g_Timer1_CallBackPtr)();
}

ISR(TIMER2_OVF_vect)
{
	if(g_Timer2_CallBackPtr != NULL_PTR)
		(*g_Timer2_CallBackPtr)();
}

/* -------------------------------------------------------------------------
 *                      ISR - Compare Match
 * -------------------------------------------------------------------------*/
ISR(TIMER0_COMP_vect)
{
	if(g_Timer0_CallBackPtr != NULL_PTR)
		(*g_Timer0_CallBackPtr)();
}

ISR(TIMER1_COMPA_vect)
{
	if(g_Timer1_CallBackPtr != NULL_PTR)
		(*g_Timer1_CallBackPtr)();
}

ISR(TIMER2_COMP_vect)
{
	if(g_Timer2_CallBackPtr != NULL_PTR)
		(*g_Timer2_CallBackPtr)();
}

/* -------------------------------------------------------------------------
 *                      Timer Initialization
 * -------------------------------------------------------------------------*/
void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	switch(Config_Ptr->timer_ID)
	{
	case TIMER0:

		TCNT0 = (uint8)Config_Ptr->timer_InitialValue;

		if(Config_Ptr->timer_mode == CTC_MODE)
		{
			OCR0 = (uint8)Config_Ptr->timer_compare_MatchValue;

			TCCR0 = (1<<FOC0) | (1<<WGM01);
			SET_BIT(TIMSK, OCIE0);
		}
		else
		{
			TCCR0 = (1<<FOC0);
			SET_BIT(TIMSK, TOIE0);
		}

		/* Set prescaler */
		TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->clock.timer0_1_clock);

		break;

	case TIMER1:

		TCCR1A = (1<<FOC1A) | (1<<FOC1B);
		TCNT1  = Config_Ptr->timer_InitialValue;

		if(Config_Ptr->timer_mode == CTC_MODE)
		{
			OCR1A = Config_Ptr->timer_compare_MatchValue;

			TCCR1B = (1<<WGM12);
			SET_BIT(TIMSK, OCIE1A);
		}
		else
		{
			TCCR1B = 0;
			SET_BIT(TIMSK, TOIE1);
		}

		/* Set prescaler */
		TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock.timer0_1_clock);

		break;

	case TIMER2:

		TCNT2 = (uint8)Config_Ptr->timer_InitialValue;

		if(Config_Ptr->timer_mode == CTC_MODE)
		{
			OCR2 = (uint8)Config_Ptr->timer_compare_MatchValue;

			TCCR2 = (1<<FOC2) | (1<<WGM21);
			SET_BIT(TIMSK, OCIE2);
		}
		else
		{
			TCCR2 = (1<<FOC2);
			SET_BIT(TIMSK, TOIE2);
		}

		/* Set prescaler (Timer2 specific) */
		TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr->clock.timer2_clock);

		break;
	}

	/* Enable Global Interrupt */
	SREG |= (1<<7);
}

/* -------------------------------------------------------------------------
 *                      Timer DeInitialization
 * -------------------------------------------------------------------------*/
void Timer_deInit(Timer_ID_Type timer_type)
{
	switch(timer_type)
	{
	case TIMER0:
		TCCR0 = 0;
		TCNT0 = 0;
		OCR0  = 0;
		CLEAR_BIT(TIMSK, TOIE0);
		CLEAR_BIT(TIMSK, OCIE0);
		break;

	case TIMER1:
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1  = 0;
		OCR1A  = 0;
		CLEAR_BIT(TIMSK, TOIE1);
		CLEAR_BIT(TIMSK, OCIE1A);
		break;

	case TIMER2:
		TCCR2 = 0;
		TCNT2 = 0;
		OCR2  = 0;
		CLEAR_BIT(TIMSK, TOIE2);
		CLEAR_BIT(TIMSK, OCIE2);
		break;
	}
}

/* -------------------------------------------------------------------------
 *                      Set Callback Function
 * -------------------------------------------------------------------------*/
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID)
{
	switch(a_timer_ID)
	{
	case TIMER0:
		g_Timer0_CallBackPtr = a_ptr;
		break;

	case TIMER1:
		g_Timer1_CallBackPtr = a_ptr;
		break;

	case TIMER2:
		g_Timer2_CallBackPtr = a_ptr;
		break;
	}
}
