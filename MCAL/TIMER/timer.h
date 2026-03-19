/******************************************************************************
 * File    : timer.h
 * Brief   : Timer Driver Interface for AVR (Timer0, Timer1, Timer2)
 * Author  : Marwa Mohamed
 ******************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/* -------------------------------------------------------------------------
 *                      Timer Identification
 * -------------------------------------------------------------------------*/
typedef enum {
	TIMER0,   /* 8-bit */
	TIMER1,   /* 16-bit */
	TIMER2    /* 8-bit (different prescaler) */
}Timer_ID_Type;

/* -------------------------------------------------------------------------
 *                      Timer Operating Mode
 * -------------------------------------------------------------------------*/
typedef enum {
	NORMAL_MODE,  /* Overflow mode */
	CTC_MODE      /* Compare match mode */
}Timer_ModeType;

/* -------------------------------------------------------------------------
 *          Prescaler for Timer0 & Timer1 (Same Hardware)
 * -------------------------------------------------------------------------*/
typedef enum {
	TIMER0_1_NO_CLOCK = 0,
	TIMER0_1_F_CPU_1,
	TIMER0_1_F_CPU_8,
	TIMER0_1_F_CPU_64,
	TIMER0_1_F_CPU_256,
	TIMER0_1_F_CPU_1024,
	TIMER0_1_EXTERNAL_FALLING,
	TIMER0_1_EXTERNAL_RISING
}Timer0_1_ClockType;

/* -------------------------------------------------------------------------
 *          Prescaler for Timer2 (Different Hardware)
 * -------------------------------------------------------------------------*/
typedef enum {
	TIMER2_NO_CLOCK = 0,
	TIMER2_F_CPU_1,
	TIMER2_F_CPU_8,
	TIMER2_F_CPU_32,
	TIMER2_F_CPU_64,
	TIMER2_F_CPU_128,
	TIMER2_F_CPU_256,
	TIMER2_F_CPU_1024
}Timer2_ClockType;

/* -------------------------------------------------------------------------
 *                      Timer Configuration Structure
 * -------------------------------------------------------------------------*/
typedef struct
{
	uint16 timer_InitialValue;
	uint16 timer_compare_MatchValue;

	Timer_ID_Type  timer_ID;
	Timer_ModeType timer_mode;

	union {
		Timer0_1_ClockType timer0_1_clock;
		Timer2_ClockType   timer2_clock;
	} clock;

}Timer_ConfigType;

/* -------------------------------------------------------------------------
 *                      Function Prototypes
 * -------------------------------------------------------------------------*/

/* Initialize timer with chosen configuration */
void Timer_init(const Timer_ConfigType * Config_Ptr);

/* Disable timer and clear its registers */
void Timer_deInit(Timer_ID_Type timer_type);

/* Register callback function to be called on Interrupt */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID );

#endif /* TIMER_H_ */
