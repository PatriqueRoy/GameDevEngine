#include "PhysicsRigidbody.h"

void PhysicsRigidbody::AddForce(Vector2 force)
{
	totalForces += force;
}

void PhysicsRigidbody::Stop()
{
	currentVelocity = Vector2();
	totalForces = Vector2();
}

bool PhysicsRigidbody::IsGrounded()
{
	grounded = engine.IsGrounded(this);
	return grounded;
}

void PhysicsRigidbody::SetAABB()
{
	Bounds bound = new Bounds(new Vector2(), new Vector2(1, 1));
	Renderer renderer = GetComponent<Renderer>();

	if (renderer)
	{
		bound = renderer.bounds;
	}

	aabb.bLeft = Vector2(bound.center.x - bound.extents.x, bound.center.y - bound.extents.y);
	aabb.tRight = Vector2(bound.center.x + bound.extents.x, bound.center.y + bound.extents.y);
}

void PhysicsRigidbody::Start()
{
	SetAABB();
	engine = PhysicsEngine;

	engine.AddRigidBody(this);
}

void PhysicsRigidbody::Integrate(float dT)
{
	if (obeysGravity && !IsGrounded()) {
		AddForce(gravity);
	}
	else {
		if (std::abs(currentVelocity.y) < 0.05f) currentVelocity.y = 0;
	}
	///
	///
	///

	Vector2 acceleration = totalForces / mass;
	if (mass == 0)
		acceleration = Vector2();

	currentVelocity += acceleration * dT;

	Vector2 temp = t_position;
	temp += currentVelocity * dT;
	t_position = temp;
	SetAABB();

	totalForces = Vector2();
}
