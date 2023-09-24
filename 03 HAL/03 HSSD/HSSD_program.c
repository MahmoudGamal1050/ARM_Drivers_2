/********************************************************************************/
/* File Name    	: 	HSSD_program.c   		                                */
/* Author       	: 	Mahmoud Gamal                                           */
/* Version      	: 	1.0.0                                                   */
/* Date 		 	: 	08/19/2023                                              */
/********************************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/MGPIO/MGPIO_interface.h"

#include "HAL/HSSD/HSSD_private.h"
#include "HAL/HSSD/HSSD_config.h"
#include "HAL/HSSD/HSSD_interface.h"

/* Array with 7-segment numbers combinations */
u8 SSD_Nums[10] = 
{
	0x3F, 0x06,
	0x5B, 0x4F, 
	0x66, 0x6D, 
	0x7D, 0x07, 
	0x7F, 0x6F
};
void HSSD_voidInit(void)
{
	/* Set 7-segment pins as output */
	MGPIO_voidSetPinMode(SSD_PORT, SSD_A, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(SSD_PORT, SSD_B, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(SSD_PORT, SSD_C, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(SSD_PORT, SSD_D, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(SSD_PORT, SSD_E, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(SSD_PORT, SSD_F, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(SSD_PORT, SSD_G, GPIO_OUTPUT);

}
void HSSD_voidWrite(u8 copy_u8Num)
{
	u8 local_u8FirstDigit = copy_u8Num%10;

	#if (SSD_COMMON == SSD_CATHODE)
		MGPIO_voidSetPinValue(SSD_PORT, SSD_A, GET_BIT(SSD_Nums[local_u8FirstDigit],0));
		MGPIO_voidSetPinValue(SSD_PORT, SSD_B, GET_BIT(SSD_Nums[local_u8FirstDigit],1));
		MGPIO_voidSetPinValue(SSD_PORT, SSD_C, GET_BIT(SSD_Nums[local_u8FirstDigit],2));
		MGPIO_voidSetPinValue(SSD_PORT, SSD_D, GET_BIT(SSD_Nums[local_u8FirstDigit],3));
		MGPIO_voidSetPinValue(SSD_PORT, SSD_E, GET_BIT(SSD_Nums[local_u8FirstDigit],4));
		MGPIO_voidSetPinValue(SSD_PORT, SSD_F, GET_BIT(SSD_Nums[local_u8FirstDigit],5));
		MGPIO_voidSetPinValue(SSD_PORT, SSD_G, GET_BIT(SSD_Nums[local_u8FirstDigit],6));

	#elif (SSD_COMMON == SSD_ANODE)

		MGPIO_voidSetPinValue(SSD_PORT, SSD_A, !GET_BIT(SSD_Nums[local_u8FirstDigit],0));
		MGPIO_voidSetPinValue(SSD_PORT, SSD_B, !GET_BIT(SSD_Nums[local_u8FirstDigit],1));
		MGPIO_voidSetPinValue(SSD_PORT, SSD_C, !GET_BIT(SSD_Nums[local_u8FirstDigit],2));
		MGPIO_voidSetPinValue(SSD_PORT, SSD_D, !GET_BIT(SSD_Nums[local_u8FirstDigit],3));
		MGPIO_voidSetPinValue(SSD_PORT, SSD_E, !GET_BIT(SSD_Nums[local_u8FirstDigit],4));
		MGPIO_voidSetPinValue(SSD_PORT, SSD_F, !GET_BIT(SSD_Nums[local_u8FirstDigit],5));
		MGPIO_voidSetPinValue(SSD_PORT, SSD_G, !GET_BIT(SSD_Nums[local_u8FirstDigit],6));

	#endif




}


