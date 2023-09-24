/*********************************************************************
* File Name    	: 	MUSART_interface.h                             	 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	19/9/2023                                        *
* Description   : 			         				                 *
**********************************************************************/
#ifndef MUSART_INTERFACE_H_
#define MUSART_INTERFACE_H_


typedef enum
{
	USART1,
	USART2,
	USART3
}USART_Number_t;

typedef enum
{
	SAMPLING_BY_16,
	SAMPLING_BY_8
}USART_Sampling_t;

typedef enum
{
	BUAD_RATE_1200_bps = 1200,
	BUAD_RATE_2400_bps = 2400,
	BUAD_RATE_9600_bps = 9600,
	BUAD_RATE_19200_bps = 19200,
	BUAD_RATE_38400_bps = 38400,
	BUAD_RATE_57600_bps = 57600,
	BUAD_RATE_115200_bps = 115200,
	BUAD_RATE_230400_bps = 230400,
	BUAD_RATE_460800_bps = 460800,
	BUAD_RATE_921600_bps = 921600,
	BUAD_RATE_1792000_bps = 1792000,
	BUAD_RATE_1843200_bps = 1843200,
	BUAD_RATE_3584000_bps = 3584000,
	BUAD_RATE_3686400_bps = 3686400,
	BUAD_RATE_7168000_bps = 7168000,
	BUAD_RATE_7372800_bps = 7372800,
	BUAD_RATE_9000000_bps = 9000000,
	BUAD_RATE_10500000_bps = 10500000,

}USART_BaudRate_t;


typedef enum
{
	DATA_SIZE_8_BITS,
	DATA_SIZE_9_BITS
}USART_DataSize_t;

typedef enum
{
	PARITY_DISABLED,
	EVEN_PARITY,
	ODD_PARITY
}USART_Parity_t;

typedef enum
{
	ONE_STOP_BIT,
	HALF_STOP_BIT,
	TWO_STOP_BITS
}USART_StopBits_t;




typedef struct
{
	USART_Number_t		Copy_uddtUsartNumber;
	USART_Sampling_t	Copy_uddtSampling;
	USART_BaudRate_t	Copy_uddtBuadRate;
	USART_DataSize_t 	Copy_uddtDataSize;
	USART_Parity_t      Copy_uddtParity;
	USART_StopBits_t	Copy_uddtStopBits;

}USART_cfg_t;


typedef enum
{
	TRANSMIT_DISABLED,
	RECEIVE_DISABLED,
	TRANSMIT_RECEIVE_DISABLE
}USART_Disable_t;

typedef enum
{
	TRANSMIT_ENABLED,
	RECEIVE_ENABLED,
	TRANSMIT_RECEIVE_ENABLED
}USART_Enable_t;

void MUSART_voidInit(USART_cfg_t const *PS_uddtUsartCfg);
 
void MUSART_voidEnable(USART_Number_t Copy_uddtUsartNumber, USART_Enable_t Copy_uddtUsartEnable);
 
void MUSART_voidDisable(USART_Number_t Copy_uddtUsartNumber, USART_Disable_t Copy_uddtUsartDisable);
 
void MUSART_voidSend(u8 Copy_u8Data);
 
u8   MUSART_u8Receive(void);
 
void MUSART_voidSendBlocking(u8 Copy_u8Data);

u8   MUSART_u8ReceiveBlocking(void);


#endif 
