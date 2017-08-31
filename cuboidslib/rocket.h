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
	*   \param ex explosive object, which can explode.
	*   \param pos starting position of the bullet.
	*   \param velocity linear velocity of the bullet.
	*   \param lifeSpan how long bullet will live.
	*   \param size size of the bullet (default: 1.0f). */
	rocket(
		physicslib::world& w,
		iexplosive& ex,
		const glm::vec3& pos,
		const glm::vec3& velocity,
		const seconds lifeSpan,
		const float size = 1.0f
	);

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override;

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(imutable_visitor& v) override;

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(ivisitor& v) const override;

	/*! \brief Rocket's size getter.
	*   \return Size of the rocket. */
	float size() const;
private:
	float m_size;
};

}
