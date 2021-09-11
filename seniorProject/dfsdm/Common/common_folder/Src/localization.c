/*
 * localization.c
 *
 *  Created on: Jul 27, 2021
 *      Author: Chris
 */

#include "localization.h"



void Create_Arcsine_Table(uint32_t size, float *arcsinTable){
	for(uint32_t i = 0; i < 2*size+1; i++){
		arcsinTable[i] = (float)( asin((((double)i-(double)size) / 48000.0l) * 340.0l / 0.5l) * 180.0l/acos(-1) );
	}
}

bool Localize_1D_TimeDifference(float *sig_i, float *sig_j, uint32_t offset, float MAX, float *arcsinTable, float *angle){

	static uint32_t pos_i, pos_j;
	static float max_i, max_j;
	static int32_t sampleNum;
	static float buffer_i[2*LOCALIZATION_SIZE], buffer_j[2*LOCALIZATION_SIZE];
	static bool state;
	static uint32_t index = 0;

	arm_max_no_idx_f32(sig_i, LOCALIZATION_SIZE, &max_i);
	arm_max_no_idx_f32(sig_j, LOCALIZATION_SIZE, &max_j);

	if( (max_i >= MAX) && (max_j >= MAX)){
			state = true;
	}
	if(state){
			index++;
			if(index == 1){
				arm_copy_f32(&sig_i[0], &buffer_i[0], LOCALIZATION_SIZE);
				arm_copy_f32(&sig_j[0], &buffer_j[0], LOCALIZATION_SIZE);
				return false;
			}
			else{
				index = 0;
				state = false;
				arm_copy_f32(&sig_i[0], &buffer_i[LOCALIZATION_SIZE], LOCALIZATION_SIZE);
				arm_copy_f32(&sig_j[0], &buffer_j[LOCALIZATION_SIZE], LOCALIZATION_SIZE);

				arm_max_f32(&buffer_i[0], 2*LOCALIZATION_SIZE, &max_i, &pos_i);
				arm_max_f32(&buffer_j[0], 2*LOCALIZATION_SIZE, &max_j, &pos_j);

				sampleNum =  (int32_t)pos_i - (int32_t)pos_j;

				if(sampleNum < -1*(int32_t)offset){
					sampleNum = -1*(int32_t)offset;
				}
				else if(sampleNum > (int32_t)offset){
					sampleNum = (int32_t)offset;
				}

				*angle= arcsinTable[sampleNum + (int32_t)offset];

				return true;

			}
	}


	else
		return false;


}

bool Localize_1D_CorrMax(float *sig_i, float *sig_j, uint32_t offset, float MAX, float *arcsinTable, float *angle){

	static float max_i, max_j;
	static int32_t sampleNum;
	static int32_t corr_pos;
	static float dummy;
	static float corr[LOCALIZATION_SIZE];

	arm_max_no_idx_f32(sig_i, LOCALIZATION_SIZE, &max_i);
	arm_max_no_idx_f32(sig_j, LOCALIZATION_SIZE, &max_j);

	if( (max_i >= MAX) && (max_j >= MAX)){
		arm_correlate_f32(sig_i, LOCALIZATION_SIZE, sig_j, LOCALIZATION_SIZE, &corr[0]);
		arm_max_f32(&corr[0], LOCALIZATION_SIZE*2, &dummy, (uint32_t*)&corr_pos);
		sampleNum = corr_pos - (LOCALIZATION_SIZE-1);
		*angle= arcsinTable[sampleNum + (int32_t)offset];
		return true;

	}

	else
		return false;


}

bool Localize_1D_CorrBuffer(float *sig_i, float *sig_j,  uint32_t offset, float MAX, float *arcsinTable, float *angle){

	static float max_i, max_j;
	static int32_t sampleNum;
	static int32_t corr_pos;
	static float dummy;
	static float buffer_i[2*LOCALIZATION_SIZE], buffer_j[2*LOCALIZATION_SIZE];
	static uint32_t index = 0;
	static bool state = false;
	static float corr[4*LOCALIZATION_SIZE];

	arm_max_no_idx_f32(sig_i, LOCALIZATION_SIZE, &max_i);
	arm_max_no_idx_f32(sig_j, LOCALIZATION_SIZE, &max_j);

	if( (max_i >= MAX) && (max_j >= MAX)){
		state = true;
	}

	if(state){
		index++;
		if(index == 1){
			arm_copy_f32(&sig_i[0], &buffer_i[0], LOCALIZATION_SIZE);
			arm_copy_f32(&sig_j[0], &buffer_j[0], LOCALIZATION_SIZE);
			return false;
		}
		else{
			index = 0;
			state = false;
			arm_copy_f32(&sig_i[0], &buffer_i[LOCALIZATION_SIZE], LOCALIZATION_SIZE);
			arm_copy_f32(&sig_j[0], &buffer_j[LOCALIZATION_SIZE], LOCALIZATION_SIZE);

			arm_correlate_f32(&buffer_i[0], 2*LOCALIZATION_SIZE, &buffer_j[0], 2*LOCALIZATION_SIZE, &corr[0]);
			arm_max_f32(&corr[0], 4*LOCALIZATION_SIZE, &dummy, (uint32_t*)&corr_pos);
			sampleNum = corr_pos - (2*LOCALIZATION_SIZE-1);

			if(sampleNum < -1*(int32_t)offset){
				sampleNum = -1*(int32_t)offset;
			}
			else if(sampleNum > (int32_t)offset){
				sampleNum = (int32_t)offset;
			}

			*angle= arcsinTable[sampleNum + (int32_t)offset];

			return true;

		}
	}

	else
		return false;

}