#include <stdio.h>
#include "GameObject.h"
#include "iostream"
#include <map>
#include <list>
#include <iterator>

class GameObjectManager
{
public:
	GameObject* CreateObject();

	void Update(float msec, sf::RenderWindow *window);
	void Awake();
	void Start();
	void LateUpdate(float msec, sf::RenderWindow *window);

	void checkForCollisions(GameObject* first);

	GameObject* returnObject(int index);
	int endIndex();

private:
	std::map<int, GameObject*> objects;
	static int nextObjectID;
};
