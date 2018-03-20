#pragma once
#include "TransformComponent.h"
#include "PhysicsEngine.h"

class PhysicsRigidbody {
public:
	float mass;
	float bounciness;
	bool obeysGravity;
	Vector2 gravity = Vector2(0, -9.8f);
	Vector2 currentVelocity;
	Vector2 maxVelocity =  Vector2(10.0f, 10.0f);
	bool grounded;
	struct AABB
	{
		Vector2 bLeft;
		Vector2 tRight;
	};
	AABB aabb;
	void AddForce(Vector2 force);
	void Stop();
	bool IsGrounded();
	void SetAABB();
	void Start();
	void Integrate(float dT);
private:
	Vector2 totalForces;
	PhysicsEngine engine;
};