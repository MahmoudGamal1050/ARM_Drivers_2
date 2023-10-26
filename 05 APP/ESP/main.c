/*********************************************************************
* File Name    	: 	main.c                                 			 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	19/9/2023                                        *
* Description   : 	ESP test				  			             *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"


#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "MCAL/MUSART/MUSART_interface.h"
#include "HAL/HESP/HESP_interface.h"
#include "HAL/HLED/HLED_interface.h"

USART_cfg_t uart =
{
		.Copy_uddtUsartNumber = USART1,
		.Copy_uddtSampling    = SAMPLING_BY_16,
		.Copy_uddtBuadRate    = BUAD_RATE_115200_bps,
		.Copy_uddtDataSize    = DATA_SIZE_8_BITS,
		.Copy_uddtParity      = PARITY_DISABLED,
		.Copy_uddtStopBits    = ONE_STOP_BIT
};

int main(void)
{
	/* Create Variable To Receive Data From Server */
	u8 LOC_u8Data = 0;

	/* Initialize RCC with AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);
	/* Enable RCC for GPIOB */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOB);
	/* Enable RCC for USART1 */
	MRCC_voidEnablePeripheral(RCC_APB2 , RCC_USART1);
	MUSART_voidInit(&uart);
	MUSART_voidEnableDisable(USART1, TRANSMIT_RECEIVE_ENABLED);

	MSTK_voidInit(STK_AHB_Div_BY_8);

	HESP_voidInit();
	HESP_voidConnectToWifi("Android", "10501050");

	MGPIO_voidSetPinMode(GPIOA, GPIO_PIN0, GPIO_OUTPUT);
	while(1)
	{
		HESP_voidConnectToServer("23.179.32.37", "80");
		HESP_voidReceiveHTTPRequest("gabagool.freevar.com/status.txt", "44");

		/* We Receive ASCII So We Will Subtract 48 From Data Come */
		MGPIO_voidSetPinValue( GPIOA , GPIO_PIN0 , LOC_u8Data - 48 );
	}
}

