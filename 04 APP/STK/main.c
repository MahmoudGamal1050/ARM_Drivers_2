/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Gamal
 * @brief          : Main program body
 ******************************************************************************

 */

#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/MCAL/MRCC/MRCC_interface.h"
#include "../Inc/MCAL/MGPIO/MGPIO_interface.h"
#include "../Inc/MCAL/MEXTI/MEXTI_interface.h"
#include "../Inc/MCAL/MNVIC/MNVIC_interface.h"
#include "../Inc/MCAL/MSTK/MSTK_interface.h"
#include "../Inc/HAL/HLED/HLED_interface.h"

void STK_ToggleLED(void);
int main(void)
{
	/* Initialize RCC with AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);


	/* Configure PA0 as output */
	MGPIO_voidSetPinMode(GPIOA, GPIO_PIN0, GPIO_OUTPUT);
	/* Configure PA0 as output push_pull */
	MGPIO_voidSetOutputMode(GPIOA, GPIO_PIN0, GPIO_OUTPUT_PUSH_PULL);
	/* Configure PA0 as output high speed */
	MGPIO_voidSetOutputSpeed(GPIOA, GPIO_PIN0, GPIO_OUTPUT_SPEED_HIGH);

	/* Initialize STK with frequency equals AHB/8 or SYS_CLK/16 = 1MHz */
	MSTK_voidInit(STK_AHB_Div_BY_8);
	MSTK_voidSetIntervalPeriodic(1000000, STK_ToggleLED);
	while(1)
	{





	}
}
void STK_ToggleLED(void)
{
	/* Toggle LED on PA0 */
	MGPIO_voidTogglePin(GPIOA, GPIO_PIN0);
}

