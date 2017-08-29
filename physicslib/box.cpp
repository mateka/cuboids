#include <physicslib/box.h>
#include <glm/gtc/matrix_transform.hpp>


namespace physicslib {

box::box(
	btDiscreteDynamicsWorld& world,
	const float mass,
	const btVector3& size,
	const btTransform& startTransform
)
	: box_shape_holder{ size },
	body { world, mass, m_shape, startTransform
}
{}

box::box(
	btDiscreteDynamicsWorld& world,
	const float mass,
	const btVector3& size,
	const btVector3& startPosition
)
	: box_shape_holder{ size },
	body{ world, mass, m_shape, startPosition }
{}

box::box(
	btDiscreteDynamicsWorld& world,
	const btVector3& size,
	const btTransform& startTransform
)
	: box{ world, 0.0f, size, startTransform }
{}

box::box(
	btDiscreteDynamicsWorld& world,
	const btVector3& size,
	const btVector3& startPosition
)
	: box{ world, 0.0f, size, startPosition }
{}

/*! \brief Calculates scale transform used on this box.
*   \return Box's scale transform. */
glm::mat4 box::scale() const {
	const auto sv = 2 * m_shape.getImplicitShapeDimensions();
	return glm::scale(glm::mat4(), glm::vec3{ sv.x(), sv.y(), sv.z() });
}

glm::mat4 box::transform() const {
	return body::transform() * scale();
}

namespace details {

box_shape_holder::box_shape_holder(const btVector3& size)
	: m_shape{ size }
{}

}

}
