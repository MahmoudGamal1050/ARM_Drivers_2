/*********************************************************************
* File Name    	: 	HKPD_config.h                                    *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	13/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/

#ifndef HKPD_CONFIG_H_
#define HKPD_CONFIG_H_

/* Keypad number of rows and columns */
#define KPD_ROWS 	4
#define KPD_COLS	4

/* Keypad Port (GPIOA, GPIOB) */
#define KPD_PORT	GPIOB
/* Keypad rows pins (GPIO_PIN0:GPIO_PIN15) */
#define KPD_ROW1_PIN	GPIO_PIN0
#define KPD_ROW2_PIN	GPIO_PIN1
#define KPD_ROW3_PIN	GPIO_PIN2
#define KPD_ROW4_PIN	GPIO_PIN3
/* Keypad columns pins (GPIO_PIN0:GPIO_PIN15) */
#define KPD_COL1_PIN	GPIO_PIN4
#define KPD_COL2_PIN	GPIO_PIN5
#define KPD_COL3_PIN	GPIO_PIN6
#define KPD_COL4_PIN	GPIO_PIN7

/* Array that has keypad characters */
const u8 KPD_Number[KPD_ROWS][KPD_COLS] =
{
	{ '1', '2', '3', '+' },
	{ '4', '5', '6', '-' },
	{ '7', '8', '9', 'C' },
	{ '*', '0', '/', '=' }

};

#endif 
