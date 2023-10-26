/*********************************************************************
* File Name    	: 	main.c                                 			 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	19/9/2023                                        *
* Description   : 	Bootloader				  			             *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"


#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "MCAL/MUSART/MUSART_interface.h"
#include "MCAL/MFDI/MFDI_interface.h"

#include <SERVICE/SPARSE_interface.h>

#define   NEW_UPDATE_REQUEST     0x01u
#define   READY_TO_RECEIVE       0x02u
#define   REQUEST_ACCPETED		 0x05u
#define   START_SENDING	         0x07u
#define   RECORD_RECEIVED        0x08u



#define	SCB_VTOR	*((volatile u32 *)(0xE000ED08))

u8 G_u8ReceiveBuffer[100];
u8 G_u8RecordCounter;
u8 G_u8WriteRequest=1;
u8 G_u8TimeOutFlag;
u8 G_u8StartFlag;

typedef void(*APP_Call_t)(void);
APP_Call_t AddressToCall = NULL;

void APP_voidEntryPoint(void)
{
	/* Set the pointer to the end of vector table (startup code of Application) */
	AddressToCall = *(APP_Call_t*)0x08004004;

	/* Call the application (startup code) */
	if((u32)*AddressToCall != 0xFFFFFFFF)
	{
		/* Set vector table offset to the first address in sector 1 */
		SCB_VTOR = FLASH_APP_ADDRESS;
		AddressToCall();
	}


}
int main(void)
{
	/* USART Configuration Struct */
	USART_cfg_t uart =
	{
			.Copy_uddtUsartNumber = USART1,
			.Copy_uddtSampling    = SAMPLING_BY_16,
			.Copy_uddtBuadRate    = BUAD_RATE_9600_bps,
			.Copy_uddtDataSize    = DATA_SIZE_8_BITS,
			.Copy_uddtParity      = PARITY_DISABLED,
			.Copy_uddtStopBits    = ONE_STOP_BIT
	};

	u8 L_u8ReceivedStatus=0,L_u8data;
	/* Initialize RCC with SYS_CLK=16MHz and AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);
	/* Enable RCC for USART1 */
	MRCC_voidEnablePeripheral(RCC_APB2, RCC_USART1);


	/* Set Pin Mode For Pins 9 , 10 -> Alternative Function */
	MGPIO_voidSetPinMode(GPIOA, GPIO_PIN9, GPIO_ALTF);    //TX-> USART1
	MGPIO_voidSetPinMode(GPIOA,GPIO_PIN10,GPIO_ALTF) ;   //RX-> USART1

	/* Set USART1 alternative function (ALTF7) for  For Pins 9 , 10  */
	MGPIO_voidSetAltFun(GPIOA,GPIO_PIN9,GPIO_ALTFN_7) ;                //TX-> USART1
	MGPIO_voidSetAltFun(GPIOA,GPIO_PIN10,GPIO_ALTFN_7) ;               //RX-> USART1

	/* Initialize USART1 */
	MUSART_voidInit(&uart);
	/* Enable USART1 receiver and transmitter */
	MUSART_voidEnableDisable(USART1, TRANSMIT_RECEIVE_ENABLED);


	/* STK frequency = 16MHz/2/8 = 1MHz (tickTime = 1us) */
	MSTK_voidInit(STK_AHB_Div_BY_8);
	/* Wait 15s to receive data through usart or call application */
	MSTK_voidSetIntervalPeriodic(16000000, APP_voidEntryPoint);

	MGPIO_voidSetPinMode(GPIOA, GPIO_PIN0, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(GPIOA, GPIO_PIN1, GPIO_OUTPUT);
	MGPIO_voidSetPinValue(GPIOA, GPIO_PIN0, GPIO_HIGH);
	MGPIO_voidSetPinValue(GPIOA, GPIO_PIN1, GPIO_HIGH);


	while(1)
	{
		while(G_u8StartFlag==0)
		{
			MUSART_voidReceiveBlocking(&L_u8data);
			if(L_u8data==NEW_UPDATE_REQUEST)
			{
				/*Stop Timer Because Application Code In Processing*/
				MSTK_voidStopInterval();
				MUSART_voidSendBlocking(REQUEST_ACCPETED);
				MUSART_voidReceiveBlocking(&L_u8data);
				if(L_u8data==START_SENDING ||L_u8data==NEW_UPDATE_REQUEST)
				{
					MUSART_voidSendBlocking(READY_TO_RECEIVE);
					G_u8StartFlag = 1;
				}
			}
		}

		L_u8ReceivedStatus = MUSART_u8ReceiveNonBlocking(&G_u8ReceiveBuffer[G_u8RecordCounter]);
		if(L_u8ReceivedStatus==1)
		{
			/*indicate The end Of the Record*/
			if(G_u8ReceiveBuffer[G_u8RecordCounter]=='\n')
			{
				if(G_u8WriteRequest==1)
				{
					/*Erase The Application Code*/
					MFDI_voidEraseAppArea();
					G_u8WriteRequest=0;
				}
				/*Parse The Record and Write it to flash*/
				PARSE_voidParseRecord(G_u8ReceiveBuffer);
				/*Send ok to tool to send the next Record */
				MUSART_voidSendBlocking(RECORD_RECEIVED);
				/*Reset Buffer Counter*/
				G_u8RecordCounter=0;

			}

			else
			{
				G_u8RecordCounter++;
			}
		}

		if(G_u8ReceiveBuffer[8]=='1')
		{

			MGPIO_voidSetPinValue(GPIOA, GPIO_PIN0, GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA, GPIO_PIN1, GPIO_LOW);
			MUSART_voidSendBlocking(RECORD_RECEIVED);
			/*Wait 1 sec then jump to Application*/
			APP_voidEntryPoint();


		}
	}
}

