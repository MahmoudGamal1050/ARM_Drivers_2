/********************************************************************************/
/* File Name    	: 	HBUTTON_interface.h   		                            */
/* Author       	: 	Mahmoud Gamal                                           */
/* Version      	: 	1.0.0                                                   */
/* Date 		 	: 	09/12/2023                                              */
/********************************************************************************/
#ifndef HBUTTON_INTERFACE_H
#define HBUTTON_INTERFACE_H


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
/********************** Internal Pull State Macros **************************/
/****************************************************************************/
#define INTERNAL_PULL_UP       (0b01)
#define INTERNAL_PULL_DOWN     (0b10)

/*********************************************************************************
****************************** Functions Prototypes ******************************
*********************************************************************************/

/* Function to initialize the button */
void HBUTTON_voidInit(u8 Copy_u8PortName, u8 Copy_u8PinNum);
/* Function to enable internal pull up or down resistor */
void HBUTTON_voidEnableInternalPullUpDown(u8 Copy_u8PortName, u8 Copy_u8PinNum, u8 Copy_u8PullState);
/* Function to read button value */
u8 HBUTTON_u8GetValue(u8 Copy_u8PortName, u8 Copy_u8PinNum);


#endif 
