#pragma once

#include <memory>
#include <functional>
#include <unordered_map>
#include <utils/seconds.h>
#include <physicslib/include_bullet.h>
#include <physicslib/box.h>


namespace physicslib {

/*! \brief Class for simple world for physics simulation. */
class world final {
public:
	/* \brief Type for collision callback. */
	using collision_callback = std::function<void (const body*, const body*)>;

	/*! \brief Creates simple physics world simulation.
	*   \brief cc collision callback
	*/
	world(collision_callback cc);

	// copying is disabled
	world(const world&) = delete;
	world& operator=(const world&) = delete;

	// moving is disabled
	world(world&&) = delete;
	world& operator=(world&&) = delete;

	/*! \brief Gets gravity in world.
	*   \return Gravity vector. */
	glm::vec3 gravity() const;

	/*! \brief Sets gravity in world.
	*   \param gv gravity vector. */
	void gravity(const glm::vec3& gv);

	/*! \brief Updates world state - steps simulaton.
	*   \param time step time.
	*   \param subSteps max number of simulation sub steps (default: 1) */
	void update(const utils::seconds time, const int subSteps = 1);

	/* \brief Adds physics body to simulation.
	*  \param b body to add.*/
	void add_body(body& b);

	/* \brief Removes physics body to simulation.
	*  \param b body to remove.*/
	void remove_body(body& b);

	/*! \brief Create dynamic rigid body with cuboid shape.
	*   \param mass mass of the box.
	*   \param size half extends of the box.
	*   \param startTransform starting transform of the box.
	*   \return Rigid body with cuboid shape. */
	std::unique_ptr<box> create_dynamic_box(
		const float mass,
		const glm::vec3& size,
		const btTransform& startTransform
	);

	/*! \brief Create dynamic rigid body with cuboid shape.
	*   \param mass mass of the box.
	*   \param size half extends of the box.
	*   \param startTransform starting position of the box.
	*   \return Rigid body with cuboid shape. */
	std::unique_ptr<box> create_dynamic_box(
		const float mass,
		const glm::vec3& size,
		const glm::vec3& startPosition
	);

	/*! \brief Create dynamic rigid body with cuboid shape.
	*   \param size half extends of the box.
	*   \param startTransform starting transform of the box.
	*   \return Rigid body with cuboid shape. */
	std::unique_ptr<box> create_static_box(
		const glm::vec3& size, const btTransform& startTransform
	);
	/*! \brief Create dynamic rigid body with cuboid shape.
	*   \param size half extends of the box.
	*   \param startTransform starting position of the box.
	*   \return Rigid body with cuboid shape. */
	std::unique_ptr<box> create_static_box(
		const glm::vec3& size, const glm::vec3& startPosition
	);
private:
	btDefaultCollisionConfiguration m_collisionConfiguration;
	btCollisionDispatcher m_collisionDispatcher;
	btDbvtBroadphase m_broadPhaseAlgorithm;
	btSequentialImpulseConstraintSolver m_solver;
	btDiscreteDynamicsWorld m_worldSimulation;
	std::unordered_map<const btCollisionObject*, body*> m_bodies;
	collision_callback m_collisionCallback;
};

}
