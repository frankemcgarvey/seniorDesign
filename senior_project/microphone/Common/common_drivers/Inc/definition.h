/*
 * definition.h
 *
 *  Created on: Aug 6, 2021
 *      Author: Chris
 */

#ifndef COMMON_DRIVERS_INC_DEFINITION_H_
#define COMMON_DRIVERS_INC_DEFINITION_H_



//Arcsine Table
#define ARCSIN_INDEX 	20

#define BUFFER_SIZE 	16384
#define PCM_CHUNK_SIZE 	1024
#define CHANNEL_NUMBER	2
#define DECIMATION		PDM_FILTER_DEC_FACTOR_64

#define MIC_GAIN        -6
#define HIGH_PASS       0

#define TAPS 			301
#define BLOCK_SIZE 		PCM_CHUNK_SIZE

#define FFT_LEN			256
#define LOCAL_SIZE		512
#endif /* COMMON_DRIVERS_INC_DEFINITION_H_ */
