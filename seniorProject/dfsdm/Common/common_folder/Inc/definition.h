/*
 * definition.h
 *
 *  Created on: Aug 13, 2021
 *      Author: Chris
 */

#ifndef COMMON_FOLDER_INC_DEFINITION_H_
#define COMMON_FOLDER_INC_DEFINITION_H_

#include "stm32h7xx_hal.h"
#include "arm_math.h"

#define PCM_CHUNK_SIZE 		1024
#define CHANNEL_NUMBER		4

#define STAGES			    35

#define FIR_TAPS 			101
#define IIR_TAPS			5*STAGES

#define UPSAMPLE_SIZE		3
#define UPSAMPLE			12

#define SPLINE_SIZE			(3*(UPSAMPLE_SIZE*UPSAMPLE-1))
#define ARGMAX_RANGE		24
typedef enum{
	NONE,
	HALF,
	FULL,
	READY,
}flag_t;

typedef struct{
	ALIGN_32BYTES(int32_t topLeftChannel[2*PCM_CHUNK_SIZE]);
	ALIGN_32BYTES(int32_t topRightChannel[2*PCM_CHUNK_SIZE]);
	ALIGN_32BYTES(int32_t bottomLeftChannel[2*PCM_CHUNK_SIZE]);
	ALIGN_32BYTES(int32_t bottomRightChannel[2*PCM_CHUNK_SIZE]);

	ALIGN_32BYTES(float pcmBuffer_flt[CHANNEL_NUMBER][PCM_CHUNK_SIZE]);

	ALIGN_32BYTES(q15_t pcmBuffer_q15[2*CHANNEL_NUMBER][PCM_CHUNK_SIZE]);
	ALIGN_32BYTES(q31_t pcmBuffer_q31[2*CHANNEL_NUMBER][PCM_CHUNK_SIZE]);
}buffer_t;

typedef struct{
	arm_fir_instance_f32  Filter_inst;
	float state[FIR_TAPS + PCM_CHUNK_SIZE - 1];
}dsp_buffer_fir_t;

typedef struct{
	arm_biquad_cascade_df2T_instance_f32  Filter_inst;
	float state[2*STAGES];
}dsp_buffer_iir_t;

typedef struct{
	float correlation;
	float sample;
}corr_t;

typedef struct{
	arm_spline_instance_f32 S;
	arm_spline_type splineType;
	float coeff[SPLINE_SIZE];
	float tempBuffer[2*UPSAMPLE*UPSAMPLE_SIZE - 1];
	uint32_t n;
}cubic_spline_t;

#endif /* COMMON_FOLDER_INC_DEFINITION_H_ */
