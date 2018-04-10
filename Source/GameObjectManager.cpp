#include "GameObjectManager.h"

// new game object ID
int GameObjectManager::nextObjectID = 0;

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
	window->clear();
	for (std::map<int, GameObject*>::iterator i = objects.begin(); i != objects.end(); ++i) {
		(i->second)->Update(msec, window);
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

