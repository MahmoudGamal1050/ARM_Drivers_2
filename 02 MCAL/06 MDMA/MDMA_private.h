/*********************************************************************
* File Name    	: 	MDMA_private.h                                 	 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	17/9/2023                                        *
* Description   : 			         				                 *
**********************************************************************/
#ifndef DMA_PRIVATE_H
#define DMA_PRIVATE_H


#define FLAG_CLEAR_MASK		0b111101U
#define DMA1_BASE_ADDRESS	(0x40026000)
#define DMA2_BASE_ADDRESS	(0x40026400)

typedef struct
{
														  
	u32	CR;    /* Configuration register     */
    u32	NDTR;  /* Number of Data Register    */
    u32	PAR;   /* Peripheral Address Register*/
    u32	M0AR;  /* Memory 0 Address Register  */
    u32	M1AR;  /* Memory 1 Address Register  */
    u32	FCR;   /* FIFO Control Register      */

}DMA_Channel;

typedef struct
{												   
	u32 LISR;    /* DMA Low ISR register                   */
    u32 HISR;    /* DMA High ISR register                  */
    u32 LIFCR;   /* DMA Low Interrupt Flag Clear register  */
    u32 HIFCR;   /* DMA High Interrupt Flag Clear register */
	DMA_Channel Stream[8];

}DMA_t;

#define 	DMA1 	( ( volatile DMA_t * )DMA1_BASE_ADDRESS )
#define 	DMA2 	( ( volatile DMA_t * )DMA2_BASE_ADDRESS )

/* DMA_SxCR Pins Definitions */
#define EN		0
#define DMEIE	1
#define TEIE	2
#define HTIE	3
#define TCIE	4
#define DIR0	6
#define CIRC	8
#define PINC	9
#define MINC	10
#define PSIZE0	11
#define MSIZE0	13
#define PL0		16
#define CHSEL0	25

/* DMA_LIFCR Pins Definitions */
#define	CFEIF0 0
#define	CFEIF1 6
#define	CFEIF2 16
#define	CFEIF3 22

/* DMA_HIFCR Pins Definitions */
#define	CFEIF4 0
#define	CFEIF5 6
#define	CFEIF6 16
#define	CFEIF7 22




#endif /* DMA_private_H_ */
