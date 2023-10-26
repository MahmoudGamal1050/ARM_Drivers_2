/*********************************************************************
* File Name    	: 	main.c                                 			 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	20/9/2023                                        *
* Description   : 	TFT test				  			             *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"


#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "MCAL/MSPI/MSPI_interface.h"

#include "HAL/HTFT/HTFT_interface.h"
#include "HAL/HTFT/image.h"

SPI_config_t SPI1Configuration =
{
	.Copy_uddtSPINumber	   = SPI1,
	.Copy_uddtMasterSlave  = MASTER,
	.Copy_uddtBaudeRate	   = F_CPU_DIV_BY_2,
	.Copy_uddtFrameFormat  = MSB_FIRST,
	.Copy_uddtDataSize     = _8_BIT_DATA,
	.Copy_uddtClockPhase   = SECOND_EDGE_CAPTURE,
	.Copy_uddtClockPolarity= IDLE_ONE,
	.Copy_uddtSSManagement = SW_SLAVE_MANAGEMENT
};

int main(void)
{

	/* Initialize RCC with AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);
	/* Enable RCC for GPIOB */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOB);
	/* Enable RCC for SPI1 */
	MRCC_voidEnablePeripheral(RCC_APB2, RCC_SPI1);

	MSTK_voidInit(STK_AHB_Div_BY_8);

	MSPI_voidInit(&SPI1Configuration);
	HTFT_voidInit();
	HTFT_voidDisplayImage(image);


	while(1)
	{



	}
}

