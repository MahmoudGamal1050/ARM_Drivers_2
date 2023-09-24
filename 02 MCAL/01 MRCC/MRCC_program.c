/*********************************************************************
* File Name    	: 	MRCC_program.c                                 	 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	6/9/2023                                         *
* Description   : 			         				                 *                         
*********************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/MRCC/MRCC_private.h"
#include "MCAL/MRCC/MRCC_config.h"
#include "MCAL/MRCC/MRCC_interface.h"

void MRCC_voidInit(void)
{
	#if RCC_SYS_CLK == HSI
		/*  RCC_CFGR SW[1:0] = 00 to select HSI as system clock */
		CLR_BIT( MRCC->RCC_CFGR , SW0  );
		CLR_BIT( MRCC->RCC_CFGR , SW1  );
		/* Set HSION (Bit 0) IN RCC_CR Register */
		SET_BIT( MRCC->RCC_CR , HSION );

	#elif RCC_SYS_CLK == HSE

		/*  RCC_CFGR SW[1:0] = 01 to select HSE as system clock */
		SET_BIT( MRCC->RCC_CFGR , SW0  );
		CLR_BIT( MRCC->RCC_CFGR , SW1  );
		/* Set HSEON (Bit 16) IN RCC_CR Register */
		SET_BIT( MRCC->RCC_CR , HSEON );
		/* Clear HSEBYP to disable bybass */
		CLR_BIT( MRCC->RCC_CR , HSEBYP  );

	#elif RCC_SYS_CLK == HSE_BYPASS
		/*  RCC_CFGR SW[1:0] = 01 to select HSE as system clock */
		SET_BIT( MRCC->RCC_CFGR , SW0  );
		CLR_BIT( MRCC->RCC_CFGR , SW1  );
		/* Set HSEON (Bit 16) IN RCC_CR Register */
		SET_BIT( MRCC->RCC_CR , HSEON );
		/* Set HSEBYP to enable bybass */
		SET_BIT( MRCC->RCC_CR , HSEBYP  );


	#elif RCC_SYS_CLK == PLL

		/*  RCC_CFGR SW[1:0] = 10 to select PLL as system clock */
		CLR_BIT( MRCC->RCC_CFGR , SW0  );
		SET_BIT( MRCC->RCC_CFGR , SW1  );
		

		/* Clear RCC_PLLCFGR required bits before writing */
 		MRCC->RCC_PLLCFGR = (MRCC->RCC_PLLCFGR & 0xFFBC8000);

		/*		Write to the register
		 *	 	PLLM_DIV_FACTOR PLLM[5:0](Bits 5:0)
		 * 		PLLN_MUL_FACTOR PLLN[9:0](Bits 14:6)
		 * 		PLLP_DIV_FACTOR PLLP[1:0](Bits 17:16)
		 * 		PLL_SRC (Bit 22)(0 for HSI and 1 for HSE)
		 */
		MRCC->RCC_PLLCFGR |= (PLLM_DIV_FACTOR<<PLLM0) | (PLLN_MUL_FACTOR<<PLLN0)
						   | (PLLP_DIV_FACTOR<<PLLP0) | (PLL_SRC<<PLLSRC);
	

		/* Clear RCC_CFGR bits before writing */
 		MRCC->RCC_CFGR = (MRCC->RCC_CFGR & 0xFFFF030C);

		/*  RCC_CFGR SW[1:0] = 01 to select PLL as system clock */
		CLR_BIT( MRCC->RCC_CFGR , SW0  );
		SET_BIT( MRCC->RCC_CFGR , SW1  );

		/* PLL Clock Enable (bit24(PLLON) in RCC_CR)*/
		SET_BIT( MRCC->RCC_CR , PLLON );

	
	#endif
		/*   HPRE[3:0] = AHB_PRESCALAR
		 * 	PPRE1[2:0] = APB1_PRESCALAR
		 * 	PPRE2[2:0] = APB2_PRESCALAR
		 */
		MRCC->RCC_CFGR |= (AHB_PRESCALAR<<HPRE0)| (APB1_PRESCALAR<<PPRE10) | (APB2_PRESCALAR<<PPRE20);
	
}
void MRCC_voidEnablePeripheral(u8 copy_u8BusId,u8 copy_u8PerId)
{
	/*	Range Check		*/
	if(copy_u8PerId < 32)
	{
		switch(copy_u8BusId)
		{
			case	RCC_AHB1	:	SET_BIT(MRCC->RCC_AHB1ENR,copy_u8PerId);	break;
			case	RCC_AHB2	:	SET_BIT(MRCC->RCC_AHB2ENR,copy_u8PerId);	break;
			case	RCC_APB1	:	SET_BIT(MRCC->RCC_APB1ENR,copy_u8PerId);	break;
			case	RCC_APB2	:	SET_BIT(MRCC->RCC_APB2ENR,copy_u8PerId);	break;
		
		}
		
	}

	else
	{	
		/* Return Error "Out Of The Range" */
	}
	
}
void MRCC_voidDisablePeripheral(u8 copy_u8BusId,u8 copy_u8PerId)
{
	/*	Range Check		*/
	if(copy_u8PerId < 32)
	{
		switch(copy_u8BusId)
		{
			case	RCC_AHB1	:	CLR_BIT(MRCC->RCC_AHB1ENR,copy_u8PerId) ;	break;
			case	RCC_AHB2	:	CLR_BIT(MRCC->RCC_AHB2ENR,copy_u8PerId) ;	break;
			case	RCC_APB1	:	CLR_BIT(MRCC->RCC_APB1ENR,copy_u8PerId);	break;
			case	RCC_APB2	:	CLR_BIT(MRCC->RCC_APB2ENR,copy_u8PerId);	break;
		}
		
	}

	else
	{	
		/*	Return Error "Out Of The Range"	*/	
	}	
}	
