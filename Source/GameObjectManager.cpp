#include "GameObjectManager.h"

// new game object ID
int GameObjectManager::nextObjectID = 0;

void GameObjectManager::Awake() {
	for (std::map<int, GameObject*>::iterator i = objects.begin(); i != objects.end(); ++i) {
		(i->second)->Awake();
	}
}

void GameObjectManager::Start() {
	for (std::map<int, GameObject*>::iterator i = objects.begin(); i != objects.end(); ++i) {
		(i->second)->Start();
	}
}

void GameObjectManager::Update(float msec) {
	for (std::map<int, GameObject*>::iterator i = objects.begin(); i != objects.end(); ++i) {
		(i->second)->Update(msec);
	}
}

GameObject* GameObjectManager::CreateObject()
{
	GameObject* newObj = new GameObject(nextObjectID++);
	objects[newObj->GetObjectID()] = newObj;
	return newObj;
}

