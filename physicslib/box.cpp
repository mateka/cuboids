#include <physicslib/box.h>
#include <physicslib/world.h>
#include <glm/gtc/matrix_transform.hpp>


namespace physicslib {

box::box(
	world& w,
	const float mass,
	const glm::vec3& size,
	const btTransform& startTransform
)
	: box_shape_holder{ size },
	body { w, mass, m_shape, startTransform }
{}

box::box(
	world& w,
	const float mass,
	const glm::vec3& size,
	const glm::vec3& startPosition
)
	: box_shape_holder{ size },
	body{ w, mass, m_shape, startPosition }
{}

box::box(
	world& w,
	const glm::vec3& size,
	const btTransform& startTransform
)
	: box{ w, 0.0f, size, startTransform }
{}

box::box(
	world& w,
	const glm::vec3& size,
	const glm::vec3& startPosition
)
	: box{ w, 0.0f, size, startPosition }
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

box_shape_holder::box_shape_holder(const glm::vec3& size)
	: m_shape{ {size.x, size.y, size.z} }
{}

}

}
