#pragma once
#include "Render.h"
#include "GameObject.h"
#include "KeyboardIn.h"
#include "KeyboardOut.h"
#include "Controls.h"

class GameEngine {
	public:
		KeyboardIn * keyboardIn;
		KeyboardOut * keyboardOut;
		Render * render;
		Controls * controls;
		ObjectList * objects;

		RenderWindow window;

		bool showFPS = false;
		bool pause = false;

		GameEngine();
		void start(int w, int h, string t);
};
