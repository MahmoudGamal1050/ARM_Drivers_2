/*********************************************************************
* File Name    	: 	MNVIC_private.h                                  *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	10/9/2023                                        *
* Description   : 			         				                 *                         
*********************************************************************/
#ifndef		MNVIC_PRIVATE_H
#define		MNVIC_PRIVATE_H

#define			NVIC_BASE_ADD			(0xE000E100)

typedef struct
{
	u32 ISER[8];			/* Interrupt set-enable registers */
	u32 RESERVED1[24];
	u32 ICER[8];			/* Interrupt clear-enable registers */
	u32 RESERVED2[24];
	u32 ISPR[8];			/* Interrupt set-pending registers */
	u32 RESERVED3[24];
	u32 ICPR[8];			/* Interrupt clear-pending registers */
	u32 RESERVED4[24];
	u32 IABR[8];			/* Interrupt active bit registers */
	u32 RESERVED5[56];
	u32 IPR[60];			/* Interrupt priority registers */
	u32 RESERVED6[580];
	u32 STIR;				/* Software trigger interrupt register */
}NVIC_r;

/* Pointer to NVIC registers struct */
#define MNVIC ((volatile NVIC_r*)NVIC_BASE_ADD)

/* Application interrupt and reset control register definition */
#define	SCB_AIRCR	*((volatile u32 *)(0xE000ED0C))

#define		VECTKEY		(0x05FA0000) /* Key to write to AIRCR register */


#endif




