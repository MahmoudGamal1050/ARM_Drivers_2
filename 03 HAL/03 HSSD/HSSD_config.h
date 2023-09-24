/*********************************************************************
* File Name    	: 	HSSD_config.h                                    *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	12/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/

#ifndef HSSD_CONFIG_H
#define HSSD_CONFIG_H
/* 7-segment Type:
*		    	  SSD_CATHODE
*                 SSD_ANODE
*/
#define SSD_COMMON SSD_ANODE
/* Choose SSD port */
#define SSD_PORT	GPIOA
/*  Choose SSD pins (GPIO_PIN0 : GPIO_PIN15) */
#define SSD_A	GPIO_PIN0
#define SSD_B	GPIO_PIN1
#define SSD_C	GPIO_PIN2
#define SSD_D	GPIO_PIN3
#define SSD_E	GPIO_PIN4
#define SSD_F	GPIO_PIN5
#define SSD_G	GPIO_PIN6


#endif 
