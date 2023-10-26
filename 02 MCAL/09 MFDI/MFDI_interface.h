/*********************************************************************
* File Name    	: 	MFDI_interface.h                                 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	28/09/2023                                       *
* Description   : 			         				                 *
*********************************************************************/
#ifndef MFDI_INTERFACE_H_
#define MFDI_INTERFACE_H_

#define FLASH_START_ADDRESS   0x08000000
#define FLASH_APP_ADDRESS     0x08004000

void MFDI_voidEraseSector(u8 copy_u8SectorNumber);
void MFDI_voidFlashWrite(u32 copy_u32Address , u16 *copy_u16PtrData , u8 copy_u8DataLength);
void MFDI_voidEraseAppArea(void);

#endif
