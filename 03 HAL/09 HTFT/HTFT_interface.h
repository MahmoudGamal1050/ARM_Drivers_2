/*********************************************************************
* File Name    	: 	HTFT_interface.h                                 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	20/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/
#ifndef HTFT_INTERFACE_H
#define HTFT_INTERFACE_H
#include "fonts.h"

/* Color constants */
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x0400
#define LIME 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

/* Positions for HTFT_voidDrawLine function */
#define HORIZONTAL_LINE		0
#define VERTICAL_LINE		1


void HTFT_voidInit(void);

void HTFT_voidDisplayImage (const u16* Copy_Image);

void HTFT_voidDrawLine( u8 Copy_u8XaxisStart , u8 Copy_u8YaxisStart , u8 Copy_u8Position,
						u8 Copy_u8Length , u16 Copy_u8Color );


void HTFT_voidDrawRectangle (u8 Copy_u8XaxisStart, u8 Copy_u8Width, u8 Copy_u8YaxisStart,
							 u8 Copy_u8Height, u16 Copy_u8Color);

void HTFT_voidFillRectangle(u8 Copy_u8XaxisStart, u8 Copy_u8XaxisEnd, u8 Copy_u8YaxisStart,
							u8 Copy_u8YaxisEnd, u16 Copy_u16Color);

void HTFT_voidWriteChar(u8 Copy_u8Xaxis, u8 Copy_u8Yaxis , u8 Copy_u8Character,
						FontDef Copy_uddtFont, u16 Copy_u8Color, u16 Copy_u8BackGroundColor );

void HTFT_voidWriteString(u16 Copy_u8Xaxis, u16 Copy_u8Yaxis,  char* str,
						  FontDef Copy_uddtFont, u16 Copy_u8Color, u16 Copy_u8BackGroundColor);


#endif
