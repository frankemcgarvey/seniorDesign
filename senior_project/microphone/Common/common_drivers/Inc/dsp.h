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


typedef struct{
	arm_fir_instance_f32  Filter_inst;
	float state[TAPS + BLOCK_SIZE - 1];
}dsp_buffer_t;

void FIR_Filter(dsp_buffer_t* dsp, float (*input)[BLOCK_SIZE], float (*output)[BLOCK_SIZE]);
void FIR_Filter_Init(dsp_buffer_t* buff, float *coeff);
void Q15_To_Float(q15_t (*q15)[BLOCK_SIZE], float (*flt)[BLOCK_SIZE]);
void Float_To_Q15(float (*flt)[BLOCK_SIZE], q15_t (*q15)[BLOCK_SIZE]);
#endif /* COMMON_DRIVERS_INC_DSP_H_ */
