/*********************************************************************
* File Name    	: 	main.c                                 			 *
* Author       	: 	Mahmoud Gamal                                    *
* Version      	: 	1.0.0                                            *
* Date  		: 	18/9/2023                                        *
* Description   : 	DMA test							             *
**********************************************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"


#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MDMA/MDMA_interface.h"
#include "MCAL/MNVIC/MNVIC_interface.h"
#include "HAL/HLED/HLED_interface.h"

void DMA_voidTransferCompleteCallBackFun(void);

int main(void)
{

	/* Initialize RCC with AHB frequency equals SYS_CLK/2 */
	MRCC_voidInit();
	/* Enable RCC for GPIOA */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_GPIOA);
	/* Enable RCC for DMA2 */
	MRCC_voidEnablePeripheral(RCC_AHB1, RCC_DMA2);

	/* Initialize LED at PA0 */
	HLED_voidInit(GPIOA, GPIO_PIN0);
	/* LED is off at the beginning */
	HLED_voidWrite(GPIOA, GPIO_PIN0, LED_OFF);

	/* Set NVIC grouping as 16 groups and no subgroups */
	MNVIC_voidSetGroupingMode(GRB_16_SUB_00);
	/* Set interrupt priority for DMA2 stream0 */
	MNVIC_voidSetIntPriority(NVIC_DMA2_Stream0, GRB_16_SUB_00, 1, 1);
	/* Enable interrupt for DMA2 stream0 */
	MNVIC_voidEnablePerInt(NVIC_DMA2_Stream0);

	/* Source array to copy from using DMA */
	u32 arr1[10]= {1,2,3,4,5,6,7,8,9,10};
	/* Destination array */
	u32 arr2[10];
	/* Initialize DMA2 stream0 to copy array elements to another array (MEM2MEM) */
	MDMA_voidInit(DMA_STREAM0, DMA_CHANNEL0, DMA_MEM2MEM,DMA_CIRCULAR_EN,
			DMA_MEM_INC_EN, DMA_PER_INC_EN, DMA_FOUR_BYTES, DMA_FOUR_BYTES, DMA_VERY_HIGH);
	/* Set source and destination addresses with length of 10 elements */
	MDMA_voidSetAddress(DMA_STREAM0, arr1, arr2, 10);
	/* Set call back function for DMA2 stream0 interrupt */
	MDMA_voidSetCallBack(DMA_STREAM0, DMA_voidTransferCompleteCallBackFun);
	/* Enable transfer complete interrupt for DMA2 stream0 */
	MDMA_voidInerruptEnable(DMA_STREAM0, DMA_TRANSFER_COMPLETE);
	/* Enable DMA2 stream0 */
	MDMA_voidStreamEnable(DMA_STREAM0);

	while(1)
	{


	}
}
 void DMA_voidTransferCompleteCallBackFun(void)
{
	 /* LED on when DMA transfer is complete */
	 HLED_voidWrite(GPIOA, GPIO_PIN0, LED_ON);
}


