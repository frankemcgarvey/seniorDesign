/*
 * localization.c
 *
 *  Created on: Jul 27, 2021
 *      Author: Chris
 */

#include "localization.h"



void Create_Arcsine_Table(float *arcsinTable){
	for(uint32_t i = 0; i < 2*ARCSIN_INDEX+1; i++){
		arcsinTable[i] = (float)( asin((((double)i-(double)ARCSIN_INDEX) / 48000.0l) * 340.0l / 0.5l) * 180.0l/acos(-1) );
	}
}


void Localize_1D(float *sig_i, float *sig_j){

	static corr[];

	for(uint32_t i = 0; i < ; i++){
		arm
	}

}
