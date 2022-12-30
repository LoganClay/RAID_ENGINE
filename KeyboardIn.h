#pragma once
#include <SFML/Window/Event.hpp>
#include "Hitbox.h"

class KeyboardIn
{
private:

public:
	bool keyList[104];
	bool buttonList[5];
	int mouseWheel;
	shared_ptr<int> mouseXPos, mouseYPos;
	Hitbox* mouse;
	void checkInput(sf::Event e);
	KeyboardIn();
	bool getKeyListAt(int i);
	bool getButtonListAt(int i);
	void setMouse(int x, int y);
};