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
#include "MCAL/MNVIC/MNVIC_interface.h"
#include "MCAL/MUART/MUSART_interface.h"

USART_cfg_t uart =
{
		.Copy_uddtUsartNumber = USART1,
		.Copy_uddtSampling    = SAMPLING_BY_16,
		.Copy_uddtBuadRate    = BUAD_RATE_9600_bps,
		.Copy_uddtDataSize    = DATA_SIZE_8_BITS,
		.Copy_uddtParity      = PARITY_DISABLED,
		.Copy_uddtStopBits    = ONE_STOP_BIT
};

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
	MUSART_voidInit(&uart);
	MUSART_voidEnableDisable(USART1, TRANSMIT_RECEIVE_ENABLED);

	u8 L_u8Data = 'A';
	MUSART_voidSendBlocking(L_u8Data);

	while(1)
	{



	}
}

