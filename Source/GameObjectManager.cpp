#include "GameObjectManager.h"

// new game object ID
int GameObjectManager::nextObjectID = 0;

AudioComponent GameObjectManager::audioManager = AudioComponent();

int GameObjectManager::score = 0;
int GameObjectManager::health = 3;

void GameObjectManager::Awake() {
	for (std::map<int, GameObject*>::iterator i = objects.begin(); i != objects.end(); ++i) {
		(i->second)->Awake();
	}
}

void GameObjectManager::Start() {
	/*for (std::map<int, GameObject*>::iterator i = objects.begin(); i != objects.end(); ++i) {
		(i->second)->Start();
	}*/
}

void GameObjectManager::Update(float msec, sf::RenderWindow *window) {
	//window->clear();
	for (std::map<int, GameObject*>::iterator i = objects.begin(); i != objects.end(); ++i) {
		(i->second)->Update(msec, window);

		std::string firstName = i->second->getName();

		if (firstName == "ball")
		{
			checkForCollisions(i->second);
		}
	}
	window->display();
}

GameObject* GameObjectManager::returnObject(int index) {
	for (std::map<int, GameObject*>::iterator i = objects.begin(); i != objects.end(); ++i) {
		if (i->first == index) {
			return i->second;
		}
	}
}

int GameObjectManager::endIndex() {
	return nextObjectID;
}

GameObject* GameObjectManager::CreateObject()
{
	GameObject* newObj = new GameObject(nextObjectID++);
	objects[newObj->GetObjectID()] = newObj;
	return newObj;
}

void GameObjectManager::checkForCollisions(GameObject* first)
{
	for (std::map<int, GameObject*>::iterator j = objects.begin(); j != objects.end(); ++j)
	{
		std::string secondName = j->second->getName();

		if (secondName == "block" && j->second->isDrawn)
		{
			if (first->getSprite()->getGlobalBounds().intersects(j->second->getSprite()->getGlobalBounds()))
			{
				//reversing velocity
				float tempYVel = first->getTransform()->velocity.y;
				first->getTransform()->velocity = sf::Vector2f(first->getTransform()->velocity.x, tempYVel * -1);

				//playing sound
				audioManager.playSound("boop.wav", 35);

				//making block dissapear
				j->second->isDrawn = false;
				score++;
				return;
			}
		}
	}
}

