/*********************************************************************
* File Name    	: 	HESP_interface.h                                 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	25/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/

#ifndef HESP_INTERFACE_H_
#define HESP_INTERFACE_H_

void HESP_voidInit(void) ;
void HESP_voidConnectToWifi(char* ssid, char* password);
void HESP_voidConnectToServer(char* ServerIp, char* PortNumber);
u8 HESP_u8ReceiveHTTPRequest(char* url, char* length);



#endif /* ESP8266_INTERFACE_H_ */
