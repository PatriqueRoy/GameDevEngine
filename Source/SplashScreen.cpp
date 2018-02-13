#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SplashScreen.h"
#include "Spaghengine.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow) {
	sf::Image image;

	if (image.loadFromFile("images/SplashScreen.png") != true) {
		return;
	}

	sf::Sprite sprite(image);

	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (_gameState != Spaghengine::Initialized) {
		while (renderWindow.GetEvent(event)) {
			if (event.Type == sf::Event::EventType::KeyPressed
				|| event.Type == sf::Event::EventType::MouseButtonPressed
				|| event.Type == sf::Event::EventType::Closed) {
				return;
			}
		}
	}
}