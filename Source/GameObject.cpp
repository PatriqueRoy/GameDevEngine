#include "GameObject.h"
#include <iostream>

void GameObject::AddChild(GameObject* s) {
	children.push_back(s);
	s->parent =	this;
}

void GameObject::AddComponent(BaseComponent* c) {
	components.push_back(c);
}

void GameObject::Awake() {
	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Awake();
	}
}

void GameObject::Start() {
	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Start();
	}
}

void GameObject::Update(float msec, sf::RenderWindow *window) {
	drawSprite(window);

	//updating children if present
	for(std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Update(msec, window);
	}
}

void GameObject::updateSpriteTransform(sf::RenderWindow *window) {
	Local_Transform.t_position = sf::Vector2f(Local_Transform.t_position.x + Local_Transform.velocity.x, Local_Transform.t_position.y + Local_Transform.velocity.y);

	if (parent) {
		//This node has a parent...  
		World_Transform = TransformAdd(parent->World_Transform, Local_Transform);
	}
	else
	{
		//Root node, world transform is local transform!
		World_Transform = Local_Transform;
	}

	if (Local_Transform.velocity.x > 0 || Local_Transform.velocity.y > 0 || Local_Transform.velocity.x < 0 || Local_Transform.velocity.y < 0)
	{
		if (World_Transform.t_position.x <= 0 || World_Transform.t_position.x >= window->getSize().x) {
			float tempXVel = Local_Transform.velocity.x;
			Local_Transform.velocity = sf::Vector2f(tempXVel * -1, Local_Transform.velocity.y);
		}
		if (World_Transform.t_position.y <= 0 || World_Transform.t_position.y >= window->getSize().y) {
			float tempYVel = Local_Transform.velocity.y;
			Local_Transform.velocity = sf::Vector2f(Local_Transform.velocity.x, tempYVel * -1);
		}
	}

	float tempX = World_Transform.t_position.x;
	float tempY = World_Transform.t_position.y;

	objectSprite.setPosition(tempX, tempY);

	float tempScaleX = World_Transform.t_scale.x;
	float tempScaleY = World_Transform.t_scale.y;
	objectSprite.setScale(tempScaleX, tempScaleY);

	float tempRot = World_Transform.t_rotation;
	objectSprite.setRotation(tempRot);
}

//Initilizing sprite/texture
void GameObject::createSprite(std::string fileName) {
	if (objectTex.loadFromFile(fileName) != true) {
		std::cout << "Bad Load" << std::endl;
		return;
	}

	objectSprite.setTexture(objectTex);
}

//drawing sprite
void GameObject::drawSprite(sf::RenderWindow *window) {
	updateSpriteTransform(window);

	if (checkForParent()) {
		if (parent->isDrawn) {
			window->draw(objectSprite);
		}
	}
	else {
		if (isDrawn) {
			window->draw(objectSprite);
		}
	}
}