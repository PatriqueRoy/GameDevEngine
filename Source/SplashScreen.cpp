#include "SplashScreen.h"
#include "Spaghengine.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow) {
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