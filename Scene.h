#include "Controls.cpp"
#include "Sound.h"

class Scene {
public:
	shared_ptr<Controls> controls;
	shared_ptr<ObjectList> objects;
	shared_ptr<Render> render;

	virtual void load() = 0;
	virtual void unload() = 0;
};