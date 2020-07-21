/*
 * interrupts.c
 *
 *  Created on: 21 Jul, 2020
 *      Author: siuyin
 */

#include "interrupts.h"

void sysTickISR(void) {
	tick++;
}

