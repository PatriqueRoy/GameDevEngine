#include "Spaghengine.h"

Spaghengine::GameState Spaghengine::_gameState = Spaghengine::Uninitialized;

void Spaghengine::Start(void)
{
	if (_gameState != Uninitialized)
		return;
	
	_mainWindow.create(sf::VideoMode(1024, 768, 32), "GameName");
	_gameState = Spaghengine::Playing;

	while (_mainWindow.isOpen())
	{
		sf::Event event;
		while (_mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_mainWindow.close();
		}
		_mainWindow.display();
	}

	_gameState = ShowingSplash;
}

/*
void Spaghengine::Initialize(void)
{
	sf::Texture texture;
	texture.loadFromFile("images/SplashScreen.png");
	if (texture.loadFromFile("images/SplashScreen.png") != true) {
		return;
	}

	sf::Sprite sprite(texture);

	_mainWindow.draw(sprite);
	_mainWindow.display();
	
	sf::Event event;
	while (_gameState != ShowingSplash) {
		while (_mainWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed) {
				return;
			}

		}
	}
}*/
