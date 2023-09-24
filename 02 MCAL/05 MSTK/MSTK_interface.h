/*********************************************************************
* File Name    	: 	MEXTI_interface.h                                 	 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	12/9/2023                                        *
* Description   : 			         				                 *                         
**********************************************************************/
#ifndef	MSTK_INTERFACE_H
#define	MSTK_INTERFACE_H

typedef enum
{
	STK_AHB_Div_BY_8,
	STK_AHB
}ClockSource_t;


void 	MSTK_voidInit(ClockSource_t Copy_uddtClock);
void	MSTK_voidSetBusyWait(u32 Copy_u32Ticks);
void	MSTK_voidSetIntervalSingle(u32 Copy_u32Ticks, void (*Copy_ptr)(void));
void	MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void (*Copy_ptr)(void));
void	MSTK_voidStopInterval();
u32		MSTK_u32GetElapsedTime();
u32		MSTK_u32GetRemainingTime();


#endif
