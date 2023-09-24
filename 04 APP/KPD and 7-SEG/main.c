/*********************************************************************
* File Name    	: 	main.c                                 			 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	12/9/2023                                        *
* Description   : 	Keypad with Seven Segment  			             *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "HAL/HSSD/HSSD_interface.h"
#include "HAL/HKPD/HKPD_interface.h"



int main(void)
{

	/* Initialize RCC with AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);
	/* Enable RCC for GPIOB */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOB);

	/* Output pin PA8 to control first 7-segment */
	MGPIO_voidSetPinMode(GPIOA, GPIO_PIN8, GPIO_OUTPUT);
	MGPIO_voidSetPinValue(GPIOA, GPIO_PIN8, GPIO_HIGH);

	/* Initialize seven segment */
	HSSD_voidInit();
	HSSD_voidWrite(0);

	/* Initialize keypad */
	HKPD_voidInit();
	u8 Local_u8Key;
	while(1)
	{
		Local_u8Key = HKPD_u8GetPressedKey();
		if((Local_u8Key>='0') && (Local_u8Key<='9'))
		{
			HSSD_voidWrite(Local_u8Key-'0');

		}

	}
}



