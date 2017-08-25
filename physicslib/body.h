#pragma once

#include <physicslib/include_bullet.h>


namespace physicslib {

/*! \brief Base class for rigid bodies. */
class body {
public:
	/*! \brief Creates rigid body.
	*   \param world physical simulation world.
	*   \param mass mass of the body (0 - body is static).
	*   \param shape collision shape of the body.
	*   \param startTransform starting transform of the body. */
	body(
		btDiscreteDynamicsWorld& world,
		const float mass,
		btCollisionShape& shape,
		const btTransform& startTransform
	);

	/*! \brief Creates rigid body.
	*   \param world physical simulation world.
	*   \param mass mass of the body (0 - body is static).
	*   \param shape collision shape of the body.
	*   \param startPosition starting position of the body. */
	body(
		btDiscreteDynamicsWorld& world,
		const float mass,
		btCollisionShape& shape,
		const btVector3& startPosition
	);

	/*! \brief Creates static rigid body.
	*   \param world physical simulation world.
	*   \param shape collision shape of the body.
	*   \param startTransform starting transform of the body. */
	body(
		btDiscreteDynamicsWorld& world,
		btCollisionShape& shape,
		const btTransform& startTransform
	);

	/*! \brief Creates static rigid body.
	*   \param world physical simulation world.
	*   \param shape collision shape of the body.
	*   \param startPosition starting position of the body. */
	body(
		btDiscreteDynamicsWorld& world,
		btCollisionShape& shape,
		const btVector3& startPosition
	);

	virtual ~body();

	// move is disabled
	body(body&&) = delete;
	body& operator=(body&&) = delete;

	// copying is disabled
	body(const body&) = delete;
	body& operator=(const body&) = delete;
private:
	btDiscreteDynamicsWorld& m_world;
	btDefaultMotionState m_motionState;
	btRigidBody m_rigidBody;
};

}
