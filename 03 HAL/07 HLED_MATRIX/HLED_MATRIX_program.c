/*********************************************************************
* File Name    	: 	HLED_MATRIX_program.h                            *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	13/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"

#include "HAL/HLED_MATRIX/HLED_MATRIX_private.h"
#include "HAL/HLED_MATRIX/HLED_MATRIX_config.h"
#include "HAL/HLED_MATRIX/HLED_MATRIX_interface.h"


void HLEDMX_voidInit(void)
{
	MGPIO_voidSetPortMode(LEDMX_ROWS_PORT,LOW_PINS, GPIO_OUTPUT);
	MGPIO_voidSetPortMode(LEDMX_COLS_PORT,LOW_PINS, GPIO_OUTPUT);

}

void HLEDMX_voidDisplay( u8 * arr )
{
	u8 Local_u8Counter;
	for( Local_u8Counter  = 0 ; Local_u8Counter < 8 ; Local_u8Counter++ )
	{
		MGPIO_voidSetPortValue(LEDMX_ROWS_PORT,LOW_PINS, arr[Local_u8Counter]);
		MGPIO_voidSetPinValue(LEDMX_COLS_PORT, Local_u8Counter, GPIO_LOW);
		MSTK_voidSetBusyWait(2500);
		MGPIO_voidSetPinValue(LEDMX_COLS_PORT, Local_u8Counter, GPIO_HIGH);


	}

}
