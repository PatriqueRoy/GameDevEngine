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
	splash->getTransform()->t_position = sf::Vector2f(0, 50);
	splash->getTransform()->t_scale = sf::Vector2f(1.5f, 1.5f);

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

	GameObject* paddle = objectManager.CreateObject();
	paddle->createSprite("paddleRed.png");
	paddle->getTransform()->t_position = sf::Vector2f(500, 700);
	paddle->getTransform()->t_scale = sf::Vector2f(1, 1);
	//setting proper origin
	float xCenter = paddle->getSprite()->getTexture()->getSize().x / 2;
	float yCenter = paddle->getSprite()->getTexture()->getSize().y / 2;
	paddle->getSprite()->setOrigin(sf::Vector2f(xCenter, yCenter));
	paddle->drawSprite(win);

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

	GameObject* ball = objectManager.CreateObject();
	ball->createSprite("ballBlue.png");
	ball->getTransform()->t_position = sf::Vector2f(500, 350);
	ball->getTransform()->t_scale = sf::Vector2f(1, 1);
	float xCenter = ball->getSprite()->getTexture()->getSize().x / 2;
	float yCenter = ball->getSprite()->getTexture()->getSize().y / 2;
	ball->getSprite()->setOrigin(sf::Vector2f(xCenter, yCenter));

	ball->getTransform()->velocity = sf::Vector2f(0.1f, 0.1f);

	while (win->isOpen())
	{
		//time since start of program
		sf::Time elapsed = masterClock.getElapsedTime();
		currentTime = elapsed.asSeconds();

		//delta time (time between frames)
		sf::Time dt = deltaClock.restart();
		deltaTime = dt.asSeconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			GameObject* temp = objectManager.returnObject(1);
			float tempX = temp->getTransform()->t_position.x;
			if (tempX >= 0) {
				temp->getTransform()->t_position = sf::Vector2f(tempX -= 0.1f, 700);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			GameObject* temp = objectManager.returnObject(1);
			float tempX = temp->getTransform()->t_position.x;
			if (tempX <= win->getSize().x) {
				temp->getTransform()->t_position = sf::Vector2f(tempX += 0.1f, 700);
			}
		}

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
