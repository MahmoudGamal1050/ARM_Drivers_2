/*********************************************************************
* File Name    	: 	MDMA_program.c                                 	 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	17/9/2023                                        *
* Description   : 			         				                 *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/MGPIO/MGPIO_interface.h"

#include "MCAL/MDMA/MDMA_private.h"
#include "MCAL/MDMA/MDMA_config.h"
#include "MCAL/MDMA/MDMA_interface.h"



void (*DMA_CallBackPtr[7])(void);
void MDMA_voidInit(DMA_StreamId_t Copy_uddtStreamId, DMA_ChannelId_t Copy_uddtChannelId, DMA_Direction_t Copy_uddtDirectionId,
				   DMA_CircularMode_t Copy_uddtCircularMod, DMA_MINC_t Copy_uddtMINC, DMA_PINC_t Copy_uddtPINC,
				   DMA_Size_t Copy_uddtMemSize, DMA_Size_t Copy_uddtPerSize, DMA_Priority_t Copy_uddtPriority)
{
	/* Clear EN bit to write to register DMA_SxCR */
	CLR_BIT((DMA2->Stream[Copy_uddtStreamId].CR),EN);

	/* Clear configuration register before writing to it */
	DMA2->Stream[Copy_uddtStreamId].CR = 0;

	/* Write to DMA_SxCR configuration register
	 * 1- Select Channel
	 * 2- Select Direction
	 * 3- Source increment (MINC)
	 * 4- Destination increment (PINC)
	 * 5- Source Size (MSize)
	 * 6- Destination Size (PSize)
	 * 7- Priority Level
	 */
	DMA2->Stream[Copy_uddtStreamId].CR |=
	(Copy_uddtChannelId<<CHSEL0) | (Copy_uddtDirectionId<<DIR0) | (Copy_uddtMINC<<MINC) |(Copy_uddtPINC<<PINC) |
	(Copy_uddtMemSize<<MSIZE0) | (Copy_uddtPerSize<<PSIZE0) | (Copy_uddtPriority<<PL0);


	/* Disable direct mode */
	SET_BIT((DMA2->Stream[Copy_uddtStreamId].FCR),2);

	/* Set threshold full FIFO */
	SET_BIT((DMA2->Stream[Copy_uddtStreamId].FCR),1);
	SET_BIT((DMA2->Stream[Copy_uddtStreamId].FCR),0);


}

void MDMA_voidSetAddress(DMA_StreamId_t Copy_uddtStreamId, u32 *SrcAddress, u32 *DestAddress, u32 Copy_u32Length)
{
	// send src address to PAr
	DMA2->Stream[Copy_uddtStreamId].PAR=(u32)SrcAddress;
	//send dest address to m0ar
	DMA2->Stream[Copy_uddtStreamId].M0AR=(u32)DestAddress;
	//send length to ndtr
	DMA2->Stream[Copy_uddtStreamId].NDTR=Copy_u32Length;
}

void MDMA_voidStreamEnable(DMA_StreamId_t Copy_uddtStreamId)
{
	/* Clear flags for stream x*/
	MDMA_voidClearFlags(Copy_uddtStreamId);
	/* enable stream */
	SET_BIT((DMA2->Stream[Copy_uddtStreamId].CR),EN);
}

void MDMA_voidStreamDisable(DMA_StreamId_t Copy_uddtStreamId)
{
	CLR_BIT((DMA2->Stream[Copy_uddtStreamId].CR),EN);

}

void MDMA_voidInerruptEnable( DMA_StreamId_t Copy_uddtStreamId , DMA_INTSource_t Copy_uddtINTSource )
{
    SET_BIT(DMA2->Stream[Copy_uddtStreamId].CR, Copy_uddtINTSource);
}

void MDMA_voidInerruptDiable( DMA_StreamId_t Copy_uddtStreamId , DMA_INTSource_t Copy_uddtINTSource )
{
    CLR_BIT(DMA2->Stream[Copy_uddtStreamId].CR, Copy_uddtINTSource);
}

void MDMA_voidSetCallBack(DMA_StreamId_t Copy_uddtStreamId, void ( *Ptr ) ( void ) )
{

	DMA_CallBackPtr[Copy_uddtStreamId]=Ptr;
}
void MDMA_voidClearFlags(DMA_StreamId_t Copy_uddtStreamId)
{

	switch(Copy_uddtStreamId)
	{
		case DMA_STREAM0 :
			DMA2->LIFCR|= (FLAG_CLEAR_MASK<<CFEIF0);
			break;
		case DMA_STREAM1 :
			DMA2->LIFCR|= (FLAG_CLEAR_MASK<<CFEIF1);
			break;
		case DMA_STREAM2 :
			DMA2->LIFCR|= (FLAG_CLEAR_MASK<<CFEIF2);
			break;
		case DMA_STREAM3 :
			DMA2->LIFCR|= (FLAG_CLEAR_MASK<<CFEIF3);
			break;
		case DMA_STREAM4 :
			DMA2->HIFCR|= (FLAG_CLEAR_MASK<<CFEIF4);
			break;
		case DMA_STREAM5 :
			DMA2->HIFCR|= (FLAG_CLEAR_MASK<<CFEIF5);
			break;
		case DMA_STREAM6 :
			DMA2->HIFCR|= (FLAG_CLEAR_MASK<<CFEIF6);
			break;
		case DMA_STREAM7 :
			DMA2->HIFCR|= (FLAG_CLEAR_MASK<<CFEIF7);
			break;
	}


}

void DMA2_Stream0_IRQHandler(void)
{
	if(DMA_CallBackPtr!=NULL)
	{
		DMA_CallBackPtr[0]();
	}
	/* Clear flags */
	MDMA_voidClearFlags(DMA_STREAM0);

}
