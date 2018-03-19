#include "PhysicsRigidbody.h"

void PhysicsRigidbody::AddForce(Vector2 force)
{
	totalForces += force;
}

void PhysicsRigidbody::Stop()
{
	currentVelocity = Vector2(0.0f,0.0f);
	totalForces = Vector2(0.0f,0.0f);
}

bool PhysicsRigidbody::IsGrounded()
{
	grounded = engine.IsGrounded('this');
	return grounded;
}

void PhysicsRigidbody::SetAABB()
{
	Bounds bound = new Bounds(new Vector2(0, 0), new Vector2(1, 1));
	Renderer renderer = GetComponent<Renderer>();

	if (renderer)
	{
		bound = renderer.bounds;
	}

	aabb.bLeft = new Vector2(bound.center.x - bound.extents.x, bound.center.y - bound.extents.y);
	aabb.tRight = new Vector2(bound.center.x + bound.extents.x, bound.center.y + bound.extents.y);
}

void PhysicsRigidbody::Start()
{
	SetAABB();
	engine = GameObject.FindWithTag("PhysicsEngine").GetComponent<PhysicsEngine>();

	engine.AddRigidBody(this);
}

void PhysicsRigidbody::Integrate(float dT)
{
	if (obeysGravity && !IsGrounded()) {
		AddForce(gravity);
	}
	else {
		if (Mathf.Abs(currentVelocity.y) < 0.05f) currentVelocity.y = 0;
	}
	///
	///
	///

	Vector2 acceleration = totalForces / mass;
	if (mass == 0)
		acceleration = Vector2.zero;

	currentVelocity += acceleration * dT;

	Vector2 temp = transform.position;
	temp += currentVelocity * dT;
	transform.position = temp;
	SetAABB();

	totalForces = Vector2.zero;
}
