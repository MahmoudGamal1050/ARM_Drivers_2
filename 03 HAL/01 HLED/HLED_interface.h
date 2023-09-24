/********************************************************************************/
/* File Name    	: 	HLED_interface.h   		                                */
/* Author       	: 	Mahmoud Gamal                                           */
/* Version      	: 	1.0.0                                                   */
/* Date 		 	: 	12/9/2023                                              */
/********************************************************************************/
#ifndef HLED_INTERFACE_H
#define HLED_INTERFACE_H


/****************************************************************************/
/********************** Port Macros *****************************************/
/****************************************************************************/

#define GPIOA      0U
#define GPIOB      1U
#define GPIOC      2U
#define GPIOD      3U
#define GPIOE      4U
#define GPIOH      5U

/****************************************************************************/
/********************** Pin Macros ******************************************/
/****************************************************************************/
#define GPIO_PIN0         0U
#define GPIO_PIN1         1U
#define GPIO_PIN2         2U
#define GPIO_PIN3         3U
#define GPIO_PIN4         4U
#define GPIO_PIN5         5U
#define GPIO_PIN6         6U
#define GPIO_PIN7         7U
#define GPIO_PIN8         8U
#define GPIO_PIN9         9U
#define GPIO_PIN10        10U
#define GPIO_PIN11        11U
#define GPIO_PIN12        12U
#define GPIO_PIN13        13U
#define GPIO_PIN14        14U
#define GPIO_PIN15        15U

/****************************************************************************/
/********************** LED States Macros ***********************************/
/****************************************************************************/
#define LED_OFF		0
#define LED_ON		1
#define LED_TOG		2

/*********************************************************************************
****************************** Functions Prototypes ******************************
*********************************************************************************/

void HLED_voidInit(u8 Copy_u8PortName, u8 Copy_u8PinNum);

void HLED_voidWrite(u8 Copy_u8PortName,u8 Copy_u8PinNum, u8 Copy_u8State);



#endif 
