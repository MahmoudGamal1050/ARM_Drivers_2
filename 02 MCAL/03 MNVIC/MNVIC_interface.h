/*********************************************************************
* File Name    	: 	MNVIC_interface.h                                *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	10/9/2023                                        *
* Description   : 			         				                 *                         
*********************************************************************/

#ifndef	MNVIC_INTERFACE_H
#define	MNVIC_INTERFACE_H

/* Enum for all interrupt positions */
typedef enum
{
	NVIC_WWDG,
	NVIC_EXTI16,
	NVIC_EXTI21,
	NVIC_EXTI22,
	NVIC_FLASH,
	NVIC_RCC,
	NVIC_EXTI0,
	NVIC_EXTI1,
	NVIC_EXTI2,
	NVIC_EXTI3,
	NVIC_EXTI4,
	NVIC_DMA1_Stream0,
	NVIC_DMA1_Stream1,
	NVIC_DMA1_Stream2,
	NVIC_DMA1_Stream3,
	NVIC_DMA1_Stream4,
	NVIC_DMA1_Stream5,
	NVIC_DMA1_Stream6,
	NVIC_ADC,
	NVIC_EXTI9_5=23,
	NVIC_TIM1_BRK_TIM9,
	NVIC_IM1_UP_TIM10,
	NVIC_TIM1_TRG_COM_TIM11,
	NVIC_TIM1_CC,
	NVIC_TIM2,
	NVIC_TIM3,
	NVIC_TIM4,
	NVIC_I2C1_EV,
	NVIC_I2C1_ER,
	NVIC_I2C2_EV,
	NVIC_I2C2_ER,
	NVIC_SPI1,
	NVIC_SPI2,
	NVIC_USART1,
	NVIC_USART2,
	NVIC_EXTI15_10=40,
	NVIC_EXTI17,
	NVIC_EXTI18,
	NVIC_DMA1_Stream7=47,
	NVIC_SDIO=49,
	NVIC_TIM5,
	NVIC_SPI3,
	NVIC_DMA2_Stream0=56,
	NVIC_DMA2_Stream1,
	NVIC_DMA2_Stream2,
	NVIC_DMA2_Stream3,
	NVIC_DMA2_Stream4,
	NVIC_OTG_FS=67,
	NVIC_DMA2_Stream5,
	NVIC_DMA2_Stream6,
	NVIC_DMA2_Stream7,
	NVIC_USART6,
	NVIC_I2C3_EV,
	NVIC_I2C3_ER,
	NVIC_FPU=81,
	NVIC_SPI4=84

}IntPos_t;

/* Enum for priority grouping mode */
typedef enum
{
	GRB_16_SUB_00 = 3,   /*  4 bits for groups and no bits for subgroups*/
	GRB_08_SUB_02 ,   	 /*  3 bits for groups and 1 bit for subgroups  */
	GRB_04_SUB_04 ,   	 /*  2 bits for groups and 2 bits for subgroups */
	GRB_02_SUB_08 ,    	 /*  1 bit for groups and 3 bits for subgroups  */
	GRB_00_SUB_16 ,    	 /*  No bits for groups and 4 bits for subgroups*/

}GroupMode_t;


/* Function to set priority grouping mode */
void MNVIC_voidSetGroupingMode(GroupMode_t Copy_uddtGroupMode);
/* Function to enable peripheral interrupt */
void MNVIC_voidEnablePerInt ( IntPos_t Copy_uddtIntPos );
/* Function to disable peripheral interrupt */
void MNVIC_voidDisablePerInt( IntPos_t Copy_uddtIntPos  );
/* Function to set pending flag by software without hardware event */
void MNVIC_voidSetPendingFlag        ( IntPos_t Copy_uddtIntPos  );
/* Function to clear interrupt pending flag */
void MNVIC_voidClearPendingFlag      ( IntPos_t Copy_uddtIntPos  );
/* Function to read active flag for certain interrupt */
u8   MNVIC_u8GetActiveFlag       ( IntPos_t Copy_uddtIntPos  );
/* Function to set group and subgroup priorities */
void MNVIC_voidSetIntPriority(IntPos_t Copy_uddtIntPos  ,GroupMode_t Copy_uddtGroupMode, u8 Copy_u8GroupPriority , u8 Copy_u8SubPriority);








#endif
