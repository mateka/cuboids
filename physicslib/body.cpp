#include <physicslib/body.h>
#include <limits>
#include <array>


namespace physicslib {

body::~body() {
	m_world.removeRigidBody(&m_rigidBody);
}

body::body(
	btDiscreteDynamicsWorld& world,
	const float mass,
	btCollisionShape& shape,
	const btTransform& startTransform
)
	: m_world{ world }, m_motionState{ startTransform },
	m_rigidBody{ { mass, &m_motionState, &shape, [mass, &shape]() {
		btVector3 inertia{0,0,0};
		if (mass > std::numeric_limits<float>::epsilon())
			shape.calculateLocalInertia(mass, inertia);
		return inertia;
	}()} }
{
	m_world.addRigidBody(&m_rigidBody);
}

body::body(
	btDiscreteDynamicsWorld& world,
	const float mass,
	btCollisionShape& shape,
	const btVector3& startPosition
)
	: body{ world, mass, shape, [&startPosition]() {
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(startPosition);
		return startTransform;
	}() }
{}

body::body(
	btDiscreteDynamicsWorld& world,
	btCollisionShape& shape,
	const btTransform& startTransform
)
	: body{ world, 0.0f, shape, startTransform }
{}

body::body(
	btDiscreteDynamicsWorld& world,
	btCollisionShape& shape,
	const btVector3& startPosition
)
	: body{ world, 0.0f, shape, startPosition }
{}

void body::constrain_movement(const bool x, const bool y, const bool z) {
	auto b2f = [](const bool b) { return b ? 1.0f : 0.0f; };
	m_rigidBody.setLinearFactor({ b2f(x), b2f(y), b2f(z) });
}

void body::constrain_rotation(const bool x, const bool y, const bool z) {
	auto b2f = [](const bool b) { return b ? 1.0f : 0.0f; };
	m_rigidBody.setAngularFactor({ b2f(x), b2f(y), b2f(z) });
}

btVector3 body::velocity() const {
	return m_rigidBody.getLinearVelocity();
}

void body::velocity(const btVector3& v) {
	m_rigidBody.activate(true);
	m_rigidBody.setLinearVelocity(v);
}

btVector3 body::angular_velocity() const {
	return m_rigidBody.getAngularVelocity();
}

void body::angular_velocity(const btVector3& v) {
	m_rigidBody.activate(true);
	m_rigidBody.setAngularVelocity(v);
}

glm::mat4 body::transform() const {
	btTransform transform;
	m_motionState.getWorldTransform(transform);

	std::array<btScalar, 16> components;
	transform.getOpenGLMatrix(components.data());
	return  {
		components[0], components[1], components[2], components[3],
		components[4], components[5], components[6], components[7],
		components[8], components[9], components[10], components[11],
		components[12], components[13], components[14], components[15]
	};
}

}
