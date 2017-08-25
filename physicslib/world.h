#pragma once

#include <memory>
#include <physicslib/include_bullet.h>
#include <physicslib/box.h>


namespace physicslib {

/*! \brief Class for simple world for physics simulation. */
class world final {
public:
	/*! \brief Creates simple physics world simulation. */
	world();

	// copying is disabled
	world(const world&) = delete;
	world& operator=(const world&) = delete;

	// moving is disabled
	world(world&&) = delete;
	world& operator=(world&&) = delete;

	/*! \brief Gets gravity in world.
	*   \return Gravity vector. */
	btVector3 gravity() const;

	/*! \brief Sets gravity in world.
	*   \param gv gravity vector. */
	void gravity(const btVector3& gv);

	/*! \brief Create dynamic rigid body with cuboid shape.
	*   \param mass mass of the box.
	*   \param size half extends of the box.
	*   \param startTransform starting transform of the box.
	*   \return Rigid body with cuboid shape. */
	std::unique_ptr<box> create_dynamic_box(
		const float mass,
		const btVector3& size,
		const btTransform& startTransform
	);

	/*! \brief Create dynamic rigid body with cuboid shape.
	*   \param mass mass of the box.
	*   \param size half extends of the box.
	*   \param startTransform starting position of the box.
	*   \return Rigid body with cuboid shape. */
	std::unique_ptr<box> create_dynamic_box(
		const float mass,
		const btVector3& size,
		const btVector3& startPosition
	);

	/*! \brief Create dynamic rigid body with cuboid shape.
	*   \param size half extends of the box.
	*   \param startTransform starting transform of the box.
	*   \return Rigid body with cuboid shape. */
	std::unique_ptr<box> create_static_box(
		const btVector3& size, const btTransform& startTransform
	);
	/*! \brief Create dynamic rigid body with cuboid shape.
	*   \param size half extends of the box.
	*   \param startTransform starting position of the box.
	*   \return Rigid body with cuboid shape. */
	std::unique_ptr<box> create_static_box(
		const btVector3& size, const btVector3& startPosition
	);
private:
	btDefaultCollisionConfiguration m_collisionConfiguration;
	btCollisionDispatcher m_collisionDispatcher;
	btDbvtBroadphase m_broadPhaseAlgorithm;
	btSequentialImpulseConstraintSolver m_solver;
	btDiscreteDynamicsWorld m_worldSimulation;
};

}