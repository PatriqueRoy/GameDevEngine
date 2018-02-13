#include "Spaghengine.h"
#include "Initiate.h"
#include <iostream>


Spaghengine::GameState Spaghengine::_gameState = Spaghengine::Uninitialized;
sf::RenderWindow Spaghengine::_mainWindow;

void Spaghengine::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024,768,32),"GameName");
	_gameState = Spaghengine::Playing;

	while (!IsExiting())
	{
		GameLoop();
	}
}

void Spaghengine::Initialize(void)
{
	bool init = initEngine();
	if (!init) {
		exit;
	}
	/*
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
	}*/
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

bool Spaghengine::IsExiting() {
	return false;
}
