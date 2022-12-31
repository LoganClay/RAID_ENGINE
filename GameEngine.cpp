#pragma once
#include "GameEngine.h"

using namespace std;
using namespace sf;





void GameEngine::start() {

	threadPool.start(std::thread::hardware_concurrency());

	int width = 1920, height = 1080;

	bool menuBool = false;
	bool aniChange = false;

	window = new RenderWindow;
	window->create(VideoMode(width, height), "SimmerDownDaddy", Style::Titlebar | Style::Close);
	window->setFramerateLimit(FRAME_LIMIT);
	window->setActive(true);

	float hScale = (float)width / 1920, vScale = (float)height / 1080;

	Font arial;
	arial.loadFromFile("Fonts\\arial.ttf");

	int FPS = 60;
	Text fps;
	fps.setFont(arial);
	fps.setCharacterSize(24);
	fps.setFillColor(sf::Color::Yellow);
	fps.setString("FPS: " + to_string(FPS));

	sf::Clock clock;
	float timer = 0;
	int fpsCounter = 0;

	int spriteInt = 0;
	bool boolKitchen = true;

	while (window->isOpen()) {
		fpsCounter++;
		sf::Time elapsed = clock.restart();
		//std::cout << elapsed.asSeconds() << " time elapsed since last check" << std::endl;
		timer += elapsed.asSeconds();
		if (timer >= 1) {
			//cout << timer << " time elapsed since last check" << endl;
			FPS = fpsCounter;
			fpsCounter = 0;
			timer = 0;
		}



		Event event;
		keyboardOut->updateLastKey(keyboardIn->keyList);
		keyboardOut->updateLastButton(keyboardIn->buttonList);
		keyboardIn->mouseWheel = 0;
		while (window->pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				window->close();
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
				keyboardIn->setMouse(event.mouseMove.x, event.mouseMove.y);
				//std::cout << "Mouse X: " << *keyboardIn.mouseXPos << " Mouse Y: " << *keyboardIn.mouseYPos << std::endl;
				break;
			case sf::Event::Resized:
				glViewport(0, 0, event.size.width, event.size.height);
				break;
			default:
				break;
			}
		}

		//Doing Controls
		controls->triggerAll(keyboardIn, keyboardOut, this);

		//rendering 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window->clear();
		render->renderAll(window);

		fps.setString("FPS: " + std::to_string(FPS));
		if (showFPS)window->draw(fps);

		window->display();
	}
}
