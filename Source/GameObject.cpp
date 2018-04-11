#include "GameObject.h"
#include <iostream>

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
	updateSpriteTransform();

	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Awake();
	}
}

void GameObject::Start() {
	updateSpriteTransform();

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

void GameObject::updateSpriteTransform() {
	if (parent) {
		//This node has a parent...  
		World_Transform = TransformAdd(parent->World_Transform, Local_Transform);
	}
	else
	{
		//Root node, world transform is local transform!
		World_Transform = Local_Transform;
	}

	World_Transform.t_position = sf::Vector2f(World_Transform.t_position.x + World_Transform.velocity.x, World_Transform.t_position.y + World_Transform.velocity.y);
	std::cout << World_Transform.t_position.x << std::endl;

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
	if (objectTex.loadFromFile(fileName) != true) {//TEMP to show changing out of splash screen
		std::cout << "Bad Load" << std::endl;
		return;
	}

	objectSprite.setTexture(objectTex);
}

//drawing sprite
void GameObject::drawSprite(sf::RenderWindow *window) {
	updateSpriteTransform();

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