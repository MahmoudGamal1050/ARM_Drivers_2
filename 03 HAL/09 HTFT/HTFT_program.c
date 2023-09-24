/*********************************************************************
* File Name    	: 	HTFT_program.c                                   *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	20/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "MCAL/MSPI/MSPI_interface.h"

#include "HAL/HTFT/HTFT_private.h"
#include "HAL/HTFT/HTFT_config.h"
#include "HAL/HTFT/HTFT_interface.h"

void HTFT_voidInit(void)
{
	MGPIO_voidSetPinMode(TFT_A0_PIN, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(TFT_RST_PIN, GPIO_OUTPUT);

	/* Reset Sequence */
	HTFT_voidResetSequence();
	
	/* Sleep Out Command */
	HTFT_voidWriteCommand(0x11);
	
	/* Wait 150 ms */
	MSTK_voidSetBusyWait(150000);
	
	/* Color Mode Command */
	HTFT_voidWriteCommand(0x3A);
	HTFT_voidWriteData(0x05);
	
	/* Display On Command */
	HTFT_voidWriteCommand(0x29);
}

void HTFT_voidDisplayImage (const u16* Copy_PtrImage)
{
	u16 L_u16Counter;
	u8 L_u8Data;

	/* Set X Address */
	HTFT_voidWriteCommand(0x2A);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(127);

	/* Set Y Address */
	HTFT_voidWriteCommand(0x2B);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(159);

	/* RAM Write */
	HTFT_voidWriteCommand(0x2C);

	for(L_u16Counter = 0; L_u16Counter< 20480;L_u16Counter++)
	{
		/* Write the low byte */
		L_u8Data = (u8)Copy_PtrImage[L_u16Counter];
		HTFT_voidWriteData(L_u8Data);
		L_u8Data = Copy_PtrImage[L_u16Counter] >> 8;
		/* Write the high byte */
		HTFT_voidWriteData(L_u8Data);
	}


}




void HTFT_voidDrawLine( u8 Copy_u8XaxisStart , u8 Copy_u8YaxisStart , u8 Copy_u8Position, u8 Copy_u8Length , u16 Copy_u8Color )
{
	while(Copy_u8Length>0)
	{
		/* Set X Address */
		HTFT_voidWriteCommand(0x2A);
		HTFT_voidWriteData(0);
		HTFT_voidWriteData(Copy_u8XaxisStart);

		/* Set Y Address */
		HTFT_voidWriteCommand(0x2B);
		HTFT_voidWriteData(0);
		HTFT_voidWriteData(Copy_u8YaxisStart);

		/* RAM Write */
		HTFT_voidWriteCommand(0x2C);
		HTFT_voidWriteData ( Copy_u8Color >> 8   ); // write high byte
		HTFT_voidWriteData ( (u8)Copy_u8Color ); // write low byte
		Copy_u8Length--;

		if(Copy_u8Position== HORIZONTAL_LINE)
		{
			Copy_u8XaxisStart++;

		}
		else if(Copy_u8Position== VERTICAL_LINE)
		{
			Copy_u8YaxisStart++;
		}


	}
}

void HTFT_voidDrawRectangle (u8 Copy_u8XaxisStart, u8 Copy_u8Width, u8 Copy_u8YaxisStart, u8 Copy_u8Height, u16 Copy_u8Color)
{

	HTFT_voidDrawLine (Copy_u8XaxisStart, Copy_u8YaxisStart,HORIZONTAL_LINE, Copy_u8Width, Copy_u8Color);
	HTFT_voidDrawLine (Copy_u8XaxisStart, Copy_u8YaxisStart,VERTICAL_LINE, Copy_u8Height, Copy_u8Color);
	HTFT_voidDrawLine (Copy_u8XaxisStart , Copy_u8YaxisStart+Copy_u8Height, HORIZONTAL_LINE, Copy_u8Width, Copy_u8Color);
	HTFT_voidDrawLine (Copy_u8XaxisStart+Copy_u8Width, Copy_u8YaxisStart, VERTICAL_LINE, Copy_u8Height, Copy_u8Color);

}

void HTFT_voidFillRectangle(u8 Copy_u8XaxisStart, u8 Copy_u8XaxisEnd, u8 Copy_u8YaxisStart,
							u8 Copy_u8YaxisEnd, u16 Copy_u16Color)
{
	u16 L_u16Counter;
	u16 L_u16Pixels = (Copy_u8XaxisEnd-Copy_u8XaxisStart+1)*(Copy_u8YaxisEnd-Copy_u8YaxisStart+1);
	/* Set X Address */
	HTFT_voidWriteCommand(0x2A);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(Copy_u8XaxisStart);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(Copy_u8XaxisEnd);

	/* Set Y Address */
	HTFT_voidWriteCommand(0x2B);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(Copy_u8YaxisStart);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(Copy_u8YaxisEnd);

	/* RAM Write */
	HTFT_voidWriteCommand(0x2C);

	for(L_u16Counter = 0; L_u16Counter< L_u16Pixels;L_u16Counter++)
	{
		/* Write the high byte */
		HTFT_voidWriteData(Copy_u16Color>>8);

		/* Write the low byte */
		HTFT_voidWriteData((u8)Copy_u16Color);

	}

}


void HTFT_voidWriteChar(u8 Copy_u8Xaxis , u8 Copy_u8Yaxis , u16 *Copy_ptrChar, u16 Copy_u8Color ){

	u16  LOC_u16Mask = 0x01 ;
	u16 LOC_u16Pixel       ;

	for( u8 LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 16 ; LOC_u8Iterator1++ ){

		for( u8 LOC_u8Iterator2 = 0 ; LOC_u8Iterator2 < 16 ; LOC_u8Iterator2++ ){

			/* Set The Position Of 5x7 Character */
			HTFT_voidWriteCommand( 0x2A ); // set column range (x0,x1)
			HTFT_voidWriteData(0);
			HTFT_voidWriteData( Copy_u8Xaxis + LOC_u8Iterator1 );

			HTFT_voidWriteCommand( 0x2B ); // set row range (y0,y1)
			HTFT_voidWriteData(0);
			HTFT_voidWriteData(Copy_u8Yaxis + LOC_u8Iterator2);

			HTFT_voidWriteCommand( 0x2C ); // memory write

			LOC_u16Pixel = Copy_ptrChar[ LOC_u8Iterator1 ] & LOC_u16Mask ;

			if( LOC_u16Pixel != 0  )
			{
				HTFT_voidWriteData ( Copy_u8Color >> 8   ); // write hi byte
				HTFT_voidWriteData ( (u8)Copy_u8Color  ); // write lo byte
			}
			LOC_u16Mask <<= 1 ;

		}

		LOC_u16Mask = 0x01 ;

	}

}

static void HTFT_voidWriteCommand(u8 Copy_u8Command)
{
	
	/* Set A0 Pin to Low */
	MGPIO_voidSetPinValue(TFT_A0_PIN,GPIO_LOW);
	
	/* Send Command over SPI */
	MSPI_voidSendReceiveSynch(SPI1,&Copy_u8Command);
}

static void HTFT_voidWriteData   (u8 Copy_u8Data)
{
	
	/* Set A0 Pin to High */
	MGPIO_voidSetPinValue(TFT_A0_PIN,GPIO_HIGH);
	
	/* Send data over SPI */
	MSPI_voidSendReceiveSynch(SPI1,&Copy_u8Data);
}


static void HTFT_voidResetSequence(void)
{
	MGPIO_voidSetPinValue(TFT_RST_PIN,GPIO_HIGH);
	MSTK_voidSetBusyWait(200);
	MGPIO_voidSetPinValue(TFT_RST_PIN,GPIO_LOW);
	MSTK_voidSetBusyWait(2);
	MGPIO_voidSetPinValue(TFT_RST_PIN,GPIO_HIGH);
	MSTK_voidSetBusyWait(200);
	MGPIO_voidSetPinValue(TFT_RST_PIN,GPIO_LOW);
	MSTK_voidSetBusyWait(200);
	MGPIO_voidSetPinValue(TFT_RST_PIN,GPIO_HIGH);
	MSTK_voidSetBusyWait(200000);
}



