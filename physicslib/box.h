#pragma once

#include <physicslib/include_bullet.h>
#include <physicslib/body.h>
#include <glm/mat4x4.hpp>


namespace physicslib {

class world;

namespace details {

/*! \brief Helper class for storing box shape.
*   Thanks to order in inheritance, member shape
*   can be used in construction of body base class. */
class box_shape_holder {
public:
	/*! \brief Creates box shape.
	*   \param size half extends of the box.*/
	box_shape_holder(const glm::vec3& size);

	virtual ~box_shape_holder() {}
protected:
	btBoxShape m_shape;
};

}

/*! \brief Rigid body with cuboid shape. */
class box : private details::box_shape_holder, public body {
public:
	/*! \brief Creates dynamic box.
	*   \param w physical simulation world.
	*   \param mass mass of the box.
	*   \param size half extends of the box.
	*   \param startTransform starting transform of the box.*/
	box(
		world& w,
		const float mass,
		const glm::vec3& size,
		const btTransform& startTransform
	);

	/*! \brief Creates dynamic box.
	*   \param w physical simulation world.
	*   \param mass mass of the box.
	*   \param size half extends of the box.
	*   \param startTransform starting position of the box.*/
	box(
		world& w,
		const float mass,
		const glm::vec3& size,
		const glm::vec3& startPosition
	);

	/*! \brief Creates static box.
	*   \param w physical simulation world.
	*   \param size half extends of the box.
	*   \param startTransform starting transform of the box.*/
	box(
		world& w,
		const glm::vec3& size,
		const btTransform& startTransform
	);

	/*! \brief Creates static box.
	*   \param w physical simulation world.
	*   \param size half extends of the box.
	*   \param startTransform starting position of the box.*/
	box(
		world& w,
		const glm::vec3& size,
		const glm::vec3& startPosition
	);

	/*! \brief Calculates scale transform used on this box.
	*   \return Box's scale transform. */
	glm::mat4 scale() const;

	/*! \brief Returns transform matrix of the body.
	*   \return Body's transform. */
	glm::mat4 transform() const override;
private:
	friend class world;
};

}
