/*********************************************************************
* File Name    	: 	MNVIC_program.c                                  *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	10/9/2023                                        *
* Description   : 			         				                 *                         
*********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/MNVIC/MNVIC_private.h"
#include "MCAL/MNVIC/MNVIC_config.h"
#include "MCAL/MNVIC/MNVIC_interface.h"




void MNVIC_voidSetGroupingMode(GroupMode_t Copy_uddtGroupMode)
{
	/* Assign numbers of groups and subgroups used in the system*/
	SCB_AIRCR = VECTKEY|(Copy_uddtGroupMode<<8);
}

void MNVIC_voidEnablePerInt  ( IntPos_t Copy_uddtIntPos )
{
	if(Copy_uddtIntPos<=84)
	{
		MNVIC -> ISER[Copy_uddtIntPos/32] =  (1<<(Copy_uddtIntPos%32));
	}
	
	else
	{
		/* Error : Interrupt position isn't available in this MC */
	}
}


void MNVIC_voidDisablePerInt  ( IntPos_t Copy_uddtIntPos )
{
	if(Copy_uddtIntPos<=84)
	{
		MNVIC -> ICER[Copy_uddtIntPos/32] = (1<<(Copy_uddtIntPos%32)) ;
	}
	
	else
	{
		/* Error : Interrupt position isn't available in this MC */
	}
}


void MNVIC_voidSetPendingFlag ( IntPos_t Copy_uddtIntPos )
{
	if(Copy_uddtIntPos<=84)
	{
		MNVIC -> ISPR[Copy_uddtIntPos/32] = (1<<(Copy_uddtIntPos%32)) ;
	}
	
	else
	{
		/* Error : Interrupt position isn't available in this MC */
	}
}


void MNVIC_voidClearPendingFlag ( IntPos_t Copy_uddtIntPos )
{
	if(Copy_uddtIntPos<=84)
	{
		MNVIC -> ICPR[Copy_uddtIntPos/32] = (1<<(Copy_uddtIntPos%32)) ;
	}
	
	else
	{
		/* Error : Interrupt position isn't available in this MC */
	}
}

u8   MNVIC_u8GetActiveFlag( IntPos_t Copy_uddtIntPos )
{
	u8 Local_u8ActiveFlag;
	if(Copy_uddtIntPos<=84)
	{
		Local_u8ActiveFlag = GET_BIT(MNVIC -> IABR[Copy_uddtIntPos/32],1<<(Copy_uddtIntPos%32)) ;
	}
	
	else
	{
		/* Error : Interrupt position isn't available in this MC */
	}
	
	return Local_u8ActiveFlag;
}


void MNVIC_voidSetIntPriority(IntPos_t Copy_uddtIntPos ,GroupMode_t Copy_uddtGroupMode, u8 Copy_u8GroupPriority , u8 Copy_u8SubPriority)
{

	u8 Local_u8Priority =  Copy_u8SubPriority | (Copy_u8GroupPriority << (Copy_uddtGroupMode-3) ) ;

	MNVIC -> IPR[Copy_uddtIntPos/32] = (Local_u8Priority << 4 );




}















