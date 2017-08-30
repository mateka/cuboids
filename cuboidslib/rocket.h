#pragma once

#include <cuboidslib/bullet.h>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Simple rocket */
class rocket : public bullet {
public:
	/*! \brief Creates rocket.
	*   \param w physics world in which bullet will be registered.
	*   \param pos starting position of the bullet.
	*   \param velocity linear velocity of the bullet.
	*   \param lifeSpan how long bullet will live.
	*   \param size size of the bullet (default: 1.0f). */
	rocket(
		physicslib::world& w,
		const glm::vec3& pos,
		const glm::vec3& velocity,
		const seconds lifeSpan,
		const float size = 1.0f
	);

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(imutable_visitor& v) override;

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(ivisitor& v) const override;
};

}
