/********************************************************************************/
/* File Name    	: 	HBUTTON_program.c   		                                */
/* Author       	: 	Mahmoud Gamal                                           */
/* Version      	: 	1.0.0                                                   */
/* Date 		 	: 	08/19/2023                                              */
/********************************************************************************/


#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/MGPIO/MGPIO_interface.h"

#include "HAL/HBUTTON/HBUTTON_private.h"
#include "HAL/HBUTTON/HBUTTON_config.h"
#include "HAL/HBUTTON/HBUTTON_interface.h"



/*********************************************************************************
***************************** Function Implementation ****************************
*********************************************************************************/

void HBUTTON_voidInit(u8 Copy_u8PortName, u8 Copy_u8PinNum)
{
	/* Configure Pin as input */
	MGPIO_voidSetPinMode(Copy_u8PortName, Copy_u8PinNum, GPIO_INPUT);
}


void HBUTTON_voidEnableInternalPullUpDown(u8 Copy_u8PortName, u8 Copy_u8PinNum, u8 Copy_u8PullState)
{
	/* Enable internal pull up for PB1 */
	MGPIO_voidSetInputState(Copy_u8PortName, Copy_u8PinNum, Copy_u8PullState);
}


u8 HBUTTON_u8GetValue(u8 Copy_u8PortName, u8 Copy_u8PinNum)
{
	return MGPIO_u8GetPinValue(Copy_u8PortName, Copy_u8PinNum);
}
