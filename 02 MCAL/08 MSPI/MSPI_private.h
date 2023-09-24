/*********************************************************************
* File Name    	: 	MSPI_private.h                                   *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	20/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/
#ifndef MSPI_PRIVATE_H
#define MSPI_PRIVATE_H

#define SPI1_BASE_ADDRESS	(0x40013000)
#define SPI2_BASE_ADDRESS	(0x40003800)
#define SPI3_BASE_ADDRESS	(0x40003C00)

typedef struct
{
	volatile u32 CR1    ;
	volatile u32 CR2    ;
	volatile u32 SR     ;
	volatile u32 DR     ;
	volatile u32 CRCPR  ;
	volatile u32 RXCRCR ;
	volatile u32 TXCRCR ;
	volatile u32 I2SCFGR;
	volatile u32 I2SPR  ; 
	
}SPI_t;


#define MSPI1   ((SPI_t*)SPI1_BASE_ADDRESS)
#define MSPI2   ((SPI_t*)SPI2_BASE_ADDRESS)
#define MSPI3   ((SPI_t*)SPI3_BASE_ADDRESS)


/*  SPI_CR1 Register bits definitions  */
#define CPHA		0
#define CPOL		1
#define MSTR		2
#define BR0			3
#define SPE			6
#define LSBFIRST	7
#define SSI			8
#define SSM			9
#define DFF			11

/*  SPI_SR Register bits definitions  */
#define RXNE	0
#define TXE		1
#define BSY		7


#endif
