/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Gamal
 * @brief          : Main program body
 ******************************************************************************

 */

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MEXTI/MEXTI_interface.h"
#include "MCAL/MNVIC/MNVIC_interface.h"
/* Call back function for EXTI0 */
void EXTI0_CallBackFunction(void);

int main(void)
{
	/* Initialize RCC */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);
	/* Enable RCC for GPIOB */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOB);
	/* Enable RCC for SYSCFG to use external interrupt */
	MRCC_voidEnablePeripheral(RCC_APB2, RCC_SYSCFG);

	/* Configure PA1 as output */
	MGPIO_voidSetPinMode(GPIOA, GPIO_PIN1, GPIO_OUTPUT);
	/* Configure PA1 as output push_pull */
	MGPIO_voidSetOutputMode(GPIOA, GPIO_PIN1, GPIO_OUTPUT_PUSH_PULL);
	/* Configure PA1 as output high speed */
	MGPIO_voidSetOutputSpeed(GPIOA, GPIO_PIN1, GPIO_OUTPUT_SPEED_HIGH);

	/* Configure PA0 as input */
	MGPIO_voidSetPinMode(GPIOA, GPIO_PIN0, GPIO_INPUT);
	/* Enable internal pull up for PA0 */
	MGPIO_voidSetInputState(GPIOA, GPIO_PIN0, GPIO_INPUT_PULL_UP);

	/* Set interrupt priority grouping mode */
	MNVIC_voidSetGroupingMode(GRB_00_SUB_16);
	/* Enable interrupt for EXTI0 */
	MNVIC_voidEnablePerInt(NVIC_EXTI0);
	/* SEt EXTI0 group and subgroup priorities by 1 */
	MNVIC_voidSetIntPriority(NVIC_EXTI0,GRB_00_SUB_16,1,1);
	/* Set callback function for EXTI0 */
	MEXTI_voidSetCallBack(EXTI0_CallBackFunction);
	/* Enable EXTI1 */
	MEXTI_voidEnableEXTI(EXTI_LINE0);
	/* Set EXTI configuration for PB1 */
	MEXTI_voidSetEXTIConfig(EXTI_LINE0, EXTI_PORTB);
	/* Set sensing trigger for EXTI1 as falling edge */
	MEXTI_voidSetTriggerSource(EXTI_LINE0, EXTI_FALLING_EDGE);

	while(1)
	{




	}
}

void EXTI0_CallBackFunction(void)
{
	/* Toggle PA1 LED when EXTI0 occurs (button at PA0 is pressed) */
	MGPIO_voidTogglePin(GPIOA, GPIO_PIN1);

}
