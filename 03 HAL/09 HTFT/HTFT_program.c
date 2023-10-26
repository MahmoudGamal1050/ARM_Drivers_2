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

	while(Copy_u8Length>0)
	{
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


void HTFT_voidWriteChar(u8 Copy_u8Xaxis, u8 Copy_u8Yaxis , u8 Copy_u8Character,
						FontDef Copy_uddtFont, u16 Copy_u8Color, u16 Copy_u8BackGroundColor )
{
	u32 L_u32Data;
	u8 L_u8Iterator1,L_u8Iterator2;
    // column address set
	HTFT_voidWriteCommand(0x2A);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(Copy_u8Xaxis);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(Copy_u8Xaxis+Copy_uddtFont.width-1);

    // row address set
	HTFT_voidWriteCommand(0x2B);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(Copy_u8Yaxis);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(Copy_u8Yaxis+Copy_uddtFont.height-1);

	HTFT_voidWriteCommand(0x2C);

	   for(L_u8Iterator1 = 0; L_u8Iterator1 < Copy_uddtFont.height; L_u8Iterator1++)
	   {
		   L_u32Data = Copy_uddtFont.data[(Copy_u8Character - 32) * Copy_uddtFont.height + L_u8Iterator1];
	        for(L_u8Iterator2 = 0; L_u8Iterator2 < Copy_uddtFont.width; L_u8Iterator2++)
	        {
	            if((L_u32Data << L_u8Iterator2) & 0x8000)
	            {
					HTFT_voidWriteData ( Copy_u8Color >> 8   ); // write hi byte
					HTFT_voidWriteData ( (u8)Copy_u8Color  ); // write lo byte

	            }
	            else
	            {
					HTFT_voidWriteData ( Copy_u8BackGroundColor >> 8   ); // write hi byte
					HTFT_voidWriteData ( (u8)Copy_u8BackGroundColor  ); // write lo byte
	            }
	        }
	    }

}

void HTFT_voidWriteString(u16 Copy_u8Xaxis, u16 Copy_u8Yaxis,  char* str,
						  FontDef Copy_uddtFont, u16 Copy_u8Color, u16 Copy_u8BackGroundColor)
{

    while(*str!='\0')
    {
        if(Copy_u8Xaxis + Copy_uddtFont.width >= 128)
        {
        	Copy_u8Xaxis = 0;
        	Copy_u8Yaxis += Copy_uddtFont.height;
            if(Copy_u8Yaxis + Copy_uddtFont.height >= 160)
            {
                break;
            }

            if(*str == ' ')
            {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

    	HTFT_voidWriteChar(Copy_u8Xaxis, Copy_u8Yaxis, *str, Copy_uddtFont, Copy_u8Color, Copy_u8BackGroundColor);
    	Copy_u8Xaxis += Copy_uddtFont.width;
        str++;
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



