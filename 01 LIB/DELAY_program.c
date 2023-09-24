/*********************************************************************
* File Name    	: 	DELAY_program.c	     		                     *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	13/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "LIB/DELAY_interface.h"

#include "MCAL/MSTK/MSTK_interface.h"



void _delay_ms( u32 Copy_u32Time )
{

	MSTK_voidInit(STK_AHB_Div_BY_8);
	MSTK_voidSetBusyWait(Copy_u32Time * 1000);

}


void _delay_us( u32 Copy_u32Time )
{

	MSTK_voidInit(STK_AHB_Div_BY_8);
	MSTK_voidSetBusyWait(Copy_u32Time);

}
