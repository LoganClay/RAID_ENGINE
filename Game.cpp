#pragma once
#include "Controls.cpp"
#include <thread>
#include "Sound.h"

using namespace std;

int main() {
	//Create Engine object
	GameEngine* engine = new GameEngine();
	
	shared_ptr<Controls> controls = engine->controls;
	shared_ptr<ObjectList> objects = engine->objects;
	shared_ptr<Render> render = engine->render;
	Song* title;
	//load first menu
	objects->addObject(shared_ptr<Background>(new Background(render)));
	shared_ptr<CloseButton> temp = shared_ptr<CloseButton>(new CloseButton(render));
	objects->addObject(temp);
	controls->addControl(shared_ptr<CloseTrigger>(new CloseTrigger(temp)));
	title=new Song("Music\\menuTheme.wav", 25.0f);


	//start the game
	engine->start();
}
