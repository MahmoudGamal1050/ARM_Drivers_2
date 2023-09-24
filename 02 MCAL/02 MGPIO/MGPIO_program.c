/*********************************************************************
* File Name    	: 	MGPIO_program.c                                 	 
* Author       	: 	Mahmoud Gamal                                    
* Version      	: 	1.0.0                                            
* Date  		: 	7/9/2023                                         
* Description   : 	MGPIO_program.c  ->  Implementation	         				                                      
* Module Features :
						01- MGPIO_voidSetPinMode
						02- MGPIO_voidSetPortMode
						03- MGPIO_voidSetOutputMode
						04- MGPIO_voidSetOutputSpeed
						05- MGPIO_voidSetInputState
						06- MGPIO_u8GetPinValue
						07- MGPIO_voidSetPinValue
						08- MGPIO_voidDirectSetReset
						09- MGPIO_voidTogglePin
						10- MGPIO_voidPinLock
						11- MGPIO_voidSetPortValue
						12- MGPIO_voidSetPinAltFun
						
*/



/***************************************************************************/
/********************** Standard Types *************************************/
/***************************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

/***************************************************************************/
/********************** MCAL Components ************************************/
/***************************************************************************/

#include "MCAL/MGPIO/MGPIO_private.h"
#include "MCAL/MGPIO/MGPIO_config.h"
#include "MCAL/MGPIO/MGPIO_interface.h"


/***************************************************************************/
/********************** Functions Implementation ***************************/
/***************************************************************************/


/*********************************************************************************************************/
/*										 01 - MGPIO_voidSetPinMode  									 */
/*-------------------------------------------------------------------------------------------------------*/
/*	1-  Function Description ->  function Set the mode of the Pin                                        */
/*	2-  Options : (A) MGPIO_MODE_INPUT                                                                   */
/*				  (B) MGPIO_MODE_OUTPUT                                                                  */
/*				  (C) MGPIO_MODE_ALTF                                                                    */
/*				  (D) MGPIO_MODE_ANALOG                                                                  */
/*				                                                                                         */
/*	3- Function Arguments : (A)  Copy_u8PortName  : The port Number (ex : GPIOA , GPIOB)     */
/*							(B)	 Copy_u8PinNum    : The Pin Number (ex : MGPIO_PIN0 , MGPIO_PIN1)        */
/*							(C)  Copy_u8Mode      : The Mode (ex : MGPIO_MODE_INPUT)                     */
/*	                                                                                                     */
/*	4- Function Return   ->  void																	     */
/*********************************************************************************************************/
void MGPIO_voidSetPinMode (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8Mode)
{
	if (Copy_u8PinNum < 16)
	{

		switch (Copy_u8PortName)
		{
			case GPIOA  :
				MGPIOA->MODER &= ~(0x3 << (2U * Copy_u8PinNum));
				MGPIOA->MODER |= (Copy_u8Mode << (2U * Copy_u8PinNum)) ;
				break;
			case GPIOB  :
				MGPIOB->MODER &= ~(0x3 << (2U * Copy_u8PinNum));
				MGPIOB->MODER |= (u32)(Copy_u8Mode << (2U * Copy_u8PinNum)) ;
				break;

			case GPIOC  :
				MGPIOC->MODER &= ~(0x3 << (2U * Copy_u8PinNum));
				MGPIOC->MODER |= (u32)(Copy_u8Mode << (2U * Copy_u8PinNum)) ;
				break;

			default :
			/* Error : Wrong Port */
			break;
		}

	}

	else
	{
		/* Report error pin number out of boundary */
	}

}




/*********************************************************************************************************/
/*										 02 - MGPIO_voidSetPortMode  									 */
/*-------------------------------------------------------------------------------------------------------*/
/**                                                                                                      */
/*	1-  function Description ->  function Set the mode of the Port                                       */
/*	2-  Options : 																						 */
/*  			  (A) GPIO_INPUT                                                        	             */
/*				  (B) GPIO_OUTPUT       	                                                             */
/*				  (C) GPIO_ALTF             	                                                         */
/*				  (D) GPIO_ANALOG               	                                                     */
/*				                                                                                         */
/*	3- Function Arguments : (A)  Copy_u8PortName  : The port Number (ex : GPIOA , GPIOB)  			     */
/*							(B)  Copy_u8Mode      : The Mode (ex : GPIO_INPUT)  			             */
/*	                                                                                                     */
/*	4- Function Return   ->  void                                                                        */
/*	                                                                                                     */
/*********************************************************************************************************/
void MGPIO_voidSetPortMode (u8 Copy_u8PortName ,u8 Copy_u8Position, u8 Copy_u8Mode)
{
	switch (Copy_u8PortName)
	{
		case GPIOA  :
			if(Copy_u8Position== LOW_PINS)
			{
				MGPIOA->MODER &= 0xFFFF0000 ;
				MGPIOA->MODER |=(0x00005555 * Copy_u8Mode);
			}
			else if (Copy_u8Position== HIGH_PINS)
			{
				MGPIOA->MODER &= 0x0000FFFF ;
				MGPIOA->MODER |=(0x55550000 * Copy_u8Mode);

			}
			break;

		case GPIOB  :
			if(Copy_u8Position== LOW_PINS)
			{
				MGPIOB->MODER &= 0xFFFF0000 ;
				MGPIOB->MODER |=(0x00005555 * Copy_u8Mode);
			}
			else if (Copy_u8Position== HIGH_PINS)
			{
				MGPIOB->MODER &= 0x0000FFFF ;
				MGPIOB->MODER |=(0x55550000 * Copy_u8Mode);

			}
			break;

		default :
		/* Error : Wrong Port */
		break;
	}


}


/*******************************************************************************************************/
/*                                      03- MGPIO_voidSetOutputMode                                    */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set The output mode Of Pin  Take Bits                           */
/*                                                                                                     */
/*      1- PUSH_PULL                                                                                   */
/*      2- OPEN_DRAIN                                                                                  */
/*                                                                                                     */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8OutputMode                  */
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/


void MGPIO_voidSetOutputMode (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8OutputMode )
{
	if (Copy_u8PinNum < 16)
	{
		switch (Copy_u8PortName)
		{
			case GPIOA  :  MGPIOA->OTYPER |= (u32)(Copy_u8OutputMode << ( Copy_u8PinNum)) ;  break;

			case GPIOB  :  MGPIOB->OTYPER |= (u32)(Copy_u8OutputMode << ( Copy_u8PinNum)) ;  break;

			case GPIOC  :  MGPIOC->OTYPER |= (u32)(Copy_u8OutputMode << ( Copy_u8PinNum)) ;  break;

			default :
			/* Error : Wrong Port */
			break;
		}
	}
	else
	{
		/* Report error pin number out of boundary */
	}
}


/*******************************************************************************************************/
/*                                      04- MGPIO_voidSetOutputSpeed                                   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set The output speed  Of Pin Mode Take 2Bits                    */
/*                                                                                                     */
/*      1- LOW_SPEED   		  8 MHZ                                                                    */
/*      2- MEDUIM_SPEED 	  50 MHZ                                                                   */
/*      3- HIGH_SPEED    	  80 MHZ                                                                   */
/*      4- VERY_HIGH_SPEED	  180 MHZ                                                                  */
/*																								       */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8OutputSpeed                 */
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/


void MGPIO_voidSetOutputSpeed  (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8OutputSpeed )
{
	if (Copy_u8PinNum < 16)
	{
		switch (Copy_u8PortName)
		{
			case GPIOA  :  MGPIOA->OSPEEDR |= (u32)(Copy_u8OutputSpeed << ( 2U * Copy_u8PinNum)) ;  break;

			case GPIOB  :  MGPIOB->OSPEEDR |= (u32)(Copy_u8OutputSpeed << ( 2U * Copy_u8PinNum)) ;  break;

			case GPIOC  :  MGPIOC->OSPEEDR |= (u32)(Copy_u8OutputSpeed << ( 2U * Copy_u8PinNum)) ;  break;

			default :
			/* Error : Wrong Port */
			break;
		}
	}
	else
	{
		/* Report error pin number out of boundary */
	}

}

/*******************************************************************************************************/
/*                                      05- MGPIO_voidSetInputState                                     */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set The Resistor connection state of pin Take 2Bits             */
/*                                                                                                     */
/*      1- INPUT_FLOATING                                                                                  */
/*      2- INPUT_UP                                                                                     */
/*      3- INPUT_DOWN                                                                                   */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8InputState                   */
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/

void MGPIO_voidSetInputState  (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8InputState )
{
	if (Copy_u8PinNum < 16)
	{
		switch (Copy_u8PortName)
		{
			case GPIOA  :
				MGPIOA->PUPDR &= ~(1 << ( 2U * Copy_u8PinNum)) ;
				MGPIOA->PUPDR |= (Copy_u8InputState << ( 2U * Copy_u8PinNum)) ;
				break;

			case GPIOB  :
				MGPIOB->PUPDR &= ~(1 << ( 2U * Copy_u8PinNum)) ;
				MGPIOB->PUPDR |= (u32)(Copy_u8InputState << ( 2U * Copy_u8PinNum)) ;
				break;

			case GPIOC  :
				MGPIOC->PUPDR &= ~(1 << ( 2U * Copy_u8PinNum)) ;
				MGPIOC->PUPDR |= (u32)(Copy_u8InputState << ( 2U * Copy_u8PinNum)) ;
				break;

			default :
			/* Error : Wrong Port */
			break;
		}
	}
	else
	{
		/* Report error pin number out of boundary */
	}
}

/*******************************************************************************************************/
/*                                      06- MGPIO_u8GetPinVal                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Read Data from IDR Register                                     */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum                                        */
/* 3- Function Return      -> u8 PinValue                                                              */
/*******************************************************************************************************/

u8 MGPIO_u8GetPinValue  (u8 Copy_u8PortName , u8 Copy_u8PinNum )
{
	u8 L_u8PinValue ;
	if (Copy_u8PinNum < 16)
	{
		switch (Copy_u8PortName)
		{
			case GPIOA  :  L_u8PinValue = GET_BIT(MGPIOA->IDR , Copy_u8PinNum ) ;  break;

			case GPIOB  :  L_u8PinValue = GET_BIT(MGPIOB->IDR , Copy_u8PinNum ) ;  break;

			case GPIOC  :  L_u8PinValue = GET_BIT(MGPIOC->IDR , Copy_u8PinNum ) ;  break;

			default :
			/* Error : Wrong Port */
			break;
		}
	}
	else
	{
		/* Report error pin number out of boundary */
	}

	return L_u8PinValue;
}

/*******************************************************************************************************/
/*                                      07- MGPIO_voidSetPinValue                                        */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set Pin Value At  ODR Register                                  */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum  , Copy_u8Pinvalue                       */
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/


void MGPIO_voidSetPinValue  (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8Pinvalue )
{
	if (Copy_u8PinNum < 16)
	{
		if (Copy_u8Pinvalue == GPIO_HIGH)
		{
			switch (Copy_u8PortName)
			{
				case GPIOA  :  SET_BIT(MGPIOA->ODR , Copy_u8PinNum ) ;  break;

				case GPIOB  :  SET_BIT(MGPIOB->ODR , Copy_u8PinNum ) ;  break;

				case GPIOC  :  SET_BIT(MGPIOC->ODR , Copy_u8PinNum ) ;  break;

				default :
				/* Error : Wrong Port */
				break;
			}

		}

		else if (Copy_u8Pinvalue == GPIO_LOW)
		{
			switch (Copy_u8PortName)
			{
				case GPIOA  :  CLR_BIT(MGPIOA->ODR , Copy_u8PinNum ) ;  break;

				case GPIOB  :  CLR_BIT(MGPIOB->ODR , Copy_u8PinNum ) ;  break;

				case GPIOC  :  CLR_BIT(MGPIOC->ODR , Copy_u8PinNum ) ;  break;

				default :
				/* Error : Wrong Port */
				break;
			}

		}
	}
	else
	{
		/* Report error pin number out of boundary */
	}
}


/*******************************************************************************************************/
/*                                      08- MGPIO_voidDirectSetReset                                   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set and Reset Dirct for crossponding Pin Value At  BSRR Register*/
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum  , Copy_u8SetResetState                */
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/

void MGPI_voidDirectSetReset (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8SetResetState )
{
	if (Copy_u8PinNum < 16)
	{
		if (Copy_u8SetResetState == GPIO_HIGH)
		{
			switch (Copy_u8PortName)
			{
				case GPIOA : MGPIOA -> BSRR = (1U <<Copy_u8PinNum);  break ;

				case GPIOB : MGPIOB -> BSRR = (1U <<Copy_u8PinNum);   break ;

				case GPIOC : MGPIOC -> BSRR = (1U <<Copy_u8PinNum);  break ;

				default :
				/* Error : Wrong Port */
				break;
			}
		}

		else if (Copy_u8SetResetState == GPIO_LOW)
		{
			Copy_u8PinNum += 16;

			switch (Copy_u8PortName)
			{
				case GPIOA : MGPIOA -> BSRR = (1U <<Copy_u8PinNum) ;   break ;

				case GPIOB : MGPIOB -> BSRR = (1U <<Copy_u8PinNum) ;   break ;

				case GPIOC : MGPIOC -> BSRR = (1U <<Copy_u8PinNum);    break ;

				default :
				/* Error : Wrong Port */
				break;
			}

		}
	}
	else
	{
		/* Report error pin number out of boundary */
	}
}


/*******************************************************************************************************/
/*                                      09- MGPIO_voidTogglePin                                        */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function to toggle Pin Value 			                                   */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum 				                       */
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidTogglePin  (u8 Copy_u8PortName , u8 Copy_u8PinNum )
{
	if (Copy_u8PinNum < 16)
	{
		switch (Copy_u8PortName)
		{
			case GPIOA  :  TOG_BIT(MGPIOA->ODR , Copy_u8PinNum ) ;  break;

			case GPIOB  :  TOG_BIT(MGPIOB->ODR , Copy_u8PinNum ) ;  break;

			case GPIOC  :  TOG_BIT(MGPIOC->ODR , Copy_u8PinNum ) ;  break;

			default :
			/* Error : Wrong Port */
			break;
		}

	}
	else
	{
		/* Report error pin number out of boundary */
	}

}


/*******************************************************************************************************/
/*                                      10- MGPIO_voidSetPortValue                                       */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set Port Value At  ODR Register                                 */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName  , Copy_u16OutputValue                                         */
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/


void MGPIO_voidSetPortValue (u8 Copy_u8PortName ,u8 Copy_u8Position, u8 Copy_u8OutputValue)
{

		switch (Copy_u8PortName)
		{
			case GPIOA :
				if(Copy_u8Position== LOW_PINS)
				{
					MGPIOA -> ODR &= 0xFFFF0000 ;
					MGPIOA -> ODR |=Copy_u8OutputValue;
				}
				else if (Copy_u8Position== HIGH_PINS)
				{
					MGPIOA -> ODR &= 0x0000FFFF ;
					MGPIOA -> ODR |= (Copy_u8OutputValue<<8);
				}
				break;

			case GPIOB :
			if(Copy_u8Position== LOW_PINS)
			{
				MGPIOB -> ODR &= 0xFFFF0000 ;
				MGPIOB -> ODR |=Copy_u8OutputValue;
			}
			else if (Copy_u8Position== HIGH_PINS)
			{
				MGPIOB -> ODR &= 0x0000FFFF ;
				MGPIOB -> ODR |= (Copy_u8OutputValue<<8);
			}
			break;
			default :
			/* Error : Wrong Port */
			break;
		}

}


/*******************************************************************************************************/
/*                                      11- MGPIO_voidPinLock                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Lock At pin :                                                   */
/*                               1 - Set PIN                                                           */
/*                               2 - Set PIN 16                                                        */
/*                               3 - Clr PIN 16                                                        */
/*                               4 - Set PIN 16                                                        */
/*                               5 - wait bit 16 = High                                                */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum                                        */
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/

void MGPIO_voidPinLock (u8 Copy_u8PortName , u8 Copy_u8PinNum )
{
	switch (Copy_u8PortName)
	{
		case GPIOA :
			MGPIOA -> LCKR = (1<<16)| (1<<Copy_u8PinNum);
			MGPIOA -> LCKR = (1<<Copy_u8PinNum);
			MGPIOA -> LCKR = (1<<16)| (1<<Copy_u8PinNum);
			(void)MGPIOA -> LCKR;
			break ;

		case GPIOB :
			MGPIOB -> LCKR = (1<<16)| (1<<Copy_u8PinNum);
			MGPIOB -> LCKR = (1<<Copy_u8PinNum);
			MGPIOB -> LCKR = (1<<16)| (1<<Copy_u8PinNum);
			(void)MGPIOB -> LCKR;
			break ;

		case GPIOC :
			MGPIOC -> LCKR = (1<<16)| (1<<Copy_u8PinNum);
			MGPIOC -> LCKR = (1<<Copy_u8PinNum);
			MGPIOC -> LCKR = (1<<16)| (1<<Copy_u8PinNum);
			(void)MGPIOC -> LCKR;
			break ;
		default :
		/* Error : Wrong Port */
		break;
	}
}



/*******************************************************************************************************/
/*                                      12- MGPIO_voidSetPinAltFun                                     */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set pin Alternative :                                           */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum  , Copy_u8AltFun                       */
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/


void MGPIO_voidSetAltFun (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8AltFun )
{
	if (Copy_u8PinNum <= 7U )
	{
		switch (Copy_u8PortName)
		{
			case GPIOA : MGPIOA -> AFRL  |= (Copy_u8AltFun << 4U * (Copy_u8PinNum))  ; break ;

			case GPIOB : MGPIOB -> AFRL  |= (Copy_u8AltFun << 4U * (Copy_u8PinNum))  ; break ;

			case GPIOC : MGPIOC -> AFRL  |= (Copy_u8AltFun << 4U * (Copy_u8PinNum))  ; break ;
		}
	}

	else  if (Copy_u8PinNum <= 15U )
	{
		switch (Copy_u8PortName)
		{
			case GPIOA : MGPIOA -> AFRH  |= (Copy_u8AltFun << 4U * (Copy_u8PinNum))  ; break ;

			case GPIOB : MGPIOB -> AFRH  |= (Copy_u8AltFun << 4U * (Copy_u8PinNum))  ; break ;

			case GPIOC : MGPIOC -> AFRH  |= (Copy_u8AltFun << 4U * (Copy_u8PinNum))  ; break ;
		}
	}

	else
	{
		/* Report error pin number out of boundary */
	}
}

