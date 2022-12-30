#include <SFML/Window/Event.hpp>
#include "KeyboardIn.h"
#include <iostream>

void KeyboardIn::checkInput(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed) this->keyList[e.key.code] = true;
	else if (e.type == sf::Event::KeyReleased) this->keyList[e.key.code] = false;

	if (e.type == sf::Event::MouseButtonPressed) this->buttonList[e.mouseButton.button] = true;
	else if (e.type == sf::Event::MouseButtonReleased) this->buttonList[e.mouseButton.button] = false;

	if (e.type == sf::Event::MouseWheelScrolled) mouseWheel = e.mouseWheelScroll.delta;

}

bool KeyboardIn::getKeyListAt(int i) { return this->keyList[i]; }
bool KeyboardIn::getButtonListAt(int i) { return this->buttonList[i]; }
void KeyboardIn::setMouse(int x, int y) {
	*mouseXPos = x;
	*mouseYPos = y;
}

KeyboardIn::KeyboardIn() {
	for (int i = 0; i < sizeof(this->keyList); i++) this->keyList[i] = false;
	for (int i = 0; i < sizeof(this->buttonList); i++) this->buttonList[i] = false;
	mouseWheel = 0;
	mouseXPos = shared_ptr<int>(new int (0));
	mouseYPos = shared_ptr<int>(new int (0));
	mouse = new Hitbox(mouseXPos,mouseYPos, shared_ptr<int>(new int (1)), shared_ptr<int>(new int (1)));
}
