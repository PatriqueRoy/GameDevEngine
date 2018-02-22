#pragma once
#include "BaseComponent.h"

struct Vector3
{
	Vector3() : x(0.0f), y(0.0f), z(0.0f){}

	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	float x, y, z;
};

class TransformComponent : public BaseComponent {
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();

	Vector3 GetPosition() { return t_position; }
	Vector3 GetRotation() { return t_rotation; };
	Vector3 GetScale() { return t_scale; };

protected:
	Vector3 t_position;
	Vector3 t_rotation;
	Vector3 t_scale;
};