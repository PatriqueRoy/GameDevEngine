#include "Spaghengine.h"
#include "Initiate.h"
#include <iostream>

Spaghengine::GameState Spaghengine::_gameState = Spaghengine::Uninitialized;


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

	sf::RenderWindow* win = windowHandle::Instance()->getWindow();

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

	if (texture.loadFromFile("thumb.png") != true) {
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

	while (win->isOpen())
	{
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
