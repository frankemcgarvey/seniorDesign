/*
 * dsp.c
 *
 *  Created on: Jul 3, 2021
 *      Author: Chris
 */

#include "dsp.h"


void FIR_Filter_Init(dsp_buffer_t* buff, float *coeff){
	for(uint32_t i = 0; i < CHANNEL_NUMBER; i++){
		arm_fir_init_f32(&buff[i].Filter_inst, TAPS, &coeff[0], buff[i].state, BLOCK_SIZE);
	}
}

void FIR_Filter(dsp_buffer_t* dsp, float (*input)[BLOCK_SIZE], float (*output)[BLOCK_SIZE]){
	for(uint32_t i = 0; i < CHANNEL_NUMBER; i++){
		arm_fir_f32(&dsp[i].Filter_inst, &input[i][0], &output[i][0], BLOCK_SIZE);
	}
}

void FFT_Init(arm_rfft_fast_instance_f32* fft_instance){
	for(uint32_t i = 0; i < CHANNEL_NUMBER; i++){
		arm_rfft_fast_init_f32(&fft_instance[i], FFT_LEN);
	}
}

void Q15_To_Float(q15_t (*q15)[BLOCK_SIZE], float (*flt)[BLOCK_SIZE]){
	for(uint32_t i = 0; i < CHANNEL_NUMBER; i++){
		arm_q15_to_float(&q15[i][0], &flt[i][0], BLOCK_SIZE);
	}
}

void Float_To_Q15(float (*flt)[BLOCK_SIZE], q15_t (*q15)[BLOCK_SIZE]){
	for(uint32_t i = 0; i < CHANNEL_NUMBER; i++){
		arm_float_to_q15(&flt[i][0], &q15[i][0], BLOCK_SIZE);
	}
}
#define FALSE 				0
#define fft_conjugate_j 	fft_output_j
#define fft_absolute_i_j	fft_output_i

void GCC_PHAT(arm_rfft_fast_instance_f32* fft_instance_i, float *fft_input_i, arm_rfft_fast_instance_f32* fft_instance_j, float *fft_input_j, float* Gphat_output){

	static float fft_output_i[FFT_LEN+2];
	static float fft_output_j[FFT_LEN+2];
	static float fft_multi_i_j[FFT_LEN+2];

	//FFT Signals I & J
	arm_rfft_fast_f32(&fft_instance_i[0], &fft_input_i[0], &fft_output_i[0], FALSE);
	arm_rfft_fast_f32(&fft_instance_j[0], &fft_input_j[0], &fft_output_j[0], FALSE);

	//Take the conjugate of signal J
	arm_cmplx_conj_f32(&fft_output_j[2], &fft_conjugate_j[2], FFT_LEN/2 - 1);

	//Re-assign the values for J
	fft_conjugate_j[FFT_LEN-2] 	= fft_output_j[1];
	fft_conjugate_j[FFT_LEN-1] 	= 0;
	fft_conjugate_j[1] 			= 0;

	//Re-assign the value for I
	fft_output_i[FFT_LEN-2] 	= fft_output_i[1];
	fft_output_i[FFT_LEN-1] 	= 0;
	fft_output_i[1] 			= 0;

	//Multiply the Top
	arm_cmplx_mult_cmplx_f32(&fft_output_i[0], &fft_conjugate_j[0], &fft_multi_i_j[0], (FFT_LEN+2)/2);

	//Find the bottoms magnitude
	arm_cmplx_mag_f32(&fft_multi_i_j[0], &fft_absolute_i_j[0], (FFT_LEN+2)/2);

	//Take the inverse of each one
	for(uint32_t i = 0; i < (FFT_LEN+2)/2; i++){
		fft_absolute_i_j[i] = 1/fft_absolute_i_j[i];
	}

	//Multiply the top with the bottom
	arm_cmplx_mult_real_f32(&fft_multi_i_j[0], &fft_absolute_i_j[0], &Gphat_output[0], (FFT_LEN+2)/2);
}
