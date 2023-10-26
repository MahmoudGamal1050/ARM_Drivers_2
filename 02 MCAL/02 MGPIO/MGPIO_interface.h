/*********************************************************************
* File Name    	: 	MGPIO_interface.h                                *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	7/9/2023                                         *
* Description   : 			         				                 *                         
*********************************************************************/


/****************************************************************************/
/********************** File Guard ******************************************/
/****************************************************************************/

#ifndef _GPIO_INTERFACE_H
#define _GPIO_INTERFACE_H


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
/********************** Port Position Macros ********************************/
/****************************************************************************/

#define LOW_PINS      0U
#define HIGH_PINS     1U


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
/********************** Mode Macros *****************************************/
/****************************************************************************/
#define   GPIO_INPUT     (0b00)
#define   GPIO_OUTPUT    (0b01)
#define   GPIO_ALTF      (0b10)
#define   GPIO_ANALOG    (0b11)


/****************************************************************************/
/********************** Output Types Macros *********************************/
/****************************************************************************/
#define  GPIO_OUTPUT_PUSH_PULL     (0U)
#define  GPIO_OUTPUT_OPEN_DRAIN    (1U)


/****************************************************************************/
/********************** Output Speed Macros *********************************/
/****************************************************************************/
#define GPIO_OUTPUT_SPEED_LOW             (0b00)
#define GPIO_OUTPUT_SPEED_MEDIUM          (0b01)
#define GPIO_OUTPUT_SPEED_HIGH            (0b10)
#define GPIO_OUTPUT_SPEED_VERY_HIGH       (0b11)


/****************************************************************************/
/********************** Input State Macros **********************************/
/****************************************************************************/
#define GPIO_INPUT_FLOATING      (0b00)
#define GPIO_INPUT_PULL_UP       (0b01)
#define GPIO_INPUT_PULL_DOWN     (0b10)

/***************************************************************************/
/********************** Write Date Macros **********************************/
/***************************************************************************/
#define GPIO_HIGH                  (1U)
#define GPIO_LOW                   (0U)

/***************************************************************************/
/********************** Alternate Function Macros **************************/
/***************************************************************************/
 #define GPIO_ALTFN_0                          (0b0000)
 #define GPIO_ALTFN_1                          (0b0001)
 #define GPIO_ALTFN_2                          (0b0010)
 #define GPIO_ALTFN_3                          (0b0011)
 #define GPIO_ALTFN_4                          (0b0100)
 #define GPIO_ALTFN_5                          (0b0101)
 #define GPIO_ALTFN_6                          (0b0110)
 #define GPIO_ALTFN_7                          (0b0111)
 #define GPIO_ALTFN_8                          (0b1000)
 #define GPIO_ALTFN_9                          (0b1001)
 #define GPIO_ALTFN_10                         (0b1010)
 #define GPIO_ALTFN_11                         (0b1011)
 #define GPIO_ALTFN_12                         (0b1100)
 #define GPIO_ALTFN_13                         (0b1101)
 #define GPIO_ALTFN_14                         (0b1110)
 #define GPIO_ALTFN_15                         (0b1111)




/***************************************************************************/
/********************** Functions Prototypes *******************************/
/***************************************************************************/


/*********************************************************************************************************/
/*										 01 - MGPIO_voidSetPinMode  									 */
/*-------------------------------------------------------------------------------------------------------*/
/*	1-  Function Description ->  function Set the mode of the Pin                                        */
/*	2-  Options : (A) GPIO_INPUT                                                                    	 */
/*				  (B) GPIO_OUTPUT                                                                  	     */
/*				  (C) GPIO_ALTF                                                                          */
/*				  (D) GPIO_ANALOG                                                            	         */
/*				                                                                                         */
/*	3- Function Arguments : (A)  Copy_u8PortName  : The port Number (ex : GPIOA , GPIOB)     			 */
/*							(B)	 Copy_u8PinNum    : The Pin Number (ex : GPIO_PIN0 , GPIO_PIN1)          */
/*							(C)  Copy_u8Mode      : The Mode (ex : GPIO_INPUT)          	             */
/*	                                                                                                     */
/*	4- Function Return   ->  void																	     */
/*********************************************************************************************************/	
void MGPIO_voidSetPinMode (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8Mode);



/*********************************************************************************************************/
/*										 02 - MGPIO_voidSetPortMode  									 */
/*-------------------------------------------------------------------------------------------------------*/
/**                                                                                                      */
/*	1-  function Description ->  function Set the mode of the Port                                       */
/*	2-  Options : 																						 */
/*  			  (A) GPIO_INPUT                                                        	             */
/*				  (B) GPIO_OUTPUT       	                                                             */
/*				  (C) GPIO_ALTF             	                                                         */
/*				  (D) GPIO_ANALOG               	                                                     */
/*				                                                                                         */
/*	3- Function Arguments : (A)  Copy_u8PortName  : The port Number (ex : GPIOA , GPIOB)  			     */
/*							(B)  Copy_u8Mode      : The Mode (ex : GPIO_INPUT)  	     		         */
/*	                                                                                                     */
/*	4- Function Return   ->  void                                                                        */
/*	                                                                                                     */
/*********************************************************************************************************/
void MGPIO_voidSetPortMode (u8 Copy_u8PortName ,u8 Copy_u8Position, u8 Copy_u8Mode);


/*******************************************************************************************************/
/*                                      03- MGPIO_voidSetOutputMode                                    */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set The output mode Of GPIO Pin.                                */
/*                                                                                                     */
/* 2- Output Modes Options :                                                                           */
/*		1- GPIO_OUTPUT_PUSH_PULL  (Default mode when pin is configured as output)                                                                     */
/*      2- GPIO_OUTPUT_OPEN_DRAIN                                                                      */
/*                                                                                                     */
/* 3- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8OutputMode                  */                   
/* 4- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidSetOutputMode (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8OutputMode );



/*******************************************************************************************************/
/*                                      04- MGPIO_voidSetOutputSpeed                                   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set The output speed  Of GPIO Pin 		                       */
/*                                                                                                     */
/*      1- GPIO_OUTPUT_SPEED_LOW       	  8 MHZ                                                        */
/*      2- GPIO_OUTPUT_SPEED_MEDIUM    	  50 MHZ                                                       */
/*      3- GPIO_OUTPUT_SPEED_HIGH      	  80 MHZ                                                       */
/*      4- GPIO_OUTPUT_SPEED_VERY_HIGH 	  180 MHZ                                                      */
/*																								       */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8OutputSpeed                 */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidSetOutputSpeed  (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8OutputSpeed );



/*******************************************************************************************************/
/*                                      05- MGPIO_voidSetInputState                                    */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set The Resistor connection state of GPIO pin 	               */
/*      1- GPIO_INPUT_FLOATING                                                                         */
/*      2- GPIO_INPUT_PULL_UP                                                                          */
/*      3- GPIO_INPUT_PULL_DOWN                                                                        */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8InputState                  */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidSetInputState  (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8InputState );



/*******************************************************************************************************/
/*                                      06- MGPIO_u8GetPinValue                                        */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Read Data from IDR Register                                     */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum                                        */                   
/* 3- Function Return      -> u8 PinValue                                                              */
/*******************************************************************************************************/
u8 MGPIO_u8GetPinValue  (u8 Copy_u8PortName , u8 Copy_u8PinNum );




/*******************************************************************************************************/
/*                                      07- MGPIO_voidSetPinValue                                      */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set Pin Value At  ODR Register                                  */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum  , Copy_u8Pinvalue                     */
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidSetPinValue  (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8Pinvalue );



/*******************************************************************************************************/
/*                                      08- MGPIO_voidDirectSetReset                                   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set and Reset Dirct for crossponding Pin Value At  BSRR Register*/
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum  , Copy_u8SetResetState                */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPI_voidDirectSetReset (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8SetResetState );



/*******************************************************************************************************/
/*                                      09- MGPIO_voidTogglePin                                        */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function to toggle Pin Value 			                                   */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum 				                       */
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidTogglePin  (u8 Copy_u8PortName , u8 Copy_u8PinNum );

/*******************************************************************************************************/
/*                                      10- MGPIO_voidSetPortValue                                       */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set Port Value At  ODR Register                                 */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName  , Copy_u8OutputValue                                         */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidSetPortValue (u8 Copy_u8PortName ,u8 Copy_u8Position, u8 Copy_u8OutputValue);


/*******************************************************************************************************/
/*                                      11- MGPIO_voidPinLock                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Lock At pin :                                                   */
/*                               1 - Set PIN                                                           */
/*                               2 - Set PIN 16                                                        */
/*                               3 - Clr PIN 16                                                        */
/*                               4 - Set PIN 16                                                        */
/*                               5 - wait bit 16 = High                                                */ 
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum                                        */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidPinLock (u8 Copy_u8PortName , u8 Copy_u8PinNum );




/*******************************************************************************************************/
/*                                      12- MGPIO_voidSetPinAltFun                                     */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set pin Alternative :                                           */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum  , Copy_u8AltFun                       */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/

void MGPIO_voidSetAltFun (u8 Copy_u8PortName , u8 Copy_u8PinNum , u8 Copy_u8AltFun );






#endif 
