/*
 * dsp.c
 *
 *  Created on: Jul 3, 2021
 *      Author: Chris
 */

#include "dsp.h"


static const float coeff[TAPS+1] = {0.000000e+00,-8.592732e-05,-3.193261e-04,-6.232598e-04,-8.840666e-04,-9.854609e-04,-8.521635e-04,-4.894706e-04,3.102859e-13,4.383326e-04,6.357459e-04,4.777282e-04,-6.137172e-13,-5.894618e-04,-9.668234e-04,-8.197004e-04,6.015608e-13,1.367077e-03,2.881604e-03,3.999644e-03,4.260699e-03,3.521501e-03,2.084361e-03,6.375122e-04,0.000000e+00,7.562056e-04,2.933325e-03,5.881905e-03,8.451249e-03,9.428289e-03,8.079900e-03,4.564261e-03,-1.523545e-12,-3.893430e-03,-5.487076e-03,-4.001685e-03,2.494134e-12,4.651880e-03,7.417786e-03,6.125483e-03,-1.994844e-12,-9.763350e-03,-2.020926e-02,-2.764194e-02,-2.913081e-02,-2.392262e-02,-1.413737e-02,-4.340795e-03,-3.155686e-18,-5.291800e-03,-2.106097e-02,-4.376907e-02,-6.598798e-02,-7.845736e-02,-7.312953e-02,-4.619562e-02,2.564661e-12,5.693579e-02,1.119381e-01,1.517002e-01,1.661947e-01,1.517002e-01,1.119381e-01,5.693579e-02,2.564661e-12,-4.619562e-02,-7.312953e-02,-7.845736e-02,-6.598798e-02,-4.376907e-02,-2.106097e-02,-5.291800e-03,-3.155686e-18,-4.340795e-03,-1.413737e-02,-2.392262e-02,-2.913081e-02,-2.764194e-02,-2.020926e-02,-9.763350e-03,-1.994844e-12,6.125483e-03,7.417786e-03,4.651880e-03,2.494134e-12,-4.001685e-03,-5.487076e-03,-3.893430e-03,-1.523545e-12,4.564261e-03,8.079900e-03,9.428289e-03,8.451249e-03,5.881905e-03,2.933325e-03,7.562056e-04,0.000000e+00,6.375122e-04,2.084361e-03,3.521501e-03,4.260699e-03,3.999644e-03,2.881604e-03,1.367077e-03,6.015608e-13,-8.197004e-04,-9.668234e-04,-5.894618e-04,-6.137172e-13,4.777282e-04,6.357459e-04,4.383326e-04,3.102859e-13,-4.894706e-04,-8.521635e-04,-9.854609e-04,-8.840666e-04,-6.232598e-04,-3.193261e-04,-8.592732e-05,0.000000e+00};


void matrix_init(uint32_t numRow, uint32_t numCol, uint16_t* matrix, arm_matrix_instance_q15* instance, uint32_t offset){

	for(uint32_t i = 0; i < 2; i++){
		arm_mat_init_q15(&instance[i], numRow, numCol, (q15_t*)&matrix[offset*i]);
	}
}

void FIR_Filter_Init(dsp_buffer_t* buff, uint32_t channelNumber){
	for(uint32_t i = 0; i < channelNumber; i++){
		arm_fir_init_f32(buff[i].lpFilter_inst, TAPS, &coeff[0], buff[i].state, BLOCK_SIZE);
	}
}

void FIR_Filter(dsp_buffer_t* dsp, float (*input)[BLOCK_SIZE], float (*output)[BLOCK_SIZE] , uint32_t channelNumber){
	for(uint32_t i = 0; i < channelNumber; i++){
		arm_fir_f32(dsp[i].lpFilter_inst, &input[i][0], &output[i][0], BLOCK_SIZE);
	}
}

void FFT_Init(arm_rfft_fast_instance_f32* fft_instance, uint32_t channelNumber){
	for(uint32_t i = 0; i < channelNumber; i++){
		arm_rfft_fast_init_f32(&fft_instance[i], FFT_LEN);
	}
}

#define FALSE 0
void GCC_PHAT(arm_rfft_fast_instance_f32* fft_instance0, float *fft_input0, arm_rfft_fast_instance_f32* fft_instance1, float *fft_input1, float* Gphat_output){

	static float fft_output0[FFT_LEN];
	static float fft_output1[FFT_LEN];

	arm_rfft_fast_f32(&fft_instance0[0], &fft_input0[0], &fft_output0[0], FALSE);
	arm_rfft_fast_f32(&fft_instance1[0], &fft_input1[0], &fft_output1[0], FALSE);

	for(uint32_t i = 0; i < FFT_LEN; i++){

	}

}
