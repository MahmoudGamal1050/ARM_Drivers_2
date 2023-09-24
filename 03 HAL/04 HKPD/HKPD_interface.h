/*********************************************************************
* File Name    	: 	HKPD_interface.h                                 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	13/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/

#ifndef HKPD_INTERFACE_H_
#define HKPD_INTERFACE_H_

/* Function to initialize the keypad */
void HKPD_voidInit(void);
/* Function to get pressed key
 * Return : Ascii of pressed key and 0 if now key is pressed */
u8 HKPD_u8GetPressedKey(void);

#endif 
