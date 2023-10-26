/*********************************************************************
* File Name    	: 	HSTP_interface.h                                 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	25/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/

#ifndef HSTP_INTERFACE_H_
#define HSTP_INTERFACE_H_

void STP_VidInit           ( void            );
void STP_VidByteOutput     ( u8  Copy_u8Data );
void STP_VidHalfWordOutput ( u16 Copy_u8Data );

#endif /* S_T_P_INTERFACE_H_ */
