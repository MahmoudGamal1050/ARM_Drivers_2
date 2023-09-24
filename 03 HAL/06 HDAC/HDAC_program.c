/*********************************************************************
* File Name    	: 	HDAC_program.c                              	 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	14/9/2023                                        *
* Description   : 			         				                 *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"

#include "HAL/HDAC/HDAC_private.h"
#include "HAL/HDAC/HDAC_config.h"
#include "HAL/HDAC/HDAC_interface.h"


void HDAC_voidWrie( u8 Copy_u8Data )
{

	MGPIO_voidSetPortValue(DAC_PORT, PORT_POSITION, Copy_u8Data);

}

void HDAC_voidInit( void )
{

	MGPIO_voidSetPortMode(DAC_PORT, PORT_POSITION, GPIO_OUTPUT);

}


