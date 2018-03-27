#include "Spaghengine.h"
#include "Initiate.h"
#include <iostream>
#include "TransformComponent.h"

Spaghengine::GameState Spaghengine::_gameState = Spaghengine::Uninitialized;
float Spaghengine::currentTime = 0.0;
float Spaghengine::deltaTime = 0.0;
sf::Clock masterClock;
sf::Clock deltaClock;

void Spaghengine::Initialize(void)
{
	if (_gameState != Uninitialized)
		return;

	bool init = initEngine();
	if (!init) {
		exit;
	}

	sf::Texture texture;

	if (texture.loadFromFile("theThing.png") != true) {
		std::cout << "Bad Load" << std::endl;
		return;
	}

	sf::Sprite sprite(texture);

	sf::RenderWindow* win = windowHandle::Instance()->getWindow();//this must be called in any function you wanna mess with the window in, creates a reference to the main window

	win->draw(sprite);
	win->display();

	_gameState = ShowingSplash;

	sf::Event event;
	while (_gameState == ShowingSplash) {
		while (win->pollEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed) {
				return;
			}

		}
	}
}

void Spaghengine::Start(void)
{
	sf::Texture texture;

	if (texture.loadFromFile("thumb.png") != true) {//TEMP to show changing out of splash screen
		std::cout << "Bad Load" << std::endl;
		return;
	}

	sf::Sprite sprite(texture);

	sf::RenderWindow* win = windowHandle::Instance()->getWindow();

	win->draw(sprite);
	win->display();

	_gameState = Spaghengine::Playing;

	while (!IsExiting())
	{
		GameLoop();
	}
}

void Spaghengine::GameLoop(void) 
{
	sf::RenderWindow* win = windowHandle::Instance()->getWindow();
	masterClock.restart();

	while (win->isOpen())
	{
		//time since start of program
		sf::Time elapsed = masterClock.getElapsedTime();
		currentTime = elapsed.asSeconds();

		//delta time (time between frames)
		sf::Time dt = deltaClock.restart();
		deltaTime = dt.asSeconds();

		sf::Event event;
		while (win->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				win->close();
		}
	}
}

bool Spaghengine::IsExiting() {
	return false;
}
