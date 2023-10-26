/*********************************************************************
* File Name    	: 	main.c                                 			 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	19/9/2023                                        *
* Description   : 	UART test				  			             *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"


#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "MCAL/MUSART/MUSART_interface.h"
#include "MCAL/MNVIC/MNVIC_interface.h"

USART_cfg_t uart =
{
		.Copy_uddtUsartNumber = USART1,
		.Copy_uddtSampling    = SAMPLING_BY_16,
		.Copy_uddtBuadRate    = BUAD_RATE_9600_bps,
		.Copy_uddtDataSize    = DATA_SIZE_8_BITS,
		.Copy_uddtParity      = PARITY_DISABLED,
		.Copy_uddtStopBits    = ONE_STOP_BIT
};

void USART1_voidCallBackFun(void);
int main(void)
{

	/* Initialize RCC with AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);
	/* Enable RCC for GPIOB */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOB);
	/* Enable RCC for USART1 */
	MRCC_voidEnablePeripheral(RCC_APB2 , RCC_USART1);

	/* Set NVIC grouping as 16 groups and no subgroups */
	MNVIC_voidSetGroupingMode(GRB_16_SUB_00);
	/* Set interrupt priority for USART1*/
	MNVIC_voidSetIntPriority(NVIC_USART1, GRB_16_SUB_00, 1, 1);
	/* Enable interrupt for USART1 */
	MNVIC_voidEnablePerInt(NVIC_USART1);

	/* Set Pin Mode For Pins 9 , 10 -> Alternative Function */
	MGPIO_voidSetPinMode(GPIOA, GPIO_PIN9, GPIO_ALTF);    //TX-> USART1
	MGPIO_voidSetPinMode(GPIOA,GPIO_PIN10,GPIO_ALTF) ;   //RX-> USART1

	/* Set USART1 alternative function (ALTF7) for  For Pins 9 , 10  */
	MGPIO_voidSetAltFun(GPIOA,GPIO_PIN9,GPIO_ALTFN_7) ;                //TX-> USART1
	MGPIO_voidSetAltFun(GPIOA,GPIO_PIN10,GPIO_ALTFN_7) ;               //RX-> USART1


	MGPIO_voidSetPinMode(GPIOA, GPIO_PIN1, GPIO_OUTPUT);
	MGPIO_voidSetPinValue(GPIOA, GPIO_PIN1, GPIO_HIGH);
	MUSART_voidInit(&uart);
	MUSART_voidEnableDisable(USART1, TRANSMIT_RECEIVE_ENABLED);
	MUSART_voidSetCallBack(USART1,USART1_voidCallBackFun);
	MUSART_voidEnableInterrupt(USART1);


	while(1)
	{

	}
}


void USART1_voidCallBackFun(void)
{
	u8 recData;
	MGPIO_voidSetPinValue(GPIOA, GPIO_PIN1, GPIO_LOW);

	MUSART_u8ReceiveNonBlocking(&recData);
	if(recData== 'a')
	{
		MGPIO_voidSetPinValue(GPIOA, GPIO_PIN1, GPIO_LOW);
		MUSART_voidSendStringBlocking("Hello");
	}
	else if(recData=='b')
	{
		MGPIO_voidSetPinValue(GPIOA, GPIO_PIN1, GPIO_HIGH);
		MUSART_voidSendStringBlocking("HI");



	}

}
