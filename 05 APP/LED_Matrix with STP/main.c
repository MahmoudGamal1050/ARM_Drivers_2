/*********************************************************************
* File Name    	: 	main.c                                 			 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	27/9/2023                                        *
* Description   : 	LED Matrix using serial to parallel	             *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"


#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"

#include "HAL/HSTP/HSTP_interface.h"

int main(void)
{
	u16 L_u16SendData;
	u8 L_u8Counter1,L_u8Counter2,L_u8Counter3;

	u8 Hello[35] = {0x00,0x00,0x00,0x00,0x00,0xF8,0x20,0xF8,
					0x00,0xF8,0xA8,0xA8,0x00,0xF8,0x80,0x80,
					0x00,0xF8,0x80,0x80,0x00,0xF0,0x90,0xF0,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	/* Initialize RCC with AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);
	/* Initialize STK with frequency equals AHB/8 or SYS_CLK/16 = 1MHz -> tickTime = 1us  */
	MSTK_voidInit(STK_AHB_Div_BY_8);
	/* Initialize STP */
	HSTP_voidInit();

	while(1)
	{
		/* Outer loop to parse the HELLO array */
		for(u8 L_u8Counter1=0; L_u8Counter1<24;L_u8Counter1++)
		{
			/* Second loop to keep lED matrix on for some time */
			for(u8 L_u8Counter2=0; L_u8Counter2<10;L_u8Counter2++)
			{
				/* Inner loop to display on LED Matrix */
				for (L_u8Counter3=0;L_u8Counter3<8;L_u8Counter3++)
				{
					/* Get 8-bits of the array(for the rows) and pull current column low */
					Loc_u16SendingData=((u16)(~(1<<(8+L_u8Counter1))) &(0xFF00)) |(u16) Hello[L_u8Counter1];
					/* Send 16bits through serial to parallel */
					HSTP_voidSendTwoBytesSynch(Loc_u16SendingData);
					/* Wait for 2.5ms */
					MSTK_voidSetBusyWait(2500);


				}
			}
		}



	}
}

