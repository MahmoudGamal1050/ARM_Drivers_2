/*********************************************************************
* File Name    	: 	main.c                                 			 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	13/9/2023                                        *
* Description   : 	LED Matrix							             *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "HAL/HLED_MATRIX/HLED_MATRIX_interface.h"
int main(void)
{

	/* Initialize RCC with AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);
	/* Enable RCC for GPIOB */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOB);

	/* Initialize STK with frequency equals AHB/8 or SYS_CLK/16 = 1MHz -> tickTime = 1us  */
	MSTK_voidInit(STK_AHB_Div_BY_8);
	HLEDMX_voidInit();


	u8 Hello[35] = {0x00,0x00,0x00,0x00,0x00,0xF8,0x20,0xF8,
					0x00,0xF8,0xA8,0xA8,0x00,0xF8,0x80,0x80,
					0x00,0xF8,0x80,0x80,0x00,0xF0,0x90,0xF0,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	while(1)
	{
		for(u8 i=0; i<24;i++)
		{
			for(u8 j=0; j<10;j++)
			{
				HLEDMX_voidDisplay(&Hello[i]);
			}
		}

	}
}



