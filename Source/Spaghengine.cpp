#include "Spaghengine.h"
#include <iostream>

Spaghengine::GameState Spaghengine::_gameState = Spaghengine::Uninitialized;

Spaghengine::Spaghengine(sf::RenderWindow& window) : _mainWindow(window)
{
}

void Spaghengine::Start(void)
{
	if (_gameState != Uninitialized)
		return;
	
	_gameState = Spaghengine::Playing;

	_gameState = ShowingSplash;
}


void Spaghengine::Initialize(void)
{
	sf::Texture texture;

	if (texture.loadFromFile("theThing.png") != true) {
		std::cout << "Bad" << std::endl;
		return;
	}

	sf::Sprite sprite(texture);

	_mainWindow.draw(sprite);
	_mainWindow.display();
	
	_gameState = ShowingSplash;

	sf::Event event;
	while (_gameState == ShowingSplash) {
		while (_mainWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed) {
				return;
			}

		}
	}
}

void Spaghengine::GameLoop(void) 
{
	std::cout << "continued" << std::endl;
	while (_mainWindow.isOpen())
	{
		sf::Event event;
		while (_mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_mainWindow.close();
		}
	}
}
