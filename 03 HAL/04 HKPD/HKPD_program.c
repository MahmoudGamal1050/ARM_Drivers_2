/*********************************************************************
* File Name    	: 	HKPD_program.c                                   *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	13/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/


#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/MGPIO/MGPIO_interface.h"

#include "HAL/HKPD/HKPD_private.h"
#include "HAL/HKPD/HKPD_config.h"
#include "HAL/HKPD/HKPD_interface.h"

void HKPD_voidInit(void)
{
	/* Configure rows as input */
	MGPIO_voidSetPinMode(KPD_PORT, KPD_ROW1_PIN, GPIO_INPUT);
	MGPIO_voidSetPinMode(KPD_PORT, KPD_ROW2_PIN, GPIO_INPUT);
	MGPIO_voidSetPinMode(KPD_PORT, KPD_ROW3_PIN, GPIO_INPUT);
	MGPIO_voidSetPinMode(KPD_PORT, KPD_ROW4_PIN, GPIO_INPUT);
	/* Enable internal pull down for rows */
	MGPIO_voidSetInputState(KPD_PORT, KPD_ROW1_PIN, GPIO_INPUT_PULL_DOWN);
	MGPIO_voidSetInputState(KPD_PORT, KPD_ROW2_PIN, GPIO_INPUT_PULL_DOWN);
	MGPIO_voidSetInputState(KPD_PORT, KPD_ROW3_PIN, GPIO_INPUT_PULL_DOWN);
	MGPIO_voidSetInputState(KPD_PORT, KPD_ROW4_PIN, GPIO_INPUT_PULL_DOWN);
	
	/* Configure columns as output (Push_Pull output is default) */
	MGPIO_voidSetPinMode(KPD_PORT, KPD_COL1_PIN, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(KPD_PORT, KPD_COL2_PIN, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(KPD_PORT, KPD_COL3_PIN, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(KPD_PORT, KPD_COL4_PIN, GPIO_OUTPUT);

	
	/* Write high to all columns */
	MGPIO_voidSetPinValue(KPD_PORT, KPD_COL1_PIN, GPIO_HIGH);
	MGPIO_voidSetPinValue(KPD_PORT, KPD_COL2_PIN, GPIO_HIGH);
	MGPIO_voidSetPinValue(KPD_PORT, KPD_COL3_PIN, GPIO_HIGH);
	MGPIO_voidSetPinValue(KPD_PORT, KPD_COL4_PIN, GPIO_HIGH);


}
u8 HKPD_u8GetPressedKey(void)
{
	u8 Local_u8Row;		/* Variable to iterate rows */
	u8 Local_u8Col;		/* Variable to iterate columns */
	u8 Local_u8Key=0;	/* Variable to return pressed key */
	/* Loop for columns */
	for(Local_u8Col=0;Local_u8Col<KPD_COLS;Local_u8Col++)
	{
		/* Write low to this iteration column */
		MGPIO_voidSetPinValue(KPD_PORT, KPD_COL1_PIN+Local_u8Col, GPIO_HIGH);
		/* Loop for rows */
		for(Local_u8Row=0;Local_u8Row<KPD_ROWS;Local_u8Row++)
		{
			/* Check if there is a pressed key */
			if(MGPIO_u8GetPinValue(KPD_PORT, KPD_ROW1_PIN+Local_u8Row))
			{
				/* Get pressed key from array */
				Local_u8Key=KPD_Number[Local_u8Row][Local_u8Col];
				/* Wait until the key is released */
				while(MGPIO_u8GetPinValue(KPD_PORT, KPD_ROW1_PIN+Local_u8Row));
				//_delay_ms(10);
				break;
			}
		}
		/* Return the currnt column to high again */
		MGPIO_voidSetPinValue(KPD_PORT, KPD_COL1_PIN+Local_u8Col, GPIO_LOW);

	}

	return Local_u8Key;

}


