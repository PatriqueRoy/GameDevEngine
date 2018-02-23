#include "TransformComponent.h"

void  TransformComponent::Awake() {
	sf::Transform trans;
	trans.translate(t_position.x, t_position.y);
	trans.rotate(t_rotation);
	trans.scale(t_scale.x,t_scale.y);
	const float* model = trans.getMatrix();
	matrix = model;
	transform = trans;
}

void TransformComponent::Start() {}

void TransformComponent::Update() {
	sf::Transform trans;
	trans.translate(t_position.x, t_position.y);
	trans.rotate(t_rotation);
	trans.scale(t_scale.x, t_scale.y);
	const float* model = trans.getMatrix();
	matrix = model;
	transform = trans;
}

void TransformComponent::LateUpdate() {}