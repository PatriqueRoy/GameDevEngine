#pragma once
#include "BaseComponent.h"
#include <SFML\Graphics\Transform.hpp>

struct Vector2
{
	Vector2() : x(0.0f), y(0.0f){}

	Vector2(float _x, float _y) : x(_x), y(_y) {}

	float x, y;
};

class TransformComponent : public BaseComponent {
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();

	Vector2 t_position;
	float t_rotation;
	Vector2 t_scale;

	sf::Transform transform;
	const float* matrix = transform.getMatrix();
};