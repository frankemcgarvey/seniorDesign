/*
 * dsp.h
 *
 *  Created on: Jul 3, 2021
 *      Author: Chris
 */

#ifndef COMMON_DRIVERS_INC_DSP_H_
#define COMMON_DRIVERS_INC_DSP_H_

#include "arm_math.h"
#include "stdint.h"
#include "definition.h"

void FIR_Filter(dsp_buffer_fir_t* dsp, float (*input)[PCM_CHUNK_SIZE], float (*output)[PCM_CHUNK_SIZE]);
void FIR_Filter_Init(dsp_buffer_fir_t* dsp, float *coeff);


void IIR_Filter(dsp_buffer_iir_t* dsp, float (*input)[PCM_CHUNK_SIZE], float (*output)[PCM_CHUNK_SIZE]);
void IIR_Filter_Init(dsp_buffer_iir_t* dsp, float *coeff);

void Normalized_CC(float *sig_i, float *sig_j, float *corr);
void Upsample(float *input, float *output);

#endif /* COMMON_DRIVERS_INC_DSP_H_ */