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
	: box_shape_holder{ {0.5f, 0.5f, 0.5f} },
	body { w, mass, m_shape, startTransform }
{
	scale(size);
}

box::box(
	world& w,
	const float mass,
	const glm::vec3& size,
	const glm::vec3& startPosition
)
	: box_shape_holder{ { 0.5f, 0.5f, 0.5f } },
	body{ w, mass, m_shape, startPosition }
{
	scale(size);
}

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

namespace details {

box_shape_holder::box_shape_holder(const glm::vec3& size)
	: m_shape{ {size.x, size.y, size.z} }
{}

}

}
