/*********************************************************************
* File Name    	: 	HESP_program.c                                   *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	25/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "MCAL/MUSART/MUSART_interface.h"

#include "HAL/HESP/HESP_private.h"
#include "HAL/HESP/HESP_config.h"
#include "HAL/HESP/HESP_interface.h"


u8 volatile DataCome[200] ;
u8 volatile Iterator = 0  ;

void HESP_voidInit(void)
{
	u8 Local_u8Result = 0;

	while(Local_u8Result == 0)
	{
		/* Stop ECHO */
		MUSART_voidSendStringBlocking("ATE0\r\n");
		Local_u8Result = HESP_u8ValidateCmd();
	}

	Local_u8Result = 0;

	while(Local_u8Result == 0)
	{
		/* Set station mode */
		MUSART_voidSendStringBlocking("AT+CWMODE=1\r\n");
		Local_u8Result = HESP_u8ValidateCmd();
	}
}

void HESP_voidConnectToWifi(char* ssid, char* password)
{
	MUSART_voidSendStringBlocking("AT+CWJAP=\"");
	MUSART_voidSendStringBlocking(ssid);
	MUSART_voidSendStringBlocking("\",\"");
	MUSART_voidSendStringBlocking(password);
	MUSART_voidSendStringBlocking("\"\r\n");
	MSTK_voidSetBusyWait(8000000);

}

void HESP_voidConnectToServer(char* ServerIp, char* PortNumber)
{
	MUSART_voidSendStringBlocking("AT+CIPSTART=\"TCP\",\"");
	MUSART_voidSendStringBlocking(ServerIp);
	MUSART_voidSendStringBlocking("\",");
	MUSART_voidSendStringBlocking(PortNumber);
	MUSART_voidSendStringBlocking("\r\n");
	MSTK_voidSetBusyWait(2000000);


}


u8 HESP_u8ReceiveHTTPRequest(char* url, char* length)
{
	u8 Local_u8Response[100] = {0};
	u8 i = 0;
	u8 Dummy = 0;
	u8 Result = 0;
	MUSART_voidSendStringBlocking("AT+CIPSEND=");
	MUSART_voidSendStringBlocking(length);
	MUSART_voidSendStringBlocking("\r\n");
	MSTK_voidSetBusyWait(4000000);
	MUSART_voidSendStringBlocking("GET http://");
	MUSART_voidSendStringBlocking(url);
	MUSART_voidSendStringBlocking("\r\n");
	while (Dummy != 255)
	{
		Dummy = MUSART_u8ReceiveBlocking();
		Local_u8Response[i] = Dummy;
		i++;
	}
	
	return  Local_u8Response[82] ;

}

static u8 HESP_u8ValidateCmd(void)
{
	u8 Local_u8Response[100] = {0};
	u8 i = 0;
	u8 Dummy = 0;
	u8 Result = 0;

	while (Dummy != 255)
	{
		Dummy = MUSART_u8ReceiveBlocking();
		Local_u8Response[i] = Dummy;
		i++;
	}

	/* Check if Ok */
	if (Local_u8Response[0] == 'O' && Local_u8Response[1] == 'K')
	{
		Result = 1;
	}

	return Result;


}
