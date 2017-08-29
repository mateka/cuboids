#include <physicslib/body.h>
#include <physicslib/world.h>
#include <limits>
#include <array>


namespace physicslib {

body::body(
	world& w,
	const float mass,
	btCollisionShape& shape,
	const btTransform& startTransform
)
	: m_world{ w }, m_motionState{ startTransform },
	m_rigidBody{ { mass, &m_motionState, &shape, [mass, &shape]() {
		btVector3 inertia{0,0,0};
		if (mass > std::numeric_limits<float>::epsilon())
			shape.calculateLocalInertia(mass, inertia);
		return inertia;
	}()} }
{
	m_world.add_body(*this);
}

body::body(
	world& w,
	const float mass,
	btCollisionShape& shape,
	const glm::vec3& startPosition
)
	: body{ w, mass, shape, [&startPosition]() {
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin({ startPosition.x, startPosition.y, startPosition.z });
		return startTransform;
	}() }
{}

body::body(
	world& w,
	btCollisionShape& shape,
	const btTransform& startTransform
)
	: body{ w, 0.0f, shape, startTransform }
{}

body::body(
	world& w,
	btCollisionShape& shape,
	const glm::vec3& startPosition
)
	: body{ w, 0.0f, shape, startPosition }
{}

body::~body() {
	m_world.remove_body(*this);
}

void body::constrain_movement(const bool x, const bool y, const bool z) {
	auto b2f = [](const bool b) { return b ? 1.0f : 0.0f; };
	m_rigidBody.setLinearFactor({ b2f(x), b2f(y), b2f(z) });
}

void body::constrain_rotation(const bool x, const bool y, const bool z) {
	auto b2f = [](const bool b) { return b ? 1.0f : 0.0f; };
	m_rigidBody.setAngularFactor({ b2f(x), b2f(y), b2f(z) });
}

glm::vec3 body::velocity() const {
	auto v = m_rigidBody.getLinearVelocity();
	return { v.x(), v.y(), v.z() };
}

void body::velocity(const glm::vec3& v) {
	m_rigidBody.activate(true);
	m_rigidBody.setLinearVelocity({ v.x, v.y, v.z });
}

glm::vec3 body::angular_velocity() const {
	auto v = m_rigidBody.getAngularVelocity();
	return { v.x(), v.y(), v.z() };
}

void body::angular_velocity(const glm::vec3& v) {
	m_rigidBody.activate(true);
	m_rigidBody.setAngularVelocity({ v.x, v.y, v.z });
}

void body::position(const glm::vec3& pos) {
	btTransform transform;
	m_rigidBody.getMotionState()->getWorldTransform(transform);
	transform.setOrigin({ pos.x, pos.y, pos.z });

	m_rigidBody.setWorldTransform(transform);
	m_rigidBody.getMotionState()->setWorldTransform(transform);
}

glm::vec3 body::position() const {
	btTransform transform;
	m_motionState.getWorldTransform(transform);
	const auto pos = transform.getOrigin();
	return { pos.x(), pos.y(), pos.z() };
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

float body::restitution() const {
	return static_cast<float>(m_rigidBody.getRestitution());
}

void body::restitution(const float r) {
	m_rigidBody.setRestitution(r);
}

}
