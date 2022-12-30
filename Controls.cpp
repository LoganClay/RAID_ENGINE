#include "GameEngine.cpp"

//Template
/*
class Template : public Control {
	bool trigger(KeyboardIn mouse, KeyboardOut keys) {
		return keys.checkPress(mouse.getKeyListAt(Keyboard::Key), Keyboard::Key);
	}
	void event(GameEngine* g) {
		//do something
	}
};
*/

using namespace sf;
using namespace std;

class CloseTrigger : public Control {

public:

	shared_ptr<CloseButton> button;


	CloseTrigger(shared_ptr<CloseButton> o) {
		button = o;
	}

	bool trigger(shared_ptr<KeyboardIn> mouse, shared_ptr<KeyboardOut> keys) {
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

	void event(GameEngine* g) {
		g->window.close();
	}
};