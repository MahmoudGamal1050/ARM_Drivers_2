/*********************************************************************
* File Name    	: 	HLCD_program.c                                   *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	15/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "LIB/DELAY_interface.h"

#include "MCAL/MGPIO/MGPIO_interface.h"

#include "HAL/HLCD/HLCD_private.h"
#include "HAL/HLCD/HLCD_config.h"
#include "HAL/HLCD/HLCD_interface.h"



void HLCD_voidInit(void)
{
	/* Set RS,RW,EN as output push pull */
	MGPIO_voidSetPinMode(LCD_CONTROL_PORT, LCD_RS, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(LCD_CONTROL_PORT, LCD_RW, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(LCD_CONTROL_PORT, LCD_EN, GPIO_OUTPUT);

	/* Initialize EN pin by zero */
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, GPIO_LOW);
	_delay_ms(1);

	/* 8_Bit_Mode */
	#if LCD_MODE ==  _8_BIT_MODE
		/* Configure LCD data port as output */
		MGPIO_voidSetPortMode(LCD_DATA_PORT, LCD_PINS_POSITION, GPIO_OUTPUT);
		_delay_ms(30);
		/* Use 2-line LCD + 8-bit Mode + 5*7 dot display Mode */
		HLCD_voidSendCommand(FUNCTION_SET_8BIT);
		_delay_ms(1);

	/* 4_Bit_Mode */
	#elif LCD_MODE == _4_BIT_MODE
		/* Configure LCD data pins as output */
		MGPIO_voidSetPinMode(LCD_DATA_PORT, LCD_D4, GPIO_OUTPUT);
		MGPIO_voidSetPinMode(LCD_DATA_PORT, LCD_D5, GPIO_OUTPUT);
		MGPIO_voidSetPinMode(LCD_DATA_PORT, LCD_D6, GPIO_OUTPUT);
		MGPIO_voidSetPinMode(LCD_DATA_PORT, LCD_D7, GPIO_OUTPUT);

		_delay_ms(30);

		/* Use 2-line LCD + 4-bit Mode + 5*7 dot display Mode */
		HLCD_voidSendCommand(0x30);
		HLCD_voidSendCommand(RETURN_HOME);
		HLCD_voidSendCommand(FUNCTION_SET_4BIT);
		_delay_ms(1);


	#endif
		/* Enable LCD display */
		HLCD_voidSendCommand(DISPLAY_ON_CURSOR_OFF);
		_delay_ms(1);
		/* Clear screen at the beginning */
		HLCD_voidSendCommand(DISPLAY_CLEAR);
		_delay_ms(1);


}
static void HLCD_voidSendCommand(u8 copy_u8Command)
{
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS, GPIO_LOW); /* RS = 0 for command */
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW, GPIO_LOW); /* RW = 0 for writing */



	/* 8_Bit_Mode */
#if LCD_MODE == _8_BIT_MODE

	/* Write command on LCD data port */
	MGPIO_voidSetPortValue(LCD_DATA_PORT, LCD_PINS_POSITION, copy_u8Command);

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, GPIO_HIGH); /* EN = 1 */
	_delay_ms(1);
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, GPIO_LOW);  /* EN = 0 */
	_delay_ms(1);

	/* 4_Bit_Mode */
#elif LCD_MODE == _4_BIT_MODE
	/* Write command high nibble on LCD  4 data pins */
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D4, GET_BIT(copy_u8Command, 4));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D5, GET_BIT(copy_u8Command, 5));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D6, GET_BIT(copy_u8Command, 6));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D7, GET_BIT(copy_u8Command, 7));

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, GPIO_HIGH); /* EN = 1 */
	_delay_ms(1);
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, GPIO_LOW);  /* EN = 0 */
	_delay_ms(1);
	/* Write command low nibble on LCD  4 data pins */
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D4, GET_BIT(copy_u8Command, 0));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D5, GET_BIT(copy_u8Command, 1));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D6, GET_BIT(copy_u8Command, 2));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D7, GET_BIT(copy_u8Command, 3));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_EN, GPIO_HIGH);	/* EN = 1 */
	_delay_ms(1);
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, GPIO_LOW);  /* EN = 0 */


#endif


}
void HLCD_voidWriteData(u8 copy_u8Data)
{

	/* 8_Bit_Mode */
#if LCD_MODE == _8_BIT_MODE
	/* Write data on LCD data port */
	MGPIO_voidSetPortValue(LCD_DATA_PORT, LCD_PINS_POSITION, copy_u8Data);

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS, GPIO_HIGH); /* RS = 1 for data */
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW, GPIO_LOW);	/* RW = 0 for writing */

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, GPIO_HIGH);	/* EN = 1 */
	_delay_ms(1);
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, GPIO_LOW);	/* EN = 0 */
	_delay_ms(1);

	/* 4_Bit_Mode */
#elif LCD_MODE == _4_BIT_MODE
	/* Write command high nibble on LCD  4 data pins */
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D4, GET_BIT(copy_u8Data, 4));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D5, GET_BIT(copy_u8Data, 5));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D6, GET_BIT(copy_u8Data, 6));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D7, GET_BIT(copy_u8Data, 7));


	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS, GPIO_HIGH); /* RS = 1 for data */
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW, GPIO_LOW);	/* RW = 0 for writing */

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, GPIO_HIGH); /* EN = 1 */
	_delay_ms(1);
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, GPIO_LOW);  /* EN = 0 */
	_delay_ms(1);
	/* Write command low nibble on LCD  4 data pins */
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D4, GET_BIT(copy_u8Data, 0));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D5, GET_BIT(copy_u8Data, 1));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D6, GET_BIT(copy_u8Data, 2));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_D7, GET_BIT(copy_u8Data, 3));
	MGPIO_voidSetPinValue(LCD_DATA_PORT, LCD_EN, GPIO_HIGH);	/* EN = 1 */
	_delay_ms(1);
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, GPIO_LOW);  /* EN = 0 */


#endif

}

void HLCD_voidClearScreen(void)
{
	HLCD_voidSendCommand(DISPLAY_CLEAR);
	_delay_ms(1);
}

void HLCD_voidSetPosition(u8 Copy_u8Row, u8 Copy_u8Col)
{
	/* Check that column is in range of LCD */
	if((Copy_u8Col >=0) && (Copy_u8Col <=15))
	{
		switch(Copy_u8Row)
		{
			/* First row */
			case 0 :
				/* Go to required position */
				HLCD_voidSendCommand(LCD_SET_ROW0+Copy_u8Col);
				break;
			/* Second row */
			case 1 :
				/* Go to required position */
				HLCD_voidSendCommand(LCD_SET_ROW1+Copy_u8Col);
				break;
			default :
				/* Wrong row number */
				break;
		}
	}
	else
	{
		/* Wrong column number */
	}

}

void HLCD_voidWriteString(char *Copy_u8PtrData)
{
	u8 Local_u8Counter = 0;

	/* Iterate the string until reaching null terminator */
	while(Copy_u8PtrData[Local_u8Counter] != '\0')
	{
		/* Write current character to LCD */
		HLCD_voidWriteData(Copy_u8PtrData[Local_u8Counter]);
		/* Increment the counter */
		Local_u8Counter++;
	}
}


void HLCD_voidSaveCustomChar(u8 Copy_u8arr[], u8 copy_u8Location)
{
	u8 Local_u8Counter;
	/* Check that location is in range */
	if((copy_u8Location>=0) && (copy_u8Location<=7))
	{
		/* Send command to move address counter from DDRAM to CGRAM required location */
		HLCD_voidSendCommand(DDRAM_TO_CGRAM + copy_u8Location*8);
		for(Local_u8Counter = 0; Local_u8Counter<7 ; Local_u8Counter++)
		{
			/* Write pattern to CGRAM */
			HLCD_voidWriteData(Copy_u8arr[Local_u8Counter]);
		}
		/* Return address counter to DDRAM */
		HLCD_voidSendCommand(CGRAM_TO_DDRAM);
	}

	else
	{
		/* Wrong location */
	}

}


void HLCD_voidWriteNumber(u16 Copy_u16Number)
{
	/* Array to store the number digits */
	u8 buffer[10];
	/* Variable used as index for buffer */
	s8 Local_uIndex=-1;
	/* Loop to get every digit */
	if(0 == Copy_u16Number)
	{
		HLCD_voidWriteData('0');
	}
	else
	{


		while(Copy_u16Number!=0)
		{
			/* Save the digit in the buffer */
			buffer[Local_uIndex+1] = Copy_u16Number%10;
			/* Remove the first digit */
			Copy_u16Number /= 10;
			/* Increment the index */
			Local_uIndex++;
		}
		/* Loop to write number to LCD starting from highest digit */
		while(Local_uIndex!=-1)
		{
			HLCD_voidWriteData(buffer[Local_uIndex]+'0');
			Local_uIndex--;
		}
	}
}

void HLCD_voidWriteFloatNumber(f32 Copy_f16Number)
{
	u16 Local_u16Number = (u16)Copy_f16Number;
	HLCD_voidWriteNumber(Local_u16Number);
	HLCD_voidWriteData('.');
	HLCD_voidWriteNumber((Copy_f16Number-Local_u16Number)*100);

}

