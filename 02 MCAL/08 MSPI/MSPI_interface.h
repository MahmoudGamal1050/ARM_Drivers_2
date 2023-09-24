/*********************************************************************
* File Name    	: 	MSPI_interface.h                                 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	20/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/
#ifndef MSPI_INTERFACE_H
#define MSPI_INTERFACE_H


typedef enum
{
	SPI1,
	SPI2,
	SPI3
}SPI_Number_t;


typedef enum
{
	SLAVE,
	MASTER
}SPI_MasterSlave_t;

typedef enum
{
	F_CPU_DIV_BY_2,
	F_CPU_DIV_BY_4,
	F_CPU_DIV_BY_8,
	F_CPU_DIV_BY_16,
	F_CPU_DIV_BY_32,
	F_CPU_DIV_BY_64,
	F_CPU_DIV_BY_128,
	F_CPU_DIV_BY_256
}SPI_BaudRate_t;

typedef enum
{
	MSB_FIRST,
	LSB_FIRST
}SPI_FrameFormat_t;

typedef enum
{
	_8_BIT_DATA,
	_16_BIT_DATA
}SPI_DataSize_t;
typedef enum
{
	FIRST_EDGE_CAPTURE,
	SECOND_EDGE_CAPTURE
}SPI_ClockPhase_t;

typedef enum
{
	IDLE_ZERO,
	IDLE_ONE
}SPI_ClockPolarity_t;



typedef enum
{
	HW_SLAVE_MANAGEMENT,
	SW_SLAVE_MANAGEMENT=3,
}SPI_SS_Management_t;

typedef struct
{
	SPI_Number_t			Copy_uddtSPINumber;
	SPI_MasterSlave_t		Copy_uddtMasterSlave;
	SPI_BaudRate_t			Copy_uddtBaudeRate;
	SPI_FrameFormat_t		Copy_uddtFrameFormat;
	SPI_DataSize_t			Copy_uddtDataSize;
	SPI_ClockPhase_t		Copy_uddtClockPhase;
	SPI_ClockPolarity_t		Copy_uddtClockPolarity;
	SPI_SS_Management_t		Copy_uddtSSManagement;

}SPI_config_t;
void MSPI_voidInit(SPI_config_t const *PS_uddtSPIConfig);

void MSPI_voidSendReceiveSynch(SPI_Number_t Copy_uddtSPINumber, u8 *Copy_PtrDataToExchange);


#endif
