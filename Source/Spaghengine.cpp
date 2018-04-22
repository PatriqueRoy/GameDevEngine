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

void Spaghengine::MakeDocument() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLNode * pRoot = xmlDoc.NewElement("Root");
	xmlDoc.InsertFirstChild(pRoot);

	for (int i = 0; i < objectManager.endIndex(); i++)
	{
		tinyxml2::XMLElement * pElement = xmlDoc.NewElement("GameObject");
		pElement->SetAttribute("objectIndex", i);
		pElement->SetAttribute("objName", objectManager.returnObject(i)->getName().c_str());
		pElement->SetAttribute("spriteName", objectManager.returnObject(i)->texFilePath.c_str());
		pElement->SetAttribute("xPos", objectManager.returnObject(i)->getTransform()->t_position.x);
		pElement->SetAttribute("yPos", objectManager.returnObject(i)->getTransform()->t_position.y);
		pElement->SetAttribute("rot", objectManager.returnObject(i)->getTransform()->t_rotation);
		pElement->SetAttribute("xScale", objectManager.returnObject(i)->getTransform()->t_scale.x);
		pElement->SetAttribute("yScale", objectManager.returnObject(i)->getTransform()->t_scale.y);
		pElement->SetAttribute("xVel", objectManager.returnObject(i)->getTransform()->velocity.x);
		pElement->SetAttribute("yVel", objectManager.returnObject(i)->getTransform()->velocity.y);
		pRoot->InsertEndChild(pElement);
	}

	xmlDoc.SaveFile("SavedData.xml");
}

void Spaghengine::ReadDocument() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("SavedData.xml");

	tinyxml2::XMLNode * pRoot = xmlDoc.FirstChild();

	tinyxml2::XMLElement * pElement = pRoot->LastChildElement("GameObject");

	//Getting number of elements
	int endIndex;
	eResult = pElement->QueryIntAttribute("objectIndex", &endIndex);

	pElement = pRoot->FirstChildElement("GameObject");

	int currentIndex = 0;

	while (currentIndex < endIndex) {
		const char * spriteName;
		const char * objName;
		float xPos, yPos, rot, xScale, yScale, xVel, yVel;
		eResult = pElement->QueryStringAttribute("spriteName", &spriteName);
		eResult = pElement->QueryStringAttribute("objName", &objName);
		eResult = pElement->QueryFloatAttribute("xPos", &xPos);
		eResult = pElement->QueryFloatAttribute("yPos", &yPos);
		eResult = pElement->QueryFloatAttribute("rot", &rot);
		eResult = pElement->QueryFloatAttribute("xScale", &xScale);
		eResult = pElement->QueryFloatAttribute("yScale", &yScale);
		eResult = pElement->QueryFloatAttribute("xVel", &xVel);
		eResult = pElement->QueryFloatAttribute("yVel", &yVel);

		GameObject* obj = objectManager.CreateObject();

		obj->createSprite(spriteName);
		obj->getTransform()->t_position = sf::Vector2f(xPos, yPos);
		obj->getTransform()->t_rotation = rot;
		obj->getTransform()->t_scale = sf::Vector2f(xScale, yScale);
		float xCenter = obj->getSprite()->getTexture()->getSize().x / 2;
		float yCenter = obj->getSprite()->getTexture()->getSize().y / 2;
		obj->getSprite()->setOrigin(sf::Vector2f(xCenter, yCenter));
		obj->getTransform()->velocity = sf::Vector2f(xVel, yVel);
		obj->setName(objName);
		obj->isDrawn = false;

		pElement = pElement->NextSiblingElement("GameObject");
		eResult = pElement->QueryIntAttribute("objectIndex", &currentIndex);
	}
}

void Spaghengine::Initialize(void)
{
	if (_gameState != Uninitialized)
		return;

	bool init = initEngine();
	if (!init) {
		exit;
	}
	sf::RenderWindow* win = windowHandle::Instance()->getWindow();

	ReadDocument();

	objectManager.returnObject(0)->isDrawn = true;
	objectManager.returnObject(0)->drawSprite(win);

	win->display();

	_gameState = ShowingSplash;

	sf::Event event;
	while (_gameState == ShowingSplash) {
		while (win->pollEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed) {
				std::cout << "done splash" << std::endl;
				objectManager.returnObject(0)->isDrawn = false;
				return;
			}
		}
	}
}

void Spaghengine::Start(void)
{
	sf::RenderWindow* win = windowHandle::Instance()->getWindow();

	objectManager.audioManager.playMusic("music.wav", 15);

	for (int i = 1; i < objectManager.endIndex(); i++) {
		objectManager.returnObject(i)->isDrawn = true;
		objectManager.returnObject(i)->drawSprite(win);
	}

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

	restart:
	GameObject* paddelRef = objectManager.returnObject(1);
	GameObject* ballRef = objectManager.returnObject(2);

	for (int i = 1; i < objectManager.endIndex(); i++) {
		objectManager.returnObject(i)->isDrawn = true;
		objectManager.returnObject(i)->drawSprite(win);
	}

	ballRef->getTransform()->t_position = sf::Vector2f(115, 300);
	objectManager.score = 0;
	objectManager.health = 3;

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "error" << std::endl;
	}

	sf::Text scoreText("Score = 0", font);
	scoreText.setCharacterSize(15);
	scoreText.setFillColor(sf::Color::White);

	sf::Text healthText("Health: 3", font);
	healthText.setCharacterSize(15);
	healthText.setPosition(sf::Vector2f(345, 0));
	healthText.setFillColor(sf::Color::White);

	while (win->isOpen() && objectManager.health > 0)
	{
		int Score = objectManager.score;
		std::string temp = "Score: " + std::to_string(Score);
		scoreText.setString(temp);

		int Health = objectManager.health;
		std::string temp2 = "Health: " + std::to_string(Health);
		healthText.setString(temp2);

		win->draw(scoreText);
		win->draw(healthText);

		//time since start of program
		sf::Time elapsed = masterClock.getElapsedTime();
		currentTime = elapsed.asSeconds();

		//delta time (time between frames)
		sf::Time dt = deltaClock.restart();
		deltaTime = dt.asSeconds();

		if (ballRef->getTransform()->t_position.y >= win->getSize().y) {
			objectManager.health--;
		}

		if (ballRef->getSprite()->getGlobalBounds().intersects(paddelRef->getSprite()->getGlobalBounds())) 
		{
			float tempYVel = ballRef->getTransform()->velocity.y;
			ballRef->getTransform()->velocity = sf::Vector2f(ballRef->getTransform()->velocity.x, tempYVel * -1);
			objectManager.audioManager.playSound("boop.wav", 35);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			float tempX = paddelRef->getTransform()->t_position.x;
			if (tempX >= 0) {
				paddelRef->getTransform()->t_position = sf::Vector2f(tempX -= 0.2f, 575);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			float tempX = paddelRef->getTransform()->t_position.x;
			if (tempX <= win->getSize().x) {
				paddelRef->getTransform()->t_position = sf::Vector2f(tempX += 0.2f, 575);
			}
		}

		objectManager.Update(deltaTime, win);

		win->clear();

		sf::Event event;
		while (win->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				win->close();
		}
	}

	win->clear();
	goto restart;
}

bool Spaghengine::IsExiting() {
	return false;
}
