#include <physicslib/box.h>


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

namespace details {

box_shape_holder::box_shape_holder(const btVector3& size)
	: m_shape{ size }
{}

}

}
