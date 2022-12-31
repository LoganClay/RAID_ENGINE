#include "Controls.cpp"
#include "Sound.h"

class Scene {
public:
	Controls * controls;
	ObjectList * objects;
	Render * render;

	virtual void load() = 0;
	virtual void unload() = 0;
};
