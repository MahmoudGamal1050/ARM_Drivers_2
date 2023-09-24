/*********************************************************************
* File Name    	: 	MEXTI_program.c                                  *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	11/9/2023                                        *
* Description   : 			         				                 *                         
*********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/MEXTI/MEXTI_private.h"
#include "MCAL/MEXTI/MEXTI_config.h"
#include "MCAL/MEXTI/MEXTI_interface.h"

static u32 EXTI_SYSCFG_Mask[4]= {0x0000FFF0,0x0000FF0F,0x0000F0FF,0x00000FFF};

void (*EXTI_CallBack[16])(void);


void MEXTI_voidEnableEXTI (EXTI_LINE_t Copy_uddtLineNum)
{
	SET_BIT(MEXTI -> EXTI_IMR,Copy_uddtLineNum);


}
void MEXTI_voidDisableEXTI (EXTI_LINE_t Copy_uddtLineNum)
{
	CLR_BIT(MEXTI -> EXTI_IMR,Copy_uddtLineNum);
}
void MEXTI_voidSoftwareInterrupt (EXTI_LINE_t Copy_uddtLineNum)
{
	SET_BIT(MEXTI -> EXTI_SWIER,Copy_uddtLineNum);

}
void MEXTI_voidSetTriggerSource (EXTI_LINE_t Copy_uddtLineNum, EXTI_TriggerMode_t  Copy_uddtTrigger)
{
	switch(Copy_uddtTrigger)
	{
		case EXTI_FALLING_EDGE:
			SET_BIT(MEXTI -> EXTI_FTSR,Copy_uddtLineNum);
			break;
		case EXTI_RISING_EDGE:
			SET_BIT(MEXTI -> EXTI_RTSR,Copy_uddtLineNum);
			break;
		case EXTI_ON_CHANGE:
			SET_BIT(MEXTI -> EXTI_FTSR,Copy_uddtLineNum);
			SET_BIT(MEXTI -> EXTI_RTSR,Copy_uddtLineNum);
			break;
		default :
			break;
	}

}
void MEXTI_voidSetEXTIConfig(EXTI_LINE_t Copy_uddtLineNum , EXTI_Port_t Copy_uddtPortNum)
{

	MSYSCFG ->SYSCFG_EXTICR[Copy_uddtLineNum/4] = EXTI_SYSCFG_Mask[Copy_uddtLineNum%4];
	MSYSCFG ->SYSCFG_EXTICR[Copy_uddtLineNum/4] |= Copy_uddtPortNum<<((Copy_uddtLineNum%4)*4);

}

void MEXTI_voidSetCallBack(EXTI_LINE_t Copy_uddtLineNum, void (*ptr) (void))
{
	EXTI_CallBack[Copy_uddtLineNum] = ptr;
}


void EXTI0_IRQHandler(void)
{
	EXTI_CallBack[0]();
	SET_BIT(MEXTI -> EXTI_PR,0);
}

void EXTI1_IRQHandler(void)
{
	EXTI_CallBack[1]();
	SET_BIT(MEXTI -> EXTI_PR,1);

}

void EXTI2_IRQHandler(void)
{
	EXTI_CallBack[2]();
	SET_BIT(MEXTI -> EXTI_PR,1);

}
void EXTI3_IRQHandler(void)
{
	EXTI_CallBack[3]();
	SET_BIT(MEXTI -> EXTI_PR,1);

}

void EXTI4_IRQHandler(void)
{
	EXTI_CallBack[4]();
	SET_BIT(MEXTI -> EXTI_PR,1);

}

void EXTI9_5_IRQHandler(void)
{
	if(GET_BIT(MEXTI -> EXTI_PR, 5))
	{
		EXTI_CallBack[5]();
		SET_BIT(MEXTI -> EXTI_PR,5);
	}

	if(GET_BIT(MEXTI -> EXTI_PR, 6))
	{
		EXTI_CallBack[6]();
		SET_BIT(MEXTI -> EXTI_PR,6);
	}

	if(GET_BIT(MEXTI -> EXTI_PR, 7))
	{
		EXTI_CallBack[7]();
		SET_BIT(MEXTI -> EXTI_PR,7);
	}

	if(GET_BIT(MEXTI -> EXTI_PR, 8))
	{
		EXTI_CallBack[8]();
		SET_BIT(MEXTI -> EXTI_PR,8);
	}

	if(GET_BIT(MEXTI -> EXTI_PR, 9))
	{
		EXTI_CallBack[9]();
		SET_BIT(MEXTI -> EXTI_PR,9);
	}


}

void EXTI15_10_IRQHandler(void)
{
	if(GET_BIT(MEXTI -> EXTI_PR, 10))
	{
		EXTI_CallBack[10]();
		SET_BIT(MEXTI -> EXTI_PR,10);
	}

	if(GET_BIT(MEXTI -> EXTI_PR, 11))
	{
		EXTI_CallBack[11]();
		SET_BIT(MEXTI -> EXTI_PR,11);
	}

	if(GET_BIT(MEXTI -> EXTI_PR, 12))
	{
		EXTI_CallBack[12]();
		SET_BIT(MEXTI -> EXTI_PR,12);
	}

	if(GET_BIT(MEXTI -> EXTI_PR, 13))
	{
		EXTI_CallBack[13]();
		SET_BIT(MEXTI -> EXTI_PR,13);
	}

	if(GET_BIT(MEXTI -> EXTI_PR, 14))
	{
		EXTI_CallBack[14]();
		SET_BIT(MEXTI -> EXTI_PR,14);
	}

	if(GET_BIT(MEXTI -> EXTI_PR, 15))
	{
		EXTI_CallBack[15]();
		SET_BIT(MEXTI -> EXTI_PR,15);
	}



}





