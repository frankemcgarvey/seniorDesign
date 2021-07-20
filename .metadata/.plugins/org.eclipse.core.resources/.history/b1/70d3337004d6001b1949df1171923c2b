/*
 * pdm_to_pcm.h
 *
 *  Created on: Jun 14, 2021
 *      Author: frank
 */

#ifndef COMMON_DRIVERS_INC_PDM_TO_PCM_H_
#define COMMON_DRIVERS_INC_PDM_TO_PCM_H_

#include "pdm2pcm_glo.h"
#include "main.h"


#define BUFFER_SIZE 256
#define PCM_BUFFER_INC 32
typedef struct{
	ALIGN_32BYTES(uint16_t pdmBuffer[BUFFER_SIZE]);
	ALIGN_32BYTES(uint16_t pcmBuffer[BUFFER_SIZE]);
}buffer_t;

PDM_Filter_Handler_t  PDM_FilterHandler[2];
PDM_Filter_Config_t   PDM_FilterConfig[2];

void pdm_to_pcm(PDM_Filter_Handler_t* PDM_FilterHandler, uint8_t *pdm, uint16_t *pcm,  uint32_t channelNumber);
void pdm_to_pcm_init(PDM_Filter_Handler_t* PDM_FilterHandler, PDM_Filter_Config_t* PDM_FilterConfig, uint32_t channelNumber);

#endif /* COMMON_DRIVERS_INC_PDM_TO_PCM_H_ */
