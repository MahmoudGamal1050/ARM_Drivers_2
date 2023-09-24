/*********************************************************************
* File Name    	: 	MRCC_private.h                                 	 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	9/6/2023                                         *
* Description   : 			         				                 *                         
*********************************************************************/

#ifndef MRCC_PRIVATE_H_
#define MRCC_PRIVATE_H_


#define		RCC_BASE_ADD		(0x40023800)

typedef struct
{
	u32 RCC_CR;	
	u32 RCC_PLLCFGR;	
	u32 RCC_CFGR;	
	u32 RCC_CIR;
	u32 RCC_AHB1RSTR;
	u32 RCC_AHB2RSTR;
	u32 RESERVED1;
	u32 RESERVED2;
	u32 RCC_APB1RSTR;
	u32 RCC_APB2RSTR;
	u32 RESERVED3;
	u32 RESERVED4;
	u32 RCC_AHB1ENR;	
	u32 RCC_AHB2ENR;
	u32 Reserved;
	u32 Reserved5;
	u32 RCC_APB1ENR;
	u32 RCC_APB2ENR;
	u32 RESERVED6;
	u32 RESERVED7;
	u32 RCC_AHB1LPENR;
	u32 RCC_AHB2LPENR;
	u32 RESERVED8;
	u32 RESERVED9;
	u32 RCC_APB1LPENR;
	u32 RCC_APB2LPENR;
	u32 RESERVED10;
	u32 RESERVED11;
	u32 RCC_BDCR;
	u32 RCC_CSR;
	u32 RESERVED12;
	u32 RESERVED13;
	u32 RCC_SSCGR;
	u32 RCC_PLLI2SCFGR;
	u32 RESERVED14;
	u32 RCC_DCKCFGR;
}RCC_t;

#define MRCC ((volatile RCC_t *)RCC_BASE_ADD)

/* RCC_CR Pins Definitions */
#define	HSION	0
#define	HSIRDY	1
#define	HSEON	16
#define	HSERDY	17
#define	HSEBYP	18
#define	CSSON	19
#define	PLLON	24
#define	PLLRDY	25

/* RCC_PLLCFGR Pins Definitions */
#define PLLM0	0
#define PLLN0	6
#define PLLP0	16
#define PLLSRC	22
/* RCC_CFGR Pins Definitions */
#define SW0		0
#define SW1		1
#define SWS0	2
#define SWS1	3
#define HPRE0	4
#define PPRE10	10
#define PPRE20	13





/*  RCC SYSTEM CLOCK Definitions	*/						     		                                                              
#define HSI                         0
#define HSE							1
#define HSE_BYPASS                  2
#define PLL                         3
#define PLL_HSI        				0
#define PLL_HSE                     1


/*  PLLP_DIV_FACTOR Definitions	*/
#define PLLP_DIV_BY_2               0
#define PLLP_DIV_BY_4				1
#define PLLP_DIV_BY_6               2
#define PLLP_DIV_BY_8               3


/*	AHB_PRESCALAR Definitions */
#define	SYS_CLK					0b0000
#define	SYS_CLK_DIV_BY_2		0b1000
#define	SYS_CLK_DIV_BY_4		0b1001
#define	SYS_CLK_DIV_BY_8		0b1010
#define	SYS_CLK_DIV_BY_16       0b1011
#define	SYS_CLK_DIV_BY_64       0b1100
#define	SYS_CLK_DIV_BY_128      0b1101
#define	SYS_CLK_DIV_BY_256      0b1110
#define	SYS_CLK_DIV_BY_512      0b1111

/*	APB1_PRESCALAR and APB2_PRESCALAR  Definitions */
#define	AHB_CLK       		0b000
#define	AHB_DIV_BY_2  		0b100
#define	AHB_DIV_BY_4  		0b101
#define	AHB_DIV_BY_8  		0b110
#define	AHB_DIV_BY_16       0b111





#endif

