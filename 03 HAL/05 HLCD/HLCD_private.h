/*********************************************************************
* File Name    	: 	HLCD_private.h                                   *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	15/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/

#ifndef HAL_HLCD_HLCD_PRIVATE_H_
#define HAL_HLCD_HLCD_PRIVATE_H_

/* LCD Commands */
#define  LCD_SET_ROW0      		  0x80
#define  LCD_SET_ROW1       	  0xC0

#define  DDRAM_TO_CGRAM           0x40
#define  CGRAM_TO_DDRAM           0x80

#define  DISPLAY_CLEAR            0x01
#define  ENTRY_MODE               0x06
#define  FUNCTION_SET_8BIT		  0x38
#define  FUNCTION_SET_4BIT		  0x28
#define  RETURN_HOME 			  0x02
#define  DISPLAY_ON_CURSOR_OFF    0x0C
#define  DISPLAY_ON_CURSOR_ON     0x0E

/* LCD Modes */
#define _8_BIT_MODE			1
#define _4_BIT_MODE			2

/* Private function to send commands to LCD */
static void HLCD_voidSendCommand(u8 copy_u8Command);


#endif /* HAL_HLCD_HLCD_PRIVATE_H_ */
