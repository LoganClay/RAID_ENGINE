#pragma once
#include <SFML/Window/Event.hpp>
#include "Hitbox.h"

class KeyboardIn {
	public:
		bool keyList[104];
		bool buttonList[5];
		int mouseWheel;
		int mouseXPos;
		int mouseYPos;
		Hitbox* mouse;

		KeyboardIn();
		void checkInput(sf::Event e);

		bool getKeyListAt(int i) {
			return this->keyList[i];
		}

		bool getButtonListAt(int i) {
			return this->buttonList[i];
		}

		void setMouse(int x, int y) {
			mouseXPos = x;
			mouseYPos = y;
		}
};
