/*********************************************************************
* File Name    	: 	HIR_program.c                                    *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	18/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "MCAL/MEXTI/MEXTI_interface.h"
#include "MCAL/MNVIC/MNVIC_interface.h"

#include "HAL/HIR/HIR_private.h"
#include "HAL/HIR/HIR_config.h"
#include "HAL/HIR/HIR_interface.h"

/* Global flag to indicate start of IR frame */
u8  G_u8StartFlag = 0;
/* Global array to hold time of each frame bit */
u32 G_u32FrameTime[50] ;
/* Index for frame time array */
u8  G_u8FrameTimeIndex = 0;
/* Global variable to save IR data */
u8  G_u8IRData = 0;

/* EXTI0 call back function with falling edge sensing to calculate
 * time of each bit of the IR frame and save it to G_u32FrameTime */
void EXTI0_CallBackFunction(void);
/* Private function  to handle data after all frame is received */
static void IR_voidEndOfFrameHandler(void);


/* Initialize IR */
void HIR_voidInit( void )
{
	/* Configure PA0 as input pull up for EXTI0 */
	MGPIO_voidSetPinMode(GPIOA, GPIO_PIN8, GPIO_INPUT);
	MGPIO_voidSetInputState(GPIOA, GPIO_PIN8, GPIO_INPUT_PULL_UP);


	/* Initialize STK with frequency equals AHB/8 or SYS_CLK/16 = 1MHz */
	MSTK_voidInit(STK_AHB_Div_BY_8);

	/* Set callback function for EXTI1 */
	MEXTI_voidSetCallBack(EXTI_LINE8, EXTI0_CallBackFunction);
	/* Enable EXTI1 */
	MEXTI_voidEnableEXTI(EXTI_LINE8);
	/* Set EXTI configuration for PA0 */
	MEXTI_voidSetEXTIConfig(EXTI_LINE8, EXTI_PORTA);
	/* Set sensing trigger for EXTI0 as falling edge */
	MEXTI_voidSetTriggerSource(EXTI_LINE8, EXTI_FALLING_EDGE);


	/* Set interrupt priority for EXTI0 */
	MNVIC_voidSetIntPriority(NVIC_EXTI9_5, GRB_00_SUB_16, 1, 1);
	/* Enable interrupt for EXTI0 */
	MNVIC_voidEnablePerInt(NVIC_EXTI9_5);

}

u8 HIR_u8GetData ( void )
{
	u8 L_u8IRData = G_u8IRData;
	/* Reset IR data to return 0 if no button is pressed */
	G_u8IRData =0;
	/* Return IR data */
	return L_u8IRData ;
}


void EXTI0_CallBackFunction(void)
{
	/* Start bit */
	if ( G_u8StartFlag == 0 )
	{
		/* Start flag =1 to get next bits */
		G_u8StartFlag = 1;
		/* Start Systick to calculate time of IR start bit */
		MSTK_voidSetIntervalSingle(100000, IR_voidEndOfFrameHandler);
	}
	else if ( G_u8StartFlag == 1 )
	{
		/* Get frame time using systick and save it to the array */
		G_u32FrameTime[ G_u8FrameTimeIndex ] = MSTK_u32GetElapsedTime();
		/* Increment array index */
		G_u8FrameTimeIndex++ ;
		/* Restart systick to calculate next bit time
		 * and call  IR_voidEndOfFrameHandler after frame ends */
		MSTK_voidSetIntervalSingle(100000, IR_voidEndOfFrameHandler);

	}


}

static void IR_voidEndOfFrameHandler(void)
{
	//MGPIO_voidTogglePin(GPIOA, GPIO_PIN9);
	u8 L_u8Iterator;
	/* Get data using frame time array (bits 17:24) and save it to G_u8IRData  */
	for( L_u8Iterator = 17 ; L_u8Iterator < 25 ; L_u8Iterator++ )
	{
		/* Logical 0 */
		if( G_u32FrameTime[ L_u8Iterator ] > 1000 && G_u32FrameTime[ L_u8Iterator ] < 1400)
		{
			CLR_BIT( G_u8IRData ,L_u8Iterator-17  );
		}
		/* Logical 1 */
		else if( G_u32FrameTime[ L_u8Iterator ] >= 2000 )
		{
			SET_BIT( G_u8IRData ,L_u8Iterator-17  );
		}

	}
	/* Reset start flag for next frame */
	G_u8StartFlag =0;
	/* Reset array index */
	G_u8FrameTimeIndex=0;

}

