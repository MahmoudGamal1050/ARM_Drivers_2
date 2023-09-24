/*********************************************************************
* File Name    	: 	MRCC_config.h                                 	 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	9/6/2023                                         *
* Description   : 			         				                 *                         
*********************************************************************/

#ifndef MRCC_CONFIG_H_
#define MRCC_CONFIG_H_

/******************************************************************
*                                                                 
*  RCC_SYS_CLK Options :							     		 
*			1- HSI					             						
*			2- HSE
*			3- HSE_BYPASS					       
*			4- PLL 
*			    4.1- PLL_SRC (PLL Source) :
*						PLL_HSI       	 
*               		PLL_HSE  
*			    4.2- PLLM_DIV_FACTOR (Division factor for main PLL) 
*						PLLM Options :  2 to 63  
*		                VCO input frequency = PLL input frequency / PLLM 	                   	 
*			    4.3- PLLN_MUL_FACTOR (Main PLL multiplication factor for VCO) 
*						PLLN Options :  192 to 432  
*		                VCO output frequency = VCO input frequency * PLLN 	                   	 
*		             
*			    4.4- PLLP_DIV_FACTOR (Main PLL division factor for system clock) 
*						PLLP options :
*							PLLP_DIV_BY_2
*							PLLP_DIV_BY_4
*							PLLP_DIV_BY_6
*							PLLP_DIV_BY_8
*		                PLL output frequency = VCO output frequency / PLLP 	                   	 
*
*******************************************************************/
#define	RCC_SYS_CLK		HSI

#if RCC_SYS_CLK == PLL
#define PLL_SRC		    PLL_HSI
#define PLLM_DIV_FACTOR    16       /* PLLM_DIV_FACTOR  (2:63) */
#define PLLN_MUL_FACTOR    4       /* PLLN_MUL_FACTOR  (192:432) */
#define PLLP_DIV_FACTOR    PLLP_DIV_BY_8       /* PLLP_DIV_FACTOR  (2,4,6,8) */
#endif

/******************************************************************
*	AHB Prescalar Options :
*				SYS_CLK
*				SYS_CLK_DIV_BY_2
*				SYS_CLK_DIV_BY_4
*				SYS_CLK_DIV_BY_8
*				SYS_CLK_DIV_BY_16
*				SYS_CLK_DIV_BY_64
*				SYS_CLK_DIV_BY_128
*				SYS_CLK_DIV_BY_256
*				SYS_CLK_DIV_BY_512
*******************************************************************/
#define AHB_PRESCALAR	SYS_CLK_DIV_BY_2


/******************************************************************
*	APB1 Prescalar Options :
*				AHB_CLK
*				AHB_DIV_BY_2
*				AHB_DIV_BY_4
*				AHB_DIV_BY_8
*				AHB_DIV_BY_16
*	APB1 frequency shouldn't exceed 42MHz
*******************************************************************/
#define APB1_PRESCALAR	AHB_CLK

/******************************************************************
*	APB2 Prescalar Options :
*				AHB_CLK
*				AHB_DIV_BY_2
*				AHB_DIV_BY_4
*				AHB_DIV_BY_8
*				AHB_DIV_BY_16
*	APB2 frequency shouldn't exceed 84MHz
*******************************************************************/
#define APB2_PRESCALAR	AHB_CLK

#endif
