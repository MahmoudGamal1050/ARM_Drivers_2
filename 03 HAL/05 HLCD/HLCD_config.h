/*********************************************************************
* File Name    	: 	HLCD_config.h                                    *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	15/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/

#ifndef HAL_HLCD_HLCD_CONFIG_H_
#define HAL_HLCD_HLCD_CONFIG_H_
/* Choose LCD mode :
 * 		_8_BIT_MODE
 * 		_4_BIT_MODE
 */
#define LCD_MODE _8_BIT_MODE
/* Choose LCD data and control port : (GPIOA, GPIOB) */
#define LCD_DATA_PORT		GPIOA
#define LCD_CONTROL_PORT	GPIOA


/* Choose LCD data pins for 8_bit_mode : (GPIO_PIN0 : GPIO_PIN15)
 * LCD_PINS_POSITION Options : (LOW_PINS,HIGH_PINS)
 */
#if LCD_MODE == _8_BIT_MODE
#define LCD_PINS_POSITION	LOW_PINS
#define LCD_D0              GPIO_PIN0
#define LCD_D1              GPIO_PIN1
#define LCD_D2              GPIO_PIN2
#define LCD_D3              GPIO_PIN3
#define LCD_D4              GPIO_PIN4
#define LCD_D5              GPIO_PIN5
#define LCD_D6              GPIO_PIN6
#define LCD_D7              GPIO_PIN7

/* Choose LCD data pins for 4_bit_mode : (GPIO_PIN0 : GPIO_PIN15) */
#elif LCD_MODE ==  _4_BIT_MODE
#define LCD_D4              GPIO_PIN4
#define LCD_D5              GPIO_PIN5
#define LCD_D6              GPIO_PIN6
#define LCD_D7              GPIO_PIN7

#endif

/* Choose LCD control pins : (GPIO_PIN0 : GPIO_PIN15) */

#define LCD_RS		 		GPIO_PIN8
#define LCD_RW				GPIO_PIN9
#define LCD_EN				GPIO_PIN10


#endif /* HAL_HLCD_HLCD_CONFIG_H_ */
