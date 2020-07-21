/*
 * button.h
 *
 *  Created on: 21 Jul, 2020
 *      Author: siuyin
 */

#ifndef SOURCES_BUTTON_H_
#define SOURCES_BUTTON_H_

// ButtonStateT is a button state type with states bsReleased, bsPushed etc.
enum ButtonStateT {
	bsReleased, bsMaybeReleased, bsPushed
};

// ButtonState reflects the state of the button, eg. bsPushed, bsReleased etc.
enum ButtonStateT ButtonState;

void SenseButtonTask(void);

#endif /* SOURCES_BUTTON_H_ */
