#include "GameObject.h"

/*GameObject::~GameObject(
	void
) {
	for(unsigned int i = 0; i< children.size(); i++){
		delete	children[i];
	}
}*/
void GameObject::AddChild(GameObject* s) {
	children.push_back(s);
	s->parent =	this;
}

void GameObject::AddComponent(BaseComponent* c) {
	components.push_back(c);
}

void GameObject::Awake() {
	if (parent) {
		//This node has a parent...  
		World_Transform = parent->World_Transform * Local_transform.transform;
	}
	else
	{
		//Root node, world transform is local transform!
		World_Transform = Local_transform.transform;
	}
	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Awake();
	}
}

void GameObject::Start() {
	if (parent) {
		//This node has a parent...  
		World_Transform = parent->World_Transform * Local_transform.transform;
	}
	else
	{
		//Root node, world transform is local transform!
		World_Transform = Local_transform.transform;
	}
	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Start();
	}
}


void GameObject::Update(float msec) {
	if (parent) {
		//This node has a parent...  
		World_Transform = parent->World_Transform * Local_transform.transform;
	}
	else
	{
		//Root node, world transform is local transform!
		World_Transform = Local_transform.transform;
	}
	for(std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Update(msec);
	}
}