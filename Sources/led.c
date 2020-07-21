/*
 * led.c
 *
 *  Created on: 21 Jul, 2020
 *      Author: siuyin
 */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "PTB.h"
#include "SysTick.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "led.h"
#include "interrupts.h"
#include "button.h"
#include <stdbool.h>
#include "GPIO_PDD.h"

// TurnOnAllLEDs turns on the red,green and blue LED on PTB_8,PTB_9 and PTB_10 respectively.
void TurnOnAllLEDs(void) {
	GPIO_PDD_ClearPortDataOutputMask(GPIOB_BASE_PTR,
			GPIO_PDD_PIN_8+GPIO_PDD_PIN_9+GPIO_PDD_PIN_10);
}

void turnOffLEDs(void) {
	GPIO_PDD_SetPortDataOutputMask(GPIOB_BASE_PTR,
			GPIO_PDD_PIN_8+GPIO_PDD_PIN_9+GPIO_PDD_PIN_10);
}
// white, red, yellow, green, cyan, blue, purple, off
enum ledStateT {
	lsW, lsR, lsY, lsG, lsC, lsB, lsP, lsO
};
void turnOnLED(enum ledStateT n) {
	turnOffLEDs();

	switch (n) {
	case lsR:
		GPIO_PDD_ClearPortDataOutputMask(GPIOB_BASE_PTR, GPIO_PDD_PIN_8);
		break;
	case lsY:
		GPIO_PDD_ClearPortDataOutputMask(GPIOB_BASE_PTR,
				GPIO_PDD_PIN_8+GPIO_PDD_PIN_9);
		break;
	case lsG:
		GPIO_PDD_ClearPortDataOutputMask(GPIOB_BASE_PTR, GPIO_PDD_PIN_9);
		break;
	case lsC:
		GPIO_PDD_ClearPortDataOutputMask(GPIOB_BASE_PTR,
				GPIO_PDD_PIN_9+GPIO_PDD_PIN_10);
		break;
	case lsB:
		GPIO_PDD_ClearPortDataOutputMask(GPIOB_BASE_PTR, GPIO_PDD_PIN_10);
		break;
	case lsP:
		GPIO_PDD_ClearPortDataOutputMask(GPIOB_BASE_PTR,
				GPIO_PDD_PIN_10+GPIO_PDD_PIN_8);
		break;
	case lsW:
		TurnOnAllLEDs();
		break;
	case lsO:
		turnOffLEDs();
		break;

	}

}
void toggleLEDs(void) {
	static enum ledStateT state;

	switch (state) {

	case lsW:
		state = lsR;
		turnOnLED(lsR);
		break;
	case lsR:
		state = lsY;
		turnOnLED(lsY);
		break;
	case lsY:
		state = lsG;
		turnOnLED(lsG);
		break;
	case lsG:
		state = lsC;
		turnOnLED(lsC);
		break;
	case lsC:
		state = lsB;
		turnOnLED(lsB);
		break;
	case lsB:
		state = lsP;
		turnOnLED(lsP);
		break;
	case lsP:
		state = lsO;
		turnOnLED(lsO);
		break;
	case lsO:
		state = lsW;
		turnOnLED(lsW);
		break;
	}
}

// UpdateLEDsTask toggles the LEDs to produce a range of colours on each button press.
void UpdateLEDsTask(void) {
	static unsigned int nrt;	// next run tick

	if (tick != nrt) {
		return;
	}
	nrt = tick + 20;	// next run in x ticks

	static bool pressed;
	switch (pressed) {
	case false:
		if (ButtonState == bsPushed) {
			pressed = true;
			toggleLEDs();
		} else {
			pressed = false;
		}
		break;
	case true:
		if (ButtonState == bsPushed) {
			pressed = true;
		} else {
			pressed = false;
		}
		break;
	}
}

