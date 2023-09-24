/*********************************************************************
* File Name    	: 	MEXTI_private.h                                 	 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	12/9/2023                                        *
* Description   : 			         				                 *                         
**********************************************************************/
#ifndef	MSTK_PRIVATE_H
#define	MSTK_PRIVATE_H


#define		STK_SINGLE_INTERVAL		0
#define		STK_PERIOD_INTERVAL		1

#define STK_BASE_ADDRESS	(0xE000E010)
typedef struct
{
	u32		CTRL;
	u32		LOAD;
	u32		VAL;
	u32		CALIB;
	
}STK_t;

#define			MSTK		((volatile STK_t *)(STK_BASE_ADDRESS))

/* STK_CTRL Pins Definitions */
#define ENABLE		0
#define TICKINT		1
#define CLKSOURCE	2
#define COUNTFLAG	16


#endif
