#pragma once
#include "Render.h"
#include "GameObject.h"
using namespace std;
using namespace sf;
class GameEngine{
public:
	
	shared_ptr<KeyboardIn> keyboardIn;
	shared_ptr<KeyboardOut> keyboardOut;
	bool showFPS;
	bool pause;

	shared_ptr<Render> render;
	shared_ptr<Controls> controls;
	shared_ptr<ObjectList> objects;
	RenderWindow window;

	void start();
};
