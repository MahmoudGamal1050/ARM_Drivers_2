/*********************************************************************
* File Name    	: 	HTFT_program.c                                   *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	20/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/MGPIO/MGPIO_interface.h"

#include "MCAL/MSPI/MSPI_private.h"
#include "MCAL/MSPI/MSPI_config.h"
#include "MCAL/MSPI/MSPI_interface.h"


void MSPI_voidInit(SPI_config_t const *PS_uddtSPIConfig)
{
	switch(PS_uddtSPIConfig ->Copy_uddtSPINumber)
	{
	case SPI1 :
		MGPIO_voidSetPinMode(GPIOA, GPIO_PIN5, GPIO_ALTF);
		MGPIO_voidSetAltFun(GPIOA, GPIO_PIN5, GPIO_ALTFN_5);
		MGPIO_voidSetPinMode(GPIOA, GPIO_PIN6, GPIO_ALTF);
		MGPIO_voidSetAltFun(GPIOA, GPIO_PIN6, GPIO_ALTFN_5);
		MGPIO_voidSetPinMode(GPIOA, GPIO_PIN7, GPIO_ALTF);
		MGPIO_voidSetAltFun(GPIOA, GPIO_PIN7, GPIO_ALTFN_5);

		/* Clear SPI_CR1 before writing to it */
		MSPI1->CR1 = 0;
		MSPI1->CR1 |= (PS_uddtSPIConfig->Copy_uddtMasterSlave <<MSTR) | (PS_uddtSPIConfig->Copy_uddtBaudeRate <<BR0) |
				(PS_uddtSPIConfig->Copy_uddtFrameFormat <<LSBFIRST) | (PS_uddtSPIConfig->Copy_uddtDataSize <<DFF) |
				(PS_uddtSPIConfig->Copy_uddtClockPhase <<CPHA) | (PS_uddtSPIConfig->Copy_uddtClockPolarity <<CPOL) |
				(PS_uddtSPIConfig->Copy_uddtSSManagement <<SSI) | (1<<SPE);


		/* CPOL =1 / CPHA = 1 / Prescaller = Clk/2 / SPI Enable / MSB First */
		//MSPI1->CR1 = 0x0347;

		break;

	default :
		break;
	}


}

void MSPI_voidSendReceiveSynch(SPI_Number_t Copy_uddtSPINumber,  u8 *Copy_PtrDataToExchange)
{
		switch(Copy_uddtSPINumber)
	{
	case SPI1 :
		/* Clear For Slave Select Pin */
		MGPIO_voidSetPinValue(MSPI1_SLAVE_PIN,GPIO_LOW);

		/* Send Data */
		MSPI1 -> DR = *Copy_PtrDataToExchange;

		/* Wait Busy Flag to finish */
		while (GET_BIT(MSPI1 -> SR, BSY) == 1);

	 	/* Return to the received data */
		*Copy_PtrDataToExchange = MSPI1 -> DR;

		/* Set Salve Select Pin */
		MGPIO_voidSetPinValue(MSPI1_SLAVE_PIN,GPIO_HIGH);
		break;

	default :
		break;
	}

}

