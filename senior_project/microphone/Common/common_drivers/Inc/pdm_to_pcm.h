/*
 * pdm_to_pcm.h
 *
 *  Created on: Jun 14, 2021
 *      Author: frank
 */

#ifndef COMMON_DRIVERS_INC_PDM_TO_PCM_H_
#define COMMON_DRIVERS_INC_PDM_TO_PCM_H_

#include "main.h"
#include "../../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc/pdm2pcm_glo.h"
#include "arm_math.h"
#include "definition.h"

typedef struct{
	ALIGN_32BYTES(uint16_t pdmBuffer[BUFFER_SIZE]);
	ALIGN_32BYTES(uint16_t pcmBuffer[2*CHANNEL_NUMBER][PCM_CHUNK_SIZE]);
	ALIGN_32BYTES(float    pcmBuffer_flt[2*CHANNEL_NUMBER][PCM_CHUNK_SIZE]);
}buffer_t;

void pdm_to_pcm(PDM_Filter_Handler_t* PDM_FilterHandler, uint8_t *pdm, uint16_t (*pcm)[PCM_CHUNK_SIZE]);
void pdm_to_pcm_init(PDM_Filter_Handler_t* PDM_FilterHandler, PDM_Filter_Config_t* PDM_FilterConfig);

#endif /* COMMON_DRIVERS_INC_PDM_TO_PCM_H_ */
