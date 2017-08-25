#pragma once

#include <physicslib/include_bullet.h>
#include <physicslib/body.h>


namespace physicslib {

namespace details {

/*! \brief Helper class for storing box shape.
*   Thanks to order in inheritance, member shape
*   can be used in construction of body base class. */
class box_shape_holder {
public:
	/*! \brief Creates box shape.
	*   \param size half extends of the box.*/
	box_shape_holder(const btVector3& size);

	virtual ~box_shape_holder() {}
protected:
	btBoxShape m_shape;
};

}

/*! \brief Rigid body with cuboid shape. */
class box : private details::box_shape_holder, public body {
public:
	/*! \brief Creates dynamic box.
	*   \param world physical simulation world.
	*   \param mass mass of the box.
	*   \param size half extends of the box.
	*   \param startTransform starting transform of the box.*/
	box(
		btDiscreteDynamicsWorld& world,
		const float mass,
		const btVector3& size,
		const btTransform& startTransform
	);

	/*! \brief Creates dynamic box.
	*   \param world physical simulation world.
	*   \param mass mass of the box.
	*   \param size half extends of the box.
	*   \param startTransform starting position of the box.*/
	box(
		btDiscreteDynamicsWorld& world,
		const float mass,
		const btVector3& size,
		const btVector3& startPosition
	);

	/*! \brief Creates static box.
	*   \param world physical simulation world.
	*   \param size half extends of the box.
	*   \param startTransform starting transform of the box.*/
	box(
		btDiscreteDynamicsWorld& world,
		const btVector3& size,
		const btTransform& startTransform
	);

	/*! \brief Creates static box.
	*   \param world physical simulation world.
	*   \param size half extends of the box.
	*   \param startTransform starting position of the box.*/
	box(
		btDiscreteDynamicsWorld& world,
		const btVector3& size,
		const btVector3& startPosition
	);
private:
	friend class world;
};

}