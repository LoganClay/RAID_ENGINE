#include "KeyboardOut.h"
#include <iostream>

//constructor sets all values of lastFrameKeys to false as a default
KeyboardOut::KeyboardOut() {
	for (int i = 0; i < sizeof(this->lastFrameKeys); i++)this->lastFrameKeys[i] = false;

	for (int i = 0; i < sizeof(this->lastFrameButton); i++)this->lastFrameButton[i] = false;
}

//KeyboardOut() sets lastFrameKeys equal to a given boolean array
void KeyboardOut::updateLastKey(bool keys[]) {
	for (int i = 0; i < sizeof(this->lastFrameKeys); i++)this->lastFrameKeys[i] = keys[i];
}

void KeyboardOut::updateLastButton(bool buttons[]) {
	for (int i = 0; i < sizeof(this->lastFrameButton); i++)this->lastFrameButton[i] = buttons[i];
}



/*
TakeInput()/ TakeBInput() returns int

0 means key was pressed this frame but not last frame
1 means key was pressed this frame and last frame
2 means key was not pressed this frame but was last frame
3 means key was not pressed this frame and it was not pressed last frame

*/
int KeyboardOut::TakeInput(bool key, int keyNum) {
	if (checkPress(key, keyNum)) return 0;
	if (checkPressed(key, keyNum)) return 1;
	if (checkRelease(key, keyNum)) return 2;
	if (checkReleased(key, keyNum)) return 3;
	return -1;
}
int KeyboardOut::TakeBInput(bool key, int keyNum) {
	if (checkBPress(key, keyNum)) return 0;
	if (checkBPressed(key, keyNum)) return 1;
	if (checkBRelease(key, keyNum)) return 2;
	if (checkBReleased(key, keyNum)) return 3;
	return -1;
}
int KeyboardOut::TakeScrollInput(int scroll) {
	if (scroll == 0) return 0;
	else if (scroll > 0) return 1;
	else return -1;
}

bool KeyboardOut::checkBPressed(bool button, int buttonNum) {
	return button && lastFrameButton[buttonNum];
}

bool KeyboardOut::checkBPress(bool button, int buttonNum) {
	return button && !lastFrameButton[buttonNum];
}

bool KeyboardOut::checkBReleased(bool button, int buttonNum) {
	return !button && !lastFrameButton[buttonNum];
}
bool KeyboardOut::checkBRelease(bool button, int buttonNum) {
	return !button && lastFrameButton[buttonNum];
}

bool KeyboardOut::checkPressed(bool key, int keyNum) {
	return key && lastFrameKeys[keyNum];
}

bool KeyboardOut::checkPress(bool key, int keyNum) {
	return key && !lastFrameKeys[keyNum];
}

bool KeyboardOut::checkReleased(bool key, int keyNum) {
	return !key && !lastFrameKeys[keyNum];
}
bool KeyboardOut::checkRelease(bool key, int keyNum) {
	return !key && lastFrameKeys[keyNum];
}
