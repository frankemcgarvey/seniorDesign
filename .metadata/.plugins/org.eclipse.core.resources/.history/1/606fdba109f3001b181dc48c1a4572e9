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

#define BUFFER_SIZE 	4096
#define PCM_CHUNK_SIZE 	256
#define CHANNEL_NUMBER	2
#define DECIMATION		PDM_FILTER_DEC_FACTOR_64

#define MIC_GAIN        -10
#define HIGH_PASS       0

typedef struct{
	ALIGN_32BYTES(uint16_t pdmBuffer[BUFFER_SIZE]);
	ALIGN_32BYTES(uint16_t pcmBuffer[2*CHANNEL_NUMBER][PCM_CHUNK_SIZE]);
	ALIGN_32BYTES(uint16_t pcmBuffer_Trans[2*PCM_CHUNK_SIZE][CHANNEL_NUMBER]);
	ALIGN_32BYTES(float    pcmBuffer_flt[2*CHANNEL_NUMBER][PCM_CHUNK_SIZE]);
}buffer_t;

void pdm_to_pcm(PDM_Filter_Handler_t* PDM_FilterHandler, uint8_t *pdm, uint16_t (*pcm)[PCM_CHUNK_SIZE],  uint32_t channelNumber);
void pdm_to_pcm_init(PDM_Filter_Handler_t* PDM_FilterHandler, PDM_Filter_Config_t* PDM_FilterConfig, uint32_t channelNumber);

#endif /* COMMON_DRIVERS_INC_PDM_TO_PCM_H_ */
