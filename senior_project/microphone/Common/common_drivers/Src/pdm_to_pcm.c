/*
 * pdm_to_pcm.c
 *
 *  Created on: Jun 14, 2021
 *      Author: frank
 */


#include "pdm_to_pcm.h"

void pdm_to_pcm_init(PDM_Filter_Handler_t* PDM_FilterHandler, PDM_Filter_Config_t* PDM_FilterConfig){

	  for(uint32_t index = 0; index < CHANNEL_NUMBER; index++)
	  {
	    /* Init PDM filters */
	    PDM_FilterHandler[index].bit_order  = PDM_FILTER_BIT_ORDER_MSB;
	    PDM_FilterHandler[index].endianness = PDM_FILTER_ENDIANNESS_LE;
	    PDM_FilterHandler[index].high_pass_tap = HIGH_PASS;
	    PDM_FilterHandler[index].out_ptr_channels = 1;
	    PDM_FilterHandler[index].in_ptr_channels  = CHANNEL_NUMBER;
	    PDM_Filter_Init((PDM_Filter_Handler_t *)(&PDM_FilterHandler[index]));

	    /* Configure PDM filters */
	    PDM_FilterConfig[index].output_samples_number = PCM_CHUNK_SIZE;
	    PDM_FilterConfig[index].mic_gain = MIC_GAIN;
	    PDM_FilterConfig[index].decimation_factor = DECIMATION;
	    PDM_Filter_setConfig((PDM_Filter_Handler_t*)&PDM_FilterHandler[index], (PDM_Filter_Config_t*)&PDM_FilterConfig[index]);
	  }
}

void pdm_to_pcm(PDM_Filter_Handler_t* PDM_FilterHandler, uint8_t *pdm, uint16_t (*pcm)[PCM_CHUNK_SIZE]){

	SCB_InvalidateDCache_by_Addr((uint32_t*)&pdm[0], (uint32_t)((float)BUFFER_SIZE*((float)CHANNEL_NUMBER/2.0)));

	for(uint32_t i = 0; i < CHANNEL_NUMBER; i++){
		PDM_Filter(&pdm[i], &pcm[i][0], &PDM_FilterHandler[i]);
	}


}
