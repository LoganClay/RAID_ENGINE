#pragma once
#include "KeyboardIn.h"
#include <ioStream>

class KeyboardOut
{

private:
	bool lastFrameKeys[104];
	bool lastFrameButton[5];
public:

	KeyboardOut();
	int TakeInput(bool key, int keyNum);
	int TakeBInput(bool key, int keyNum);
	int TakeScrollInput(int scroll);
	bool checkPressed(bool key, int keyNum);
	bool checkPress(bool key, int keyNum);
	bool checkReleased(bool key, int keyNum);
	bool checkRelease(bool key, int keyNum);
	bool checkBPressed(bool key, int keyNum);
	bool checkBPress(bool key, int keyNum);
	bool checkBReleased(bool key, int keyNum);
	bool checkBRelease(bool key, int keyNum);
	void updateLastKey(bool keys[]);
	void updateLastButton(bool keys[]);
};