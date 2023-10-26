/*********************************************************************
* File Name    	: 	MSUART_program.c                               	 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	19/9/2023                                        *
* Description   : 			         				                 *
**********************************************************************/


#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/MGPIO/MGPIO_interface.h"

#include <MCAL/MUSART/MUSART_private.h>
#include <MCAL/MUSART/MUSART_config.h>
#include <MCAL/MUSART/MUSART_interface.h>


void (*USART_CallBackPtr[3])(void);


void MUSART_voidInit(USART_cfg_t const *PS_uddtUsartCfg)
{

	//f64 L_f64Mantissa;
	//f32 L_f32Fraction;
//	L_f64Mantissa = (f64)USART_CLK / (8*(2-PS_uddtUsartCfg-> Copy_uddtSampling) * PS_uddtUsartCfg->Copy_uddtBuadRate);
//	L_f32Fraction = L_f64Mantissa - (u32)L_f64Mantissa;
//
//	if(L_f32Fraction > 0)
//	{
//		L_f32Fraction *=16;
//		L_f32Fraction = (L_f32Fraction - (u32)L_f32Fraction)>=0.5 ? (u32)L_f32Fraction+1 : (u32)L_f32Fraction;
//	}

	switch(PS_uddtUsartCfg->Copy_uddtUsartNumber)
	{
		case USART1:
		{

			//MUSART1 -> BRR = L_f32Fraction;
			//MUSART1 -> BRR |= ((u32)L_f64Mantissa << DIV_MANTISSA0);
			MUSART1 -> BRR = 0x683;
			MUSART1 -> CR1 = 0;
			MUSART1 -> CR1 |= (PS_uddtUsartCfg->Copy_uddtSampling << OVER8)
						    | (PS_uddtUsartCfg->Copy_uddtDataSize  << M)
					        | (PS_uddtUsartCfg->Copy_uddtParity   << PS);


			MUSART1 -> CR2 = 0;

			MUSART1->CR2 |= (PS_uddtUsartCfg->Copy_uddtStopBits  << STOP0);
		    MUSART1->SR = 0;



			break;
		}

		case USART2:
		{

			//MUSART2 -> BRR = L_f32Fraction;
			//MUSART2 -> BRR |= ((u32)L_f64Mantissa << DIV_MANTISSA0);
			MUSART2 -> BRR = 0xD06;
			MUSART2 -> CR1 = 0;
			MUSART2 -> CR1 |= (PS_uddtUsartCfg->Copy_uddtSampling << OVER8)
						    | (PS_uddtUsartCfg->Copy_uddtDataSize  << M)
					        | (PS_uddtUsartCfg->Copy_uddtParity   << PS);



			MUSART2 -> CR2 = 0;

			MUSART2->CR2 |= (PS_uddtUsartCfg->Copy_uddtStopBits  << STOP0);

			break;
		}

		case USART6:
		{

			//MUSART6 -> BRR = L_f32Fraction;
			//MUSART6 -> BRR |= ((u32)L_f64Mantissa << DIV_MANTISSA0);
			MUSART6 -> BRR = 0xD06;
			MUSART6 -> CR1 = 0;
			MUSART6 -> CR1 |= (PS_uddtUsartCfg->Copy_uddtSampling << OVER8)
						    | (PS_uddtUsartCfg->Copy_uddtDataSize  << M)
					        | (PS_uddtUsartCfg->Copy_uddtParity   << PS);


			MUSART6 -> CR2 = 0;

			MUSART6->CR2 |= (PS_uddtUsartCfg->Copy_uddtStopBits  << STOP0);


			break;
		}
		default:
			break;

	}
}

void MUSART_voidEnableDisable(USART_Number_t Copy_uddtUsartNumber, USART_State_t Copy_uddtState)
{

	switch(Copy_uddtUsartNumber)
	{
		case USART1 :
		{
			MUSART1->CR1 = ((MUSART1->CR1 & 0xFFF3) | (Copy_uddtState << RE) | (1<<UE));
			break;
		}

		case USART2 :
		{
			MUSART2->CR1 = ((MUSART2->CR1 & 0xFFF3) | (Copy_uddtState << RE));
			break;
		}

		case USART6 :
		{
			MUSART6->CR1 = ((MUSART6->CR1 & 0xFFF3) | (Copy_uddtState << RE));
			break;
		}
	}

}

void MUSART_voidSendNonBlocking(u8 Copy_u8Data)
{
	MUSART1 -> DR = Copy_u8Data;

}



void MUSART_voidSendBlocking(u8 Copy_u8Data)
{

	MUSART1 -> DR = Copy_u8Data;
	/* Wait until transmit is complete */
	while(GET_BIT(MUSART1-> SR , TC) == 0);

}

void MUSART_voidSendStringBlocking(char *Str)
{
	u8 Local_u8counter = 0;	/* Counter to parse the whole string */
	/* Loop until reaching null terminator */
	while(Str[Local_u8counter] != '\0')
	{
		/* Send character through UART */
		MUSART_voidSendBlocking(Str[Local_u8counter]);
		Local_u8counter++;	/* Increment the counter */
	}

}

void   MUSART_voidReceiveBlocking(u8 *Copy_u8ptrData)
{
	while(GET_BIT(MUSART1 -> SR , RXNE) == 0);

	*Copy_u8ptrData =  (u8)MUSART1->DR;
}

u8   MUSART_u8ReceiveNonBlocking(u8 *Copy_u8ptrData)
{
	u8 L_u8State=1;
	if((GET_BIT(MUSART1->SR, RXNE)) == 1)
	{
		*Copy_u8ptrData = MUSART1->DR;
	}
	else
	{
		L_u8State=0;
	}
	return L_u8State;

}

void MUSART_voidEnableInterrupt(USART_Number_t Copy_uddtUsartNumber)
{
	SET_BIT(MUSART1->CR1,RXNEIE);
}

void MUSART_voidDisableInterrupt(USART_Number_t Copy_uddtUsartNumber)
{
	CLR_BIT(MUSART1->CR1,RXNEIE);

}
void MUSART_voidSetCallBack(USART_Number_t Copy_uddtUsartNumber, void ( *Ptr ) ( void ) )
{
	USART_CallBackPtr[Copy_uddtUsartNumber] = Ptr;
}

void USART1_IRQHandler(void)
{
	USART_CallBackPtr[0]();
}
