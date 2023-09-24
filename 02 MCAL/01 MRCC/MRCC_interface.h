/*********************************************************************
* File Name    	: 	MRCC_interface.h                                 	 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	9/6/2023                                         *
* Description   : 			         				                 *                         
*********************************************************************/

#ifndef MRCC_INTERFACE_H_
#define MRCC_INTERFACE_H_


/******************************                                                          
 *  Bus IDS							     		                                                              
 ******************************/
#define	RCC_AHB1		0
#define	RCC_AHB2		1
#define	RCC_APB1		2
#define	RCC_APB2		3

/********************************************
 * Peripheral Clock Enable For AHB1 Bus     
 ********************************************/
#define    RCC_GPIOA         0U
#define    RCC_GPIOB         1U
#define    RCC_GPIOC         2U
#define    RCC_GPIOD         3U
#define    RCC_GPIOE       	 4U
#define    RCC_GPIOH       	 5U
#define    RCC_CRC          12U
#define    RCC_DMA1         21U
#define    RCC_DMA2         22U
 
/********************************************
 * Peripheral Clock Enable For APB1 Bus  
 ********************************************/
#define    RCC_TIM2         0
#define    RCC_TIM3         1
#define    RCC_TIM4         2
#define    RCC_TIM5         3
#define    RCC_WWDG        11
#define    RCC_SPI2        14
#define    RCC_SPI3        15
#define    RCC_USART2      17
#define    RCC_I2C1        21
#define    RCC_I2C2        22
#define    RCC_I2C3        23
#define    RCC_PWR         28


/********************************************
 * Peripheral Clock Enable For APB2 Bus  
 ********************************************/
#define    RCC_TIM1        	1
#define    RCC_USART1       4
#define    RCC_USART6      	5
#define    RCC_ADC1        	8
#define    RCC_SDIO        11
#define    RCC_SPI1        12
#define    RCC_SPI4        13
#define    RCC_SYSCFG      14
#define    RCC_TIM9        16
#define    RCC_TIM10       17
#define    RCC_TIM11       18



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
 
/* Function to initialize RCC */
void MRCC_voidInit(void);
/* Function to enable peripheral clock */
void MRCC_voidEnablePeripheral(u8 copy_u8BusId,u8 copy_u8PerId);
/* Function to disable peripheral clock */
void MRCC_voidDisablePeripheral(u8 copy_u8BusId,u8 copy_u8PerId);


#endif
