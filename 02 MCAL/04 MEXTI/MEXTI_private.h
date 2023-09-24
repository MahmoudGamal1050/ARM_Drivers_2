/*********************************************************************
* File Name    	: 	MEXTI_private.h                                  *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	11/9/2023                                        *
* Description   : 			         				                 *                         
*********************************************************************/
#ifndef		MEXTI_PRIVATE_H
#define		MEXTI_PRIVATE_H

#define		EXTI_BASE_ADD			(0x40013C00)
#define		SYSCFG_BASE_ADD			(0x40013800)

typedef struct
{

	u32 EXTI_IMR;
	u32 EXTI_EMR;
	u32 EXTI_RTSR;
	u32 EXTI_FTSR;
	u32 EXTI_SWIER;
	u32 EXTI_PR;

}EXTI_t;

typedef struct{

	u32 SYSCFG_MEMRMP;
	u32 SYSCFG_PMC;
	u32 SYSCFG_EXTICR[4];
	u32 SYSCFG_CMPCR;
}SYSCFG_t;
#define MEXTI ((volatile EXTI_t *) EXTI_BASE_ADD)
#define MSYSCFG ((volatile SYSCFG_t *) SYSCFG_BASE_ADD)

#endif /* EXTI_PRIVATE_H_ */


