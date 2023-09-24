/*********************************************************************
* File Name    	: 	MGPIO_private.h                                  *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	7/9/2023                                         *
* Description   : 			         				                 *                         
*********************************************************************/



/****************************************************************************/
/********************** File Guard ******************************************/
/****************************************************************************/
#ifndef _GPIO_PRIVATE_H
#define _GPIO_PRIVATE_H


/****************************************************************************/
/********************** GPIOx Base Addresses ********************************/
/****************************************************************************/
#define GPIOA_BASE_ADDRESS					0x40020000

#define GPIOB_BASE_ADDRESS					0x40020400

#define GPIOC_BASE_ADDRESS					0x40020800

#define GPIOD_BASE_ADDRESS					0x40020C00

#define GPIOE_BASE_ADDRESS					0x40021000

#define GPIOH_BASE_ADDRESS					0x40021C00

 
/****************************************************************************/
/********************** Registers Definitions  ******************************/
/****************************************************************************/
typedef struct 
{
	u32 MODER;   /* GPIO port mode register, Address offset : 0x00 					  */	
	u32 OTYPER;  /* GPIO port Output type register, Address offset : 0x04 			  */
	u32 OSPEEDR; /* GPIO port Output Speed  register, Address offset : 0x08 		  */
	u32 PUPDR;   /* GPIO port Pull UP / Pull Down  register, Address offset : 0x0c    */
	u32 IDR;     /* GPIO port Input Data register, Address offset : 0x10              */
	u32 ODR;     /* GPIO port Output Data register, Address offset : 0x14             */
	u32 BSRR;    /* GPIO port Bit Set / Reset register, Address offset : 0x18         */
	u32 LCKR;    /* GPIO port Lock Pin register, Address offset : 0x1c                */
	u32 AFRL;    /* GPIO port Alternate Function Low register, Address offset : 0x10  */
	u32 AFRH;	 /* GPIO port Alternate Function High register, Address offset : 0x24 */
}GPIOx_r;


/****************************************************************************/
/********************** Struct Base Address for GPIOA  **********************/
/****************************************************************************/

#define         MGPIOA          ((volatile GPIOx_r*)GPIOA_BASE_ADDRESS)


/****************************************************************************/
/********************** Struct Base Address for GPIOB  **********************/
/****************************************************************************/

#define         MGPIOB          ((volatile GPIOx_r*)GPIOB_BASE_ADDRESS)


/****************************************************************************/
/********************** Struct Base Address for GPIOC  **********************/
/****************************************************************************/

#define         MGPIOC          ((volatile GPIOx_r*)GPIOC_BASE_ADDRESS)

  
#endif 
