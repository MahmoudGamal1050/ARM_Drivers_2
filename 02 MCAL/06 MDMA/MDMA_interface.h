/*********************************************************************
* File Name    	: 	MDMA_interface.h                               	 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	17/9/2023                                        *
* Description   : 			         				                 *
**********************************************************************/

#ifndef MDMA_INTERFACE_H
#define MDMA_INTERFACE_H




/* DMA Stream options */
typedef enum
{
	DMA_STREAM0,
	DMA_STREAM1,
	DMA_STREAM2,
	DMA_STREAM3,
	DMA_STREAM4,
	DMA_STREAM5,
	DMA_STREAM6,
	DMA_STREAM7,

}DMA_StreamId_t;

/* DMA Stream options */
typedef enum
{
	DMA_CHANNEL0,
	DMA_CHANNEL1,
	DMA_CHANNEL2,
	DMA_CHANNEL3,
	DMA_CHANNEL4,
	DMA_CHANNEL5,
	DMA_CHANNEL6,
	DMA_CHANNEL7,

}DMA_ChannelId_t;



/* Direction */
typedef enum
{
	DMA_PER2MEM,
	DMA_MEM2PER,
	DMA_MEM2MEM,

}DMA_Direction_t;


/* Circulation */
typedef enum
{
	DMA_CIRCULAR_DIS,
	DMA_CIRCULAR_EN,

}DMA_CircularMode_t;


/* MINC */
typedef enum
{
	DMA_MEM_INC_DIS,
	DMA_MEM_INC_EN,

}DMA_MINC_t;


/* PINC */
typedef enum
{
	DMA_PER_INC_DIS,
	DMA_PER_INC_EN,

}DMA_PINC_t;


/* Size */
typedef enum
{
	DMA_BYTE,
	DMA_TWO_BYTES,
	DMA_FOUR_BYTES

}DMA_Size_t;


/*  Priority */
typedef enum
{
	DMA_LOW      ,
	DMA_MEDIUM   ,
	DMA_HIGH     ,
	DMA_VERY_HIGH,

}DMA_Priority_t;


/*  Interrupt Sources */
typedef enum
{
	DMA_DIRECT_MODE_ERROR=1,
	DMA_TRANSFER_ERROR,
	DMA_HALF_TRANSFER,
	DMA_TRANSFER_COMPLETE,

}DMA_INTSource_t;



void MDMA_voidInit(DMA_StreamId_t Copy_uddtStreamId, DMA_ChannelId_t Copy_uddtChannelId,
				   DMA_Direction_t Copy_uddtDirectionId, DMA_CircularMode_t Copy_uddtCircularMod,
				   DMA_MINC_t Copy_uddtMINC, DMA_PINC_t Copy_uddtPINC, DMA_Size_t Copy_uddtMemSize,
				   DMA_Size_t Copy_uddtPerSize, DMA_Priority_t Copy_uddtPriority);

void MDMA_voidSetAddress(u8 Copy_u8StreamId, u32 *SrcAddress, u32 *DestAddress, u32 Copy_u32Length);
 
void MDMA_voidStreamEnable( u8 Copy_u8StreamId );
void MDMA_voidStreamDisable( u8 Copy_u8StreamId );

void MDMA_voidInerruptEnable( DMA_StreamId_t Copy_uddtStreamId , DMA_INTSource_t Copy_uddtINTSource );
void MDMA_voidInerruptDiable( DMA_StreamId_t Copy_uddtStreamId , DMA_INTSource_t Copy_uddtINTSource );
void MDMA_voidSetCallBack(u8 Copy_u8StreamId, void ( *Ptr ) ( void ) );

void MDMA_voidClearFlags(DMA_StreamId_t Copy_uddtStreamId);


#endif /* DMA_INTERFACE_H */
