#pragma once

#include <physicslib/include_bullet.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>


namespace physicslib {

class world;

/*! \brief Base class for rigid bodies. */
class body {
public:
	/*! \brief Creates rigid body.
	*   \param w physical simulation world.
	*   \param mass mass of the body (0 - body is static).
	*   \param shape collision shape of the body.
	*   \param startTransform starting transform of the body. */
	body(
		world& w,
		const float mass,
		btCollisionShape& shape,
		const btTransform& startTransform
	);

	/*! \brief Creates rigid body.
	*   \param w physical simulation world.
	*   \param mass mass of the body (0 - body is static).
	*   \param shape collision shape of the body.
	*   \param startPosition starting position of the body. */
	body(
		world& w,
		const float mass,
		btCollisionShape& shape,
		const glm::vec3& startPosition
	);

	/*! \brief Creates static rigid body.
	*   \param w physical simulation world.
	*   \param shape collision shape of the body.
	*   \param startTransform starting transform of the body. */
	body(
		world& w,
		btCollisionShape& shape,
		const btTransform& startTransform
	);

	/*! \brief Creates static rigid body.
	*   \param w physical simulation world.
	*   \param shape collision shape of the body.
	*   \param startPosition starting position of the body. */
	body(
		world& w,
		btCollisionShape& shape,
		const glm::vec3& startPosition
	);

	virtual ~body();

	// move is disabled
	body(body&&) = delete;
	body& operator=(body&&) = delete;

	// copying is disabled
	body(const body&) = delete;
	body& operator=(const body&) = delete;

	/*! \brief Constrains axis movement.
	*   \param x switch, whether allow movement on x axis.
	*   \param y switch, whether allow movement on y axis.
	*   \param z switch, whether allow movement on z axis.*/
	void constrain_movement(const bool x, const bool y, const bool z);

	/*! \brief Constrains axis rotation.
	*   \param x switch, whether allow rotation on x axis.
	*   \param y switch, whether allow rotation on y axis.
	*   \param z switch, whether allow rotation on z axis.*/
	void constrain_rotation(const bool x, const bool y, const bool z);

	/*! \brief Linear velocity accessor.
	*   \return Linear velocity of the body. */
	glm::vec3 velocity() const;

	/*! \brief Linear velocity setter.
	*   \param v linear velocity of the body. */
	void velocity(const glm::vec3& v);

	/*! \brief Angular velocity accessor.
	*   \return Angular velocity of the body. */
	glm::vec3 angular_velocity() const;

	/*! \brief Angular velocity setter.
	*   \param v angular velocity of the body. */
	void angular_velocity(const glm::vec3& v);

	/*! \brief Sets body's position.
	*   \param pos body's position. */
	void position(const glm::vec3& pos);

	/*! \brief Returns body's position.
	*   \return Body's position. */
	glm::vec3 position() const;

	/*! \brief Returns transform matrix of the body.
	*   \return Body's transform. */
	virtual glm::mat4 transform() const;

	/*! \brief Restitution accessor.
	*   \return Restitution of the body. */
	float restitution() const;

	/*! \brief Restitution setter.
	*   \param v restitution of the body. */
	void restitution(const float r);
private:
	friend class world;

	world& m_world;
	btDefaultMotionState m_motionState;
	btRigidBody m_rigidBody;
};

}
