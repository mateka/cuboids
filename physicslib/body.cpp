#include <physicslib/body.h>
#include <limits>


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
		if(mass > std::numeric_limits<float>::epsilon())
			shape.calculateLocalInertia(mass, inertia);
		return inertia;
	}() } }
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
		startTransform.setOrigin(btVector3(2, 10, 0));
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

}
