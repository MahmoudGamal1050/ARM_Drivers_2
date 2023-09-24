/*********************************************************************
* File Name    	: 	main.c                                 			 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	12/9/2023                                        *
* Description   : 	Seven Segment Count up using SysTick             *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "HAL/HSSD/HSSD_interface.h"

/* Global variable for counting up */
u8 Global_u8Count=0;
/* Function to write 2-digit count to 7-segments by multiplexing */
void SSD_voidWriteCount(void);
/* Function to update count every 1s */
void SSD_voidUpdateCount(void);
int main(void)
{

	/* Initialize RCC with AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);

	/* Output pin PA8 to control first 7-segment */
	MGPIO_voidSetPinMode(GPIOA, GPIO_PIN8, GPIO_OUTPUT);

	/* Output pin PA9 to control second 7-segment */
	MGPIO_voidSetPinMode(GPIOA, GPIO_PIN9, GPIO_OUTPUT);

	/* Initialize seven segment */
	HSSD_voidInit();

	/* Initialize STK with frequency equals AHB/8 or SYS_CLK/16 = 1MHz -> tickTime = 1us  */
	MSTK_voidInit(STK_AHB_Div_BY_8);
	/* Set callBack function to update count every 1S(1000000* 1us) */
	MSTK_voidSetIntervalPeriodic(1000000, SSD_voidUpdateCount);

	while(1)
	{
		/* Write count to 7-segment */
		SSD_voidWriteCount();
	}
}

void SSD_voidUpdateCount(void)
{
	/* Increment count every 1s */
	Global_u8Count++;
	if(Global_u8Count==100)
	{
		Global_u8Count = 0;
	}
}


void SSD_voidWriteCount(void)
{
	/* Variable to save SysTick remaining time */
	static u32 Local_u32RemainingTime;
	/* Disable both 7-segments */
	MGPIO_voidSetPinValue(GPIOA, GPIO_PIN8, GPIO_LOW);
	MGPIO_voidSetPinValue(GPIOA, GPIO_PIN9, GPIO_LOW);

	/* Write first digit to first 7-segment */
	HSSD_voidWrite(Global_u8Count%10);
	/* Enable first 7-segment */
	MGPIO_voidSetPinValue(GPIOA, GPIO_PIN8, GPIO_HIGH);
	/* Get SysTick remaining time to calculate 5ms for 7-segment multiplexing */
	Local_u32RemainingTime = MSTK_u32GetRemainingTime();
	/* Busy wait for 5000 ticks(5ms) */
	while((Local_u32RemainingTime - MSTK_u32GetRemainingTime())<= 5000);
	/* Disable both 7-segments */
	MGPIO_voidSetPinValue(GPIOA, GPIO_PIN8, GPIO_LOW);
	MGPIO_voidSetPinValue(GPIOA, GPIO_PIN9, GPIO_LOW);
	/* Write second digit to second 7-segment */
	HSSD_voidWrite(Global_u8Count/10);
	/* Enable second 7-segment */
	MGPIO_voidSetPinValue(GPIOA, GPIO_PIN9, GPIO_HIGH);
	/* Get SysTick remaining time */
	Local_u32RemainingTime = MSTK_u32GetRemainingTime();
	/* Busy wait for 5000 ticks(5ms) */
	while((Local_u32RemainingTime - MSTK_u32GetRemainingTime())<= 5000);

}

