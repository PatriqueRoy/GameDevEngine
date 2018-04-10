#include "Spaghengine.h"
#include "Initiate.h"
#include <iostream>
#include "TransformComponent.h"

GameObjectManager Spaghengine::objectManager = GameObjectManager();
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
	sf::RenderWindow* win = windowHandle::Instance()->getWindow();

	GameObject* splash = objectManager.CreateObject();
	splash->createSprite("theThing.png");
	splash->getSprite()->setScale(sf::Vector2f(1.5f, 1.5));
	splash->getSprite()->setPosition(sf::Vector2f(0, 50));

	splash->drawSprite(win);

	win->display();

	_gameState = ShowingSplash;

	sf::Event event;
	while (_gameState == ShowingSplash) {
		while (win->pollEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed) {
				std::cout << "done splash" << std::endl;
				splash->isDrawn = false;
				return;
			}

		}
	}
}

void Spaghengine::Start(void)
{
	sf::RenderWindow* win = windowHandle::Instance()->getWindow();

	GameObject* thumb = objectManager.CreateObject();
	thumb->createSprite("thumb.png");
	thumb->getSprite()->setScale(sf::Vector2f(0.1f, 0.1f));
	thumb->getSprite()->setPosition(sf::Vector2f(500, 50));
	thumb->drawSprite(win);

	win->display();

	_gameState = Spaghengine::Playing;

	while (!IsExiting())
	{
		GameLoop();
	}
}

void Spaghengine::GameLoop(void) 
{
	std::cout << "game loop" << std::endl;
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

		objectManager.Update(deltaTime, win);

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
