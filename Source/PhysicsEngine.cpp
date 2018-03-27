#include "PhysicsEngine.h"

/*
void PhysicsEngine::AddRigidBody(PhysicsRigidbody rigidBody)
{
	rigidBodies.push_front(rigidBody);
}

void PhysicsEngine::IntegrateBodies(float dT)
{
	for each(PhysicsRigidbody rb in rigidBodies) {
		rb.Integrate(dT);
	}
}

bool PhysicsEngine::IsGrounded(PhysicsRigidbody rigidBody)
{
	for each(PhysicsRigidbody rb in rigidBodies) {
		if (rb != rigidBody) {
			if (rigidBody.aabb.bLeft.x < rb.aabb.tRight.x
				&& rigidBody.aabb.tRight.x > rb.aabb.bLeft.x
				&& std::abs(rigidBody.aabb.bLeft.y - rb.aabb.tRight.y) <= groundedTol) {
				if (std::abs(rigidBody.currentVelocity.y) < groundedTol)
					return true;
			}
		}
	}
	return false;
}

void PhysicsEngine::CheckCollisions()
{
	for each(PhysicsRigidbody bodyA in rigidBodies.GetRange(0, rigidBodies.size - 1)) {
		for each(PhysicsRigidbody bodyB in rigidBodies.GetRange(rigidBodies.IndexOf(bodyA), rigidBodies.size - rigidBodies.IndexOf(bodyA))) {
			if (bodyA != bodyB) {
				CollisionPair pair;
				CollisionInfo colInfo;
				pair.rigidBodyA = bodyA; pair.rigidBodyB = bodyB;

				Vector2 distance = bodyB.t_position - bodyA.t_position;

				Vector2 halfSizeA = (bodyA.aabb.tRight - bodyA.aabb.bLeft) / 2;
				Vector2 halfSizeB = (bodyB.aabb.tRight - bodyB.aabb.bLeft) / 2;

				Vector2 gap = Vector2(std::abs(distance.x), std::abs(distance.y)) - (halfSizeA + halfSizeB);

				// Seperating Axis Theorem test
				if (gap.x < 0 && gap.y < 0) {
					if (collisions.ContainsKey(pair)) {
						collisions.Remove(pair);
					}

					if (gap.x > gap.y) {
						if (distance.x > 0) {
							// ... Update collision normal
							colInfo.collisionNormal =  Vector2(1, 0);
						}
						else {
							// ... Update collision normal
							colInfo.collisionNormal =  Vector2();
						}
						colInfo.penetration = gap.x;
					}
					else {
						if (distance.y > 0) {
							// ... Update collision normal
							colInfo.collisionNormal =  Vector2(0, 1);
						}
						else {
							// ... Update collision normal
							colInfo.collisionNormal =  Vector2(0, -1);
						}
						colInfo.penetration = gap.y;
					}
					collisions.Add(pair, colInfo);
				}
				else if (collisions.ContainsKey(pair)) {
					collisions.Remove(pair);
				}

			}
		}
	}
}

void PhysicsEngine::ResolveCollisions()
{
	for each(CollisionPair pair in collisions.keys) {
		float minBounce = std::min(pair.rigidBodyA.bounciness, pair.rigidBodyB.bounciness);
		float velAlongNormal = Vector2.Dot(pair.rigidBodyB.currentVelocity - pair.rigidBodyA.currentVelocity, collisions[pair].collisionNormal);
		if (velAlongNormal > 0) continue;

		float j = -(1 + minBounce) * velAlongNormal;
		float invMassA, invMassB;
		if (pair.rigidBodyA.mass == 0)
			invMassA = 0;
		else
			invMassA = 1 / pair.rigidBodyA.mass;

		if (pair.rigidBodyB.mass == 0)
			invMassB = 0;
		else
			invMassB = 1 / pair.rigidBodyB.mass;

		j /= invMassA + invMassB;

		Vector2 impulse =  collisions[pair].collisionNormal * j;

		// ... update velocities
		pair.rigidBodyA.currentVelocity -= impulse * pair.rigidBodyA.mass / 1.0f;
		pair.rigidBodyB.currentVelocity += impulse * pair.rigidBodyB.mass / 1.0f;

		if (std::abs(collisions[pair].penetration) > 0.01f) {
			PositionalCorrection(pair);
		}
	}
}

void PhysicsEngine::PositionalCorrection(CollisionPair c)
{
	const float percent = 0.2f;

	float invMassA, invMassB;
	if (c.rigidBodyA.mass == 0)
		invMassA = 0;
	else
		invMassA = 1 / c.rigidBodyA.mass;

	if (c.rigidBodyB.mass == 0)
		invMassB = 0;
	else
		invMassB = 1 / c.rigidBodyB.mass;

	Vector2 correction = -collisions[c].collisionNormal * ((collisions[c].penetration / (invMassA + invMassB)) * percent) ;

	Vector2 temp = c.rigidBodyA.t_position;
	temp -= correction * invMassA ;
	c.rigidBodyA.t_position = temp;

	temp = c.rigidBodyB.t_position;
	temp += correction * invMassB;
	c.rigidBodyB.t_position = temp;
}

void PhysicsEngine::UpdatePhysics()
{
	IntegrateBodies(Time.deltaTime);
	CheckCollisions();
	ResolveCollisions();
}

void PhysicsEngine::FixedUpdate()
{
	UpdatePhysics();
}
*/