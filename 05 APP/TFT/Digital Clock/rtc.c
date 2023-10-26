/*********************************************************************
* File Name    	: 	main.c                                 			 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	20/9/2023                                        *
* Description   : 	TFT Digital CLock				  	             *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"


#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "MCAL/MSPI/MSPI_interface.h"

#include "HAL/HTFT/HTFT_interface.h"

/* SPI Configurations struct */
SPI_config_t SPI1Configuration =
{
	.Copy_uddtSPINumber	   = SPI1,
	.Copy_uddtMasterSlave  = MASTER,
	.Copy_uddtBaudeRate	   = F_CPU_DIV_BY_2,
	.Copy_uddtFrameFormat  = MSB_FIRST,
	.Copy_uddtDataSize     = _8_BIT_DATA,
	.Copy_uddtClockPhase   = SECOND_EDGE_CAPTURE,
	.Copy_uddtClockPolarity= IDLE_ONE,
	.Copy_uddtSSManagement = SW_SLAVE_MANAGEMENT
};

/* Enum to store week day */
typedef enum
{
	SAT,SUN,MON,TUE,WED,THU,FRI
}Days_t;
/* Array of strings for week days used to display on TFT */
char DayString[7][10]={"Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday"};
/* Array of characters for day time(AM,PM) */
char DayTime[2] = {'A','P'};

/* Set date and time by initializing these variables*/
char Date[]={"24/9/2023"}; /* Set date */
u8 G_u8Seconds=45;		/* Seconds */
u8 G_u8Minutes=59;		/* Minutes */
u8 G_u8Hours=11;		/* Hours */
Days_t G_uddtDay=SUN;	/* Day */
u8 G_u8PmFlag=1;		/* 0 for AM, 1 for PM */
/* Systick call back function to update time every 1s */
void RTC_voidTimeUpdate(void);
/* Function to update display on TFT */
void RTC_voidTFTDiplay(void);

int main(void)
{

	/* Initialize RCC with AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);
	/* Enable RCC for GPIOB */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOB);
	/* Enable RCC for SPI1 */
	MRCC_voidEnablePeripheral(RCC_APB2, RCC_SPI1);

	/* Initialize STK with frequency equals AHB/8 or SYS_CLK/16 = 1MHz */
	MSTK_voidInit(STK_AHB_Div_BY_8);
	/* Initialize SPI for TFT serial communication */
	MSPI_voidInit(&SPI1Configuration);
	/* Initialize TFT */
	HTFT_voidInit();
	/* Fill TFT with blue */
	HTFT_voidFillRectangle(0, 127, 0, 159, BLUE);
	/* Display header string on TFT */
	HTFT_voidWriteString(35, 10, "RTC", Font_16x26, CYAN, BLUE);
	/* Display initialized hours */
	HTFT_voidWriteChar(15, 50, (G_u8Hours/10)+'0', Font_11x18, CYAN, BLUE);
	HTFT_voidWriteChar(26, 50, (G_u8Hours%10)+'0', Font_11x18, CYAN, BLUE);
	HTFT_voidWriteChar(37, 50, ':', Font_11x18, CYAN, BLUE);
	/* Display initialized minutes */
	HTFT_voidWriteChar(48, 50, (G_u8Minutes/10)+'0', Font_11x18, CYAN, BLUE);
	HTFT_voidWriteChar(59, 50, (G_u8Minutes%10)+'0', Font_11x18, CYAN, BLUE);
	HTFT_voidWriteChar(70, 50, ':', Font_11x18, CYAN, BLUE);
	/* Display initialized seconds */
	HTFT_voidWriteChar(81, 50, (G_u8Seconds/10)+'0', Font_11x18, CYAN, BLUE);
	HTFT_voidWriteChar(92, 50, (G_u8Seconds%10)+'0', Font_11x18, CYAN, BLUE);
	/* Display initialized day time (AM or PM) */
	HTFT_voidWriteChar(103, 50, DayTime[G_u8PmFlag], Font_11x18, CYAN, BLUE);
	HTFT_voidWriteChar(114, 50, 'M', Font_11x18, CYAN, BLUE);
	/* Display initialized day and date */
	HTFT_voidWriteString(20, 80, DayString[G_uddtDay], Font_11x18, CYAN, BLUE);
	HTFT_voidWriteString(20, 110, Date, Font_11x18, CYAN, BLUE);

	/* Start systick with call back function every 1s (tickTime = 1us)*/
	MSTK_voidSetIntervalPeriodic(1000000, RTC_voidTimeUpdate);

	while(1)
	{

	}
}

void RTC_voidTimeUpdate(void)
{
	/* Increment seconds */
	G_u8Seconds++;
	/* Display on TFT */
	RTC_voidTFTDiplay();
}

void RTC_voidTFTDiplay(void)
{
	/* Check that seconds didn't reach 60 */
	if (G_u8Seconds!=60)
	{
		/* Display updated seconds */
		HTFT_voidWriteChar(81, 50, (G_u8Seconds/10)+'0', Font_11x18, CYAN, BLUE);
		HTFT_voidWriteChar(92, 50, (G_u8Seconds%10)+'0', Font_11x18, CYAN, BLUE);
	}
	else
	{
		/* In case seconds reached 60 reset them and increment minutes */
		G_u8Seconds=0;
		/* Display 00 seconds */
		HTFT_voidWriteChar(81, 50, '0', Font_11x18, CYAN, BLUE);
		HTFT_voidWriteChar(92, 50, '0', Font_11x18, CYAN, BLUE);
		/* Increment minutes */
		G_u8Minutes++;
		/* Check that seconds didn't reach 60 */
		if(G_u8Minutes!=60)
		{
			/* Display updated minutes */
			HTFT_voidWriteChar(48, 50, (G_u8Minutes/10)+'0', Font_11x18, CYAN, BLUE);
			HTFT_voidWriteChar(59, 50, (G_u8Minutes%10)+'0', Font_11x18, CYAN, BLUE);
		}

		else
		{
			/* In case minutes reached 60 reset them and increment hours */
			G_u8Minutes=0;
			/* Display 00 minutes */
			HTFT_voidWriteChar(48, 50, '0', Font_11x18, CYAN, BLUE);
			HTFT_voidWriteChar(59, 50, '0', Font_11x18, CYAN, BLUE);
			/* Increment hours */
			G_u8Hours++;
			/* Check that seconds didn't reach 12 */
			if(G_u8Hours!=12)
			{
				/* In case the clock in initialized by 12PM (13 after increment )
				 * get modulus to turn hours from 12PM to 1PM */
				G_u8Hours /=12;
				/* Display updated hours */
				HTFT_voidWriteChar(15, 50, (G_u8Hours/10)+'0', Font_11x18, CYAN, BLUE);
				HTFT_voidWriteChar(26, 50, (G_u8Hours%10)+'0', Font_11x18, CYAN, BLUE);
			}
			/* In case minutes hours 12, check for AM,PM flag */
			else if(G_u8PmFlag==0)
			{
				/* The time was 11:59:59AM so it should be 12PM */
				HTFT_voidWriteChar(26, 50, '2', Font_11x18, CYAN, BLUE);
				HTFT_voidWriteChar(103, 50, 'P', Font_11x18, CYAN, BLUE);
				/* Reset hours */
				G_u8Hours=0;
				/* Now PM flag is 1 */
				G_u8PmFlag=1;

			}
			else if(G_u8PmFlag==1)
			{
				/* The time was 11:59:59PM so it should be 00AM */
				HTFT_voidWriteChar(15, 50, '0', Font_11x18, CYAN, BLUE);
				HTFT_voidWriteChar(26, 50, '0', Font_11x18, CYAN, BLUE);
				HTFT_voidWriteChar(103, 50, 'A', Font_11x18, CYAN, BLUE);
				/* Reset hours */
				G_u8Hours=0;
				/* Now Flag = AM */
				G_u8PmFlag=1;
				/* Increment one day */
				G_uddtDay++;
				/* Check for days boundary */
				if(G_uddtDay>FRI)
				{
					G_uddtDay=SAT;
				}
				/* Display updated day and date */
				HTFT_voidWriteString(20, 80, DayString[G_uddtDay], Font_11x18, CYAN, BLUE);
				HTFT_voidWriteChar(31, 110, '5', Font_11x18, CYAN, BLUE);


			}

		}
	}




}
