#include <SFML/Window/Event.hpp>
#include "KeyboardIn.h"
#include <iostream>

void KeyboardIn::checkInput(sf::Event e) {
	if (e.type == sf::Event::KeyPressed) {
		this->keyList[e.key.code] = true;
		return;
	}
	else if (e.type == sf::Event::KeyReleased) {
		this->keyList[e.key.code] = false;
		return;
	}

	if (e.type == sf::Event::MouseButtonPressed) {
		this->buttonList[e.mouseButton.button] = true;
		return;
	}
	else if (e.type == sf::Event::MouseButtonReleased) {
		this->buttonList[e.mouseButton.button] = false;
		return;
	}

	if (e.type == sf::Event::MouseWheelScrolled) {
		mouseWheel = e.mouseWheelScroll.delta;
	}
}

KeyboardIn::KeyboardIn() {
	for (int i = 0; i < sizeof(this->keyList); i++) {
		this->keyList[i] = false;
	}

	for (int i = 0; i < sizeof(this->buttonList); i++) {
		this->buttonList[i] = false;
	}

	mouseWheel = 0;
	mouseXPos = (int *)(new int (0));
	mouseYPos = (int *)(new int (0));
	mouse = new Hitbox(mouseXPos, mouseYPos, (int *)(new int (1)), (int *)(new int (1)));
}
