#pragma once
#include "KeyboardIn.h"
#include <iostream>

class KeyboardOut {
	private:
		bool lastFrameKeys[104];
		bool lastFrameButton[5];

	public:

		KeyboardOut();

		void updateLastKey(bool keys[]);
		void updateLastButton(bool keys[]);

		int TakeInput(bool key, int keyNum);
		int TakeBInput(bool key, int keyNum);
		int TakeScrollInput(int scroll);

		bool checkBPressed(bool button, int buttonNum) {
			return button && lastFrameButton[buttonNum];
		}

		bool checkBPress(bool button, int buttonNum) {
			return button && !lastFrameButton[buttonNum];
		}

		bool checkBReleased(bool button, int buttonNum) {
			return !button && !lastFrameButton[buttonNum];
		}
		bool checkBRelease(bool button, int buttonNum) {
			return !button && lastFrameButton[buttonNum];
		}

		bool checkPressed(bool key, int keyNum) {
			return key && lastFrameKeys[keyNum];
		}

		bool checkPress(bool key, int keyNum) {
			return key && !lastFrameKeys[keyNum];
		}

		bool checkReleased(bool key, int keyNum) {
			return !key && !lastFrameKeys[keyNum];
		}
		bool checkRelease(bool key, int keyNum) {
			return !key && lastFrameKeys[keyNum];
		}
};
