/*********************************************************************
* File Name    	: 	main.c                                 			 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	19/9/2023                                        *
* Description   : 	IR and LED matrix		  			             *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"


#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "MCAL/MNVIC/MNVIC_interface.h"
#include "MCAL/MEXTI/MEXTI_interface.h"
#include "HAL/HIR/HIR_interface.h"
#include "HAL/HLED/HLED_interface.h"
#include "HAL/HLED_MATRIX/HLED_MATRIX_interface.h"

int main(void)
{

	/* Initialize RCC with AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);
	/* Enable RCC for GPIOB */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOB);
	/* Enable RCC for SYSCFG to use external interrupt */
	MRCC_voidEnablePeripheral(RCC_APB2, RCC_SYSCFG);

	/* Set NVIC grouping as 16 groups and no subgroups */
	MNVIC_voidSetGroupingMode(GRB_00_SUB_16);

	HLED_voidInit(GPIOA, GPIO_PIN9);
	HLEDMX_voidInit();
	HIR_voidInit();
	/* Variable to receive data from IR remote */
	u8 L_ReceivedData;
	/* 2d array for numbers from 0 to 9 used to display numbers to 8*8 led matrix */
	u8 L_ArrNumbers[10][8] ={
						 {0x00, 0x38, 0x44, 0x44, 0x38, 0x00, 0x00, 0x00},	/* Number 0 */
						 {0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00, 0x00},  /* Number 1 */
						 {0x00, 0x79, 0x49, 0x49, 0x4F, 0x00, 0x00, 0x00},  /* Number 2 */
						 {0x00, 0x49, 0x49, 0x49, 0x7F, 0x00, 0x00, 0x00},  /* Number 3 */
						 {0x00, 0x0F, 0x08, 0x08, 0x7F, 0x00, 0x00, 0x00},  /* Number 4 */
						 {0x00, 0x4F, 0x49, 0x49, 0x79, 0x00, 0x00, 0x00},  /* Number 5 */
						 {0x00, 0x7F, 0x49, 0x49, 0x79, 0x00, 0x00, 0x00},  /* Number 6 */
						 {0x00, 0x03, 0x01, 0x01, 0x7F, 0x00, 0x00, 0x00},  /* Number 7 */
						 {0x00, 0x7F, 0x49, 0x49, 0x7F, 0x00, 0x00, 0x00},  /* Number 8 */
						 {0x00, 0x4F, 0x49, 0x49, 0x7F, 0x00, 0x00, 0x00}   /* Number 9 */
					   };

	/* Index for numbers array */
	u8 L_u8ArrIndex=0;


	while(1)
	{
		/* Keep displaying current number on led matrix */
		HLEDMX_voidDisplay(L_ArrNumbers[L_u8ArrIndex]);
		/* Get data from IR remote */
		L_ReceivedData = HIR_u8GetData();
		/* Change array index depending on pressed number */
		switch(L_ReceivedData)
		{
		case ZERO_BUTTON :
			L_u8ArrIndex=0;
			break;
		case ONE_BUTTON :
			L_u8ArrIndex=1;
			break;
		case TWO_BUTTON :
			L_u8ArrIndex=2;
			break;
		case THREE_BUTTON :
			L_u8ArrIndex=3;
			break;
		case FOUR_BUTTON :
			L_u8ArrIndex=4;
			break;
		case FIVE_BUTTON :
			L_u8ArrIndex=5;
			break;
		case SIX_BUTTON :
			L_u8ArrIndex=6;
			break;
		case SEVEN_BUTTON :
			L_u8ArrIndex=7;
			break;
		case EIGHT_BUTTON :
			L_u8ArrIndex=8;
			break;
		case NINE_BUTTON :
			L_u8ArrIndex=9;
			break;
		default :
			break;
		}


	}
}

