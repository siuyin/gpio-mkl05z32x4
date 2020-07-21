/*
 * button.c
 *
 *  Created on: 21 Jul, 2020
 *      Author: siuyin
 */
#include "Cpu.h"
#include "Events.h"
#include "PTB.h"
#include "SysTick.h"

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "button.h"
#include "interrupts.h"
#include "GPIO_PDD.h"
#include <stdbool.h>

bool buttonPushed(void) {
	if (GPIO_PDD_GetPortDataInput(GPIOB_BASE_PTR) & GPIO_PDD_PIN_0) {
		return false;
	}
	return true;
}

// SenseButtonTask senses button pushes and updates global variable ButtonState.
void SenseButtonTask(void) {
	static unsigned int nrt;	// next run tick

	if (tick != nrt) {
		return;
	}
	nrt = tick + 20;	// next run in x ticks

	switch (ButtonState) {
	case bsReleased:
		if (buttonPushed()) {
			ButtonState = bsPushed;
		} else {
			ButtonState = bsReleased;
		}
		break;
	case bsPushed:
		if (buttonPushed()) {
			ButtonState = bsPushed;
		} else {
			ButtonState = bsMaybeReleased;
		}
	case bsMaybeReleased:
		if (buttonPushed()) {
			ButtonState = bsPushed;
		} else {
			ButtonState = bsReleased;
		}
	}
}




