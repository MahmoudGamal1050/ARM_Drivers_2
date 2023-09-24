/*********************************************************************
* File Name    	: 	HLCD_interface.h                                 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	15/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/

#ifndef HAL_HLCD_HLCD_INTERFACE_H_
#define HAL_HLCD_HLCD_INTERFACE_H_

/* Function to initialize LCD */
void HLCD_voidInit(void);
/* Function to send character to LCD */
void HLCD_voidWriteData(u8 copy_u8Data);
/* Function to clear LCD */
void HLCD_voidClearScreen(void);
/* Function to move cursor to a certain position */
void HLCD_voidSetPosition(u8 Copy_u8Row, u8 Copy_u8Col);
/* Function to write string to LCD */
void HLCD_voidWriteString(char *Copy_u8PtrData);
/* Function to write number to LCD */
void HLCD_voidWriteNumber(u16 Copy_u16Number);
/* Function to write float number to LCD */
void HLCD_voidWriteFloatNumber(f32 Copy_f16Number);

/* Function to store custom characters in CGRAM */
void HLCD_voidSaveCustomChar(u8 Copy_u8arr[], u8 copy_u8Location);


#endif /* HAL_HLCD_HLCD_INTERFACE_H_ */
