#include <iostream>
#include "Controls.h"
#include "KeyboardOut.h"
#include "GameObject.h"

CloseTrigger::CloseTrigger(shared_ptr<CloseButton> o) {
	button = o;
}

bool CloseTrigger::trigger(shared_ptr<KeyboardIn> mouse, shared_ptr<KeyboardOut> keys) {
	if (mouse->mouse->detect(button->hitbox)) {
		button->SetAnimation(1);
		if (keys->checkBRelease(mouse->getButtonListAt(Mouse::Left), Mouse::Left)) {
			cout << "closing" << endl;
			return true;
		}
		return false;
	}
	button->SetAnimation(0);
	return false;
}

void CloseTrigger::event(GameEngine* g) {
	g->window.close();
}
