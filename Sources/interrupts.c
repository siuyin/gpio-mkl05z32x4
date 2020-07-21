/*
 * interrupts.c
 *
 *  Created on: 21 Jul, 2020
 *      Author: siuyin
 */

volatile unsigned int tick;
void sysTickISR(void) {
	tick++;
}

