/*********************************************************************
* File Name    	: 	MSUART_private.h                                	 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	19/9/2023                                        *
* Description   : 			         				                 *
**********************************************************************/
#ifndef MSUART_PRIVATE_H_
#define MSUART_PRIVATE_H_

#define	 USART1_BASE_ADDRESS			(0x40011000)
#define	 USART2_BASE_ADDRESS			(0x40004400)
#define	 USART3_BASE_ADDRESS			(0x40011400)



typedef struct
{

	u32	SR;
	u32	DR;
	u32	BRR;
	u32	CR1;
	u32	CR2;
	u32	CR3;
	u32	GTPR;

}USART_t;


#define MUSART1 	((volatile USART_t *)USART1_BASE_ADDRESS)
#define MUSART2 	((volatile USART_t *)USART2_BASE_ADDRESS)
#define MUSART3 	((volatile USART_t *)USART3_BASE_ADDRESS)


/* Registers Bits  */

/*  USART_SR Registers bits definitions  */
#define RXNE	5
#define TC		6
#define TXE		7

/*  USART_BRR Registers bits definitions  */
#define	DIV_FRACTION0    0
#define	DIV_FRACTION1    1
#define	DIV_FRACTION2    2
#define	DIV_FRACTION3    3
#define	DIV_MANTISSA0    4
#define	DIV_MANTISSA1    5
#define	DIV_MANTISSA2    6
#define	DIV_MANTISSA3    7
#define	DIV_MANTISSA4    8
#define	DIV_MANTISSA5    9
#define	DIV_MANTISSA6    10
#define	DIV_MANTISSA7    11
#define	DIV_MANTISSA8    12
#define	DIV_MANTISSA9    13
#define	DIV_MANTISSA10   14
#define	DIV_MANTISSA11   15

/* USART_CR1 Registers bits definitions  */
#define PS			9
#define PCE			10
#define M			12
#define OVER8		15

/* USART_CR2 Registers bits definitions  */
#define STOP0		12
#define STOP1		13

#endif 
