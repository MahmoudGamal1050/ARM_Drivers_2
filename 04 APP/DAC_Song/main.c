/*********************************************************************
* File Name    	: 	main.c                                 			 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	13/9/2023                                        *
* Description   : 	Play song using DAC					             *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "LIB/song.h"

#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "MCAL/MDAC/MDAC_interface.h"

u32 Song_Counter = 0;

/* Function to send sample to DAC every 125us */
void DAC_voidCallBack( void );

int main(void)
{

	/* Initialize RCC with AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);

	/* Initialize DAC */
	MDAC_voidInit();
	/* Initialize STK with frequency equals AHB/8 or SYS_CLK/16 = 1MHz */
	MSTK_voidInit(STK_AHB_Div_BY_8);
	/* Set interval to call DAC_voidCallBack every 125us */
	MSTK_voidSetIntervalPeriodic(125, DAC_voidCallBack);
	while(1)
	{


	}
}

void DAC_voidCallBack( void )
{
	/* Send sample to DAC */
	MDAC_voidWrie(Song[Song_Counter]);
	/* Increment song index */
	Song_Counter++;

	if( Song_Counter == SongLen )
	{
		/* Replay the song */
		Song_Counter = 0;
	}

}

