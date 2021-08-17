/*
 * helper.c
 *
 *  Created on: Aug 14, 2021
 *      Author: Chris
 */


#include "helper.h"
#include "stm32h7xx_hal.h"


void Clean(uint32_t *buffer, uint32_t byte){
	SCB_CleanDCache_by_Addr((uint32_t*)&buffer[0], byte);
}

