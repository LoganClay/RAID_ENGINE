#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "glad/glad.h"
#include "KeyboardIn.h"
#include "KeyboardOut.h"
#include "Render.h"
#include "Controls.h"
#include "GameObject.h"
#include "GameEngine.h"

using namespace std;

// Initialize all the member variables
GameEngine::GameEngine() {
	keyboardIn = new KeyboardIn();
	keyboardOut = new KeyboardOut();
	render = new Render();
	controls = new Controls();
	objects = new ObjectList();
}

// Basically the entire game loop
void GameEngine::start(int width, int height, string title) {
	// Create window + settings
	window.create(VideoMode(width, height), title, Style::Titlebar | Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setActive(true);

	// Load a basic Arial font
	Font arial;
	arial.loadFromFile("fnt/arial.ttf");

	// FPS Text Counter
	int FPS = 60;
	Text fpsText;
	fpsText.setFont(arial);
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(sf::Color::Yellow);
	fpsText.setString("FPS: " + to_string(FPS));

	// Used to calculate the FPS
	sf::Clock clock;
	float timer = 0;
	int fpsCounter = 0;

	// Game loop
	while (window.isOpen()) {
		fpsCounter++;
		sf::Time elapsed = clock.restart();
		timer += elapsed.asSeconds();
		if (timer > 0) {
			FPS = fpsCounter;
			fpsCounter = 0;
			timer = 0;		
		}

		// Event polling
		Event event;
		keyboardOut->updateLastKey(keyboardIn->keyList);
		keyboardOut->updateLastButton(keyboardIn->buttonList);
		keyboardIn->mouseWheel = 0;

		while (window.pollEvent(event)) {
			switch (event.type) {
				case Event::Closed:
					window.close();
					break;
				//Input Handling
				case Event::KeyPressed:
				case Event::KeyReleased:
				case Event::MouseButtonPressed:
				case Event::MouseButtonReleased:
				case Event::MouseWheelScrolled:
					keyboardIn->checkInput(event);
					break;
				case Event::MouseMoved:
					keyboardIn->setMouse(event.mouseMove.x,event.mouseMove.y);
					break;
				case sf::Event::Resized:
					glViewport(0, 0, event.size.width, event.size.height);
					break;
				default:
					break;
			}
		}

		// Doing Controls
		for (int i = 0; i < controls->controlsSize; i++) {
			Control * temp = controls->getIndex(i)->control;

			if (temp->trigger(keyboardIn, keyboardOut)) {
				temp->event(&window);
			}
		}

		// Rendering 
		window.clear();

		for (int i = 0; i < render->getSize(); i++) {
			window.draw(render->getIndex(i)->sprite);
			if (!pause) { render->getIndex(i)->iterate(); }
		}

		// Show FPS on screen
		fpsText.setString("FPS: " + std::to_string(FPS));
		if (showFPS) { window.draw(fpsText); }

		window.display();
	}
}
