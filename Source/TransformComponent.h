#pragma once
#include "BaseComponent.h"
#include <SFML\Graphics\Transform.hpp>
/*
struct Vector2
{
	Vector2() : x(0.0f), y(0.0f){}
	Vector2(float _x, float _y) : x(_x), y(_y) {}
	Vector2(const Vector2 &v): x(v.x), y(v.y) {};
	Vector2(const Vector2 *v) : x(v->x), y(v->y) {};

	float x, y;

	inline bool Vector2::operator == (const Vector2 &v) const { return (x == v.x) && (y == v.y); }
	inline bool Vector2::operator != (const Vector2 &v) const { return (x != v.x) || (y != v.y); }
	inline Vector2 & Vector2::operator - (void) { x = -x; y = -y; return *this; }

	inline const Vector2 Vector2::operator + (const Vector2 &v) const { return Vector2(x + v.x, y + v.y); }
	inline const Vector2 Vector2::operator - (const Vector2 &v) const { return Vector2(x - v.x, y - v.y); }
	inline const Vector2 Vector2::operator * (const Vector2 &v) const { return Vector2(x * v.x, y * v.y); }
	inline const Vector2 Vector2::operator / (const Vector2 &v) const { return Vector2(x / v.x, y / v.y); }

	inline Vector2& Vector2::operator += (const Vector2 &v) { x += v.x; y += v.y; return *this; }
	inline Vector2& Vector2::operator -= (const Vector2 &v) { x -= v.x; y -= v.y; return *this; }

	inline const Vector2 Vector2::operator + (float v) const { return Vector2(x + v, y + v); }
	inline const Vector2 Vector2::operator - (float v) const { return Vector2(x - v, y - v); }
	inline const Vector2 Vector2::operator * (float v) const { return Vector2(x * v, y * v); }
	inline const Vector2 Vector2::operator / (float v) const { return Vector2(x / v, y / v); }

};*/

class TransformComponent : public BaseComponent {
public:
	/*
	void Awake();
	void Start();
	void Update();
	void LateUpdate();*/
	float xPos;
	float yPos;
	sf::Vector2f t_position;
	float t_rotation;
	sf::Vector2f t_scale;

	void setPosition(float x, float y) {
		xPos = x;
		yPos = y;
	}

	//sf::Transform transform;
	//const float* matrix = transform.getMatrix();
};