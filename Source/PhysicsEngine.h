#pragma once
#include "TransformComponent.h"
#include "PhysicsRigidbody.h"
#include <list>
#include <map>
#include <cmath>
#include <algorithm>
#include <numeric>

/*
class PhysicsEngine
{
public:
	float groundedTol = 0.1f;
	struct CollisionPair {
		PhysicsRigidbody rigidBodyA;
		PhysicsRigidbody rigidBodyB;
	};
	struct CollisionInfo {
		Vector2 collisionNormal;
		float penetration;
	};
	void AddRigidBody(PhysicsRigidbody rigidBody);
	bool IsGrounded(PhysicsRigidbody rigidBody);
private:
	std::list<PhysicsRigidbody> rigidBodies;
	std::map<CollisionPair, CollisionInfo> collisions;
	void IntegrateBodies(float dT);
	void CheckCollisions();
	void ResolveCollisions();
	void PositionalCorrection(CollisionPair c);
	void UpdatePhysics();
	void FixedUpdate();
};*/