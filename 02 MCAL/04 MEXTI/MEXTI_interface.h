/*********************************************************************
* File Name    	: 	MEXTI_interface.h                                *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	11/9/2023                                        *
* Description   : 			         				                 *                         
*********************************************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


/* External Interrupt Lines */
typedef enum
{
	EXTI_LINE0 ,
	EXTI_LINE1 ,
	EXTI_LINE2 ,
	EXTI_LINE3 ,	
	EXTI_LINE4 ,
	EXTI_LINE5 ,
	EXTI_LINE6 ,
	EXTI_LINE7 ,	
	EXTI_LINE8 ,
	EXTI_LINE9 ,
	EXTI_LINE10,
	EXTI_LINE11,		
	EXTI_LINE12,
	EXTI_LINE13,
	EXTI_LINE14,
	EXTI_LINE15
}EXTI_LINE_t;

/* EXTI Sense Modes */
typedef enum
{
	EXTI_FALLING_EDGE,
	EXTI_RISING_EDGE,
	EXTI_ON_CHANGE	
	
}EXTI_TriggerMode_t;

/* EXTI Ports */
typedef enum
{
	EXTI_PORTA,
	EXTI_PORTB,
	EXTI_PORTC	
}EXTI_Port_t;


void MEXTI_voidEnableEXTI (EXTI_LINE_t Copy_uddtLineNum);
void MEXTI_voidDisableEXTI (EXTI_LINE_t Copy_uddtLineNum);
void MEXTI_voidSoftwareInterrupt (EXTI_LINE_t Copy_uddtLineNum);
void MEXTI_voidSetTriggerSource (EXTI_LINE_t Copy_uddtLineNum, EXTI_TriggerMode_t  Copy_uddtTrigger);
void MEXTI_voidSetEXTIConfig(EXTI_LINE_t Copy_uddtLineNum , EXTI_Port_t Copy_uddtPortNum); 
void MEXTI_voidSetCallBack(EXTI_LINE_t Copy_uddtLineNum, void (*ptr) (void));
#endif /* EXTI_INTERFACE_H_ */
