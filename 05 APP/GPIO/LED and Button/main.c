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
#include "../Inc/MCAL/MEXTI/MEXTI_interface.h"
#include "../Inc/MCAL/MNVIC/MNVIC_interface.h"
#include "../Inc/MCAL/MSTK/MSTK_interface.h"
#include "../Inc/HAL/HLED/HLED_interface.h"
#include "../Inc/HAL/HBUTTON/HBUTTON_interface.h"

void STK_ToggleLED(void);
int main(void)
{
	/* Initialize RCC with AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);
	/* Enable RCC for GPIOB */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOB);


	HLED_voidInit(GPIOA, GPIO_PIN0);
	HBUTTON_voidInit(GPIOB, GPIO_PIN0);
	HBUTTON_voidEnableInternalPullUpDown(GPIOB, GPIO_PIN0, INTERNAL_PULL_DOWN);

	while(1)
	{


		if(HBUTTON_u8GetValue(GPIOB, GPIO_PIN0))
		{
			while(HBUTTON_u8GetValue(GPIOB, GPIO_PIN0));
			HLED_voidWrite(GPIOA, GPIO_PIN0, LED_TOG);
		}


	}
}

