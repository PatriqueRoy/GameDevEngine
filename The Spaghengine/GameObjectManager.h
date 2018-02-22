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

	void Update(float msec);
	void Awake();
	void Start();

private:
	std::map<int, GameObject*> objects;
	static int nextObjectID;
};
