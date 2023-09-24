/********************************************************************************/
/* File Name    	: 	HLED_program.c   		                                */
/* Author       	: 	Mahmoud Gamal                                           */
/* Version      	: 	1.0.0                                                   */
/* Date 		 	: 	08/19/2023                                              */
/********************************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/MGPIO/MGPIO_interface.h"

#include "HAL/HLED/HLED_private.h"
#include "HAL/HLED/HLED_config.h"
#include "HAL/HLED/HLED_interface.h"



/*********************************************************************************
***************************** Function Implementation ****************************
*********************************************************************************/

void HLED_voidInit(u8 Copy_u8PortName, u8 Copy_u8PinNum)
{
	/* Configure pin as output */
	MGPIO_voidSetPinMode(Copy_u8PortName, Copy_u8PinNum, GPIO_OUTPUT);
	/* Configure pin as output push_pull */
	MGPIO_voidSetOutputMode(Copy_u8PortName, Copy_u8PinNum, GPIO_OUTPUT_PUSH_PULL);
	/* Configure pin as output medium speed */
	MGPIO_voidSetOutputSpeed(Copy_u8PortName, Copy_u8PinNum, GPIO_OUTPUT_SPEED_MEDIUM);
}


void HLED_voidWrite(u8 Copy_u8PortName,u8 Copy_u8PinNum, u8 Copy_u8State)
{
	switch(Copy_u8State)
	{
		case LED_ON :
			/* Setting the pin value as high */
			MGPIO_voidSetPinValue(Copy_u8PortName, Copy_u8PinNum, LED_MODE);
			break;

		case LED_OFF:
			/* Setting the pin value as low */
			MGPIO_voidSetPinValue(Copy_u8PortName, Copy_u8PinNum, !LED_MODE);
			break;

		case LED_TOG:
			/* Setting the pin value as toggle */
			MGPIO_voidTogglePin(Copy_u8PortName, Copy_u8PinNum);
			break;
		

	}

}
