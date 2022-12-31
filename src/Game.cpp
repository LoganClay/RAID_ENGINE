#include <iostream>
#include "Sound.h"
#include "Controls.h"
#include "GameEngine.h"
#include "GameObject.h"

using namespace std;

// We use macros here so if we ever need to change 
// the defaults, they're in an obvious location!
#define WIDTH 1920
#define HEIGHT 1080
#define TITLE "GameEngine"

int main() {
	// Create Engine object
	GameEngine* engine = new GameEngine();
	
	Controls * controls = engine->controls;
	ObjectList * objects = engine->objects;
	Render * render = engine->render;

	// Play the menu theme song
	// This took me a while to debug -- when you're
	// sourcing files, mamke sure to do it from the
	// perspective of where the "run" file will end up
	Song * title = new Song("aud/menu_theme.wav");
	title->play();

	// Load first menu
	objects->addObject(new Background(render));
	cout << "Got to mark 2\n";
	CloseButton * temp = new CloseButton(render);
	cout << "Got to mark 3\n";
	objects->addObject(temp);
	cout << "Got to mark 4\n";
	controls->addControl(new CloseTrigger(temp));
	cout << "Got to mark 5\n";

	// Start the game
	engine->start(WIDTH, HEIGHT, TITLE);
}
