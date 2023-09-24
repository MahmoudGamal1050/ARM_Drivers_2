/*********************************************************************
* File Name    	: 	MEXTI_program.c                                  *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	12/9/2023                                        *
* Description   : 			         				                 *                         
**********************************************************************/


#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/MSTK/MSTK_private.h"
#include "MCAL/MSTK/MSTK_config.h"
#include "MCAL/MSTK/MSTK_interface.h"



static	void	(*STK_CallBack)	(void)	=	NULL;
static	u8		STK_u8IntervalMode;

void 	MSTK_voidInit(ClockSource_t Copy_uddtClock)
{
		MSTK -> CTRL	|=	(Copy_uddtClock<<CLKSOURCE);
}
void	MSTK_voidSetBusyWait(u32 Copy_u32Ticks)
{
	/*	Load ticks to Load Register 	*/
	MSTK -> LOAD = Copy_u32Ticks;
	/*	Start the timer 				*/
	SET_BIT(MSTK -> CTRL , ENABLE);
	/*	Wait till the flag is raised 	*/
	while((GET_BIT(MSTK -> CTRL , COUNTFLAG ))==0);

	/*	Stop the timer					*/
	CLR_BIT(MSTK -> CTRL , ENABLE);
	MSTK ->	LOAD	=	0;
	MSTK ->	VAL		=	0;
}
void	MSTK_voidSetIntervalSingle(u32 Copy_u32Ticks, void (*Copy_ptr)(void))
{
	/*	Load ticks to Load Register 	*/
	MSTK -> LOAD = Copy_u32Ticks;
	/*	Start the timer 				*/
	SET_BIT(MSTK -> CTRL , ENABLE);
	/*	Save Call Back Function		 	*/
	STK_CallBack =	Copy_ptr;
	/*	Enable STK Interrupt		 	*/
	SET_BIT(MSTK -> CTRL , TICKINT);
	/*	Set the mode single Interval	*/
	STK_u8IntervalMode = STK_SINGLE_INTERVAL;
}
void	MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void (*Copy_ptr)(void))
{
		/*	Load ticks to Load Register 	*/
	MSTK -> LOAD = Copy_u32Ticks;
	/*	Start the timer 				*/
	SET_BIT(MSTK -> CTRL , ENABLE);
	/*	Save Call Back Function		 	*/
	STK_CallBack =	Copy_ptr;
	/*	Enable STK Interrupt		 	*/
	SET_BIT(MSTK -> CTRL , TICKINT);
	/*	Set the mode single Interval	*/
	STK_u8IntervalMode = STK_PERIOD_INTERVAL;
}
void	MSTK_voidStopInterval()
{
		/*	Disable The Interrupt			*/
		CLR_BIT(MSTK -> CTRL , TICKINT);
		/*	Stop the timer					*/
		CLR_BIT(MSTK -> CTRL , ENABLE);
		MSTK ->	LOAD	=	0;
		MSTK ->	VAL		=	0;
}
u32		MSTK_u32GetElapsedTime()
{
	u32	Local_u32ElapsedTime;
	Local_u32ElapsedTime	=	((MSTK -> LOAD)-(MSTK -> VAL));
	return	Local_u32ElapsedTime;	
}
u32		MSTK_u32GetRemainingTime()
{
	u32	Local_u32Remaining;
	Local_u32Remaining	=	MSTK -> VAL;
	return	Local_u32Remaining;
}

void	SysTick_Handler()
{
	u8 Local_u8Temp;
	if(STK_u8IntervalMode == STK_SINGLE_INTERVAL)
	{	
		/*	Disable The Interrupt			*/
		CLR_BIT(MSTK -> CTRL , TICKINT);
		/*	Stop the timer					*/
		CLR_BIT(MSTK -> CTRL , ENABLE);
		MSTK ->	LOAD	=	0;
		MSTK ->	VAL		=	0;
	}
	STK_CallBack();
	/*	to clear the timer flag just read it */
	Local_u8Temp	=	GET_BIT(MSTK -> CTRL,COUNTFLAG);
}





