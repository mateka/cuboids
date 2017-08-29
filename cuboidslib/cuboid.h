#pragma once

#include <cuboidslib/icuboid.h>
#include <physicslib/box.h>
#include <memory>


namespace cuboidslib {

/*! \brief Cuboid object */
class cuboid : public icuboid {
public:
	/*! \brief Creates cuboid. */
	cuboid(
		physicslib::world& w,
		const glm::vec3& pos,
		const glm::vec3& velocity,
		const glm::vec3& scale,
		const glm::vec3& rotation
	);

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override;

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(ivisitor& v) const override;

	/*! \brief Test if cuboid is alive.
	*   \return true if cuboid is on game screen.*/
	bool alive() const override;

	/*! \brief Returns model matrix of the ship.
	*   \return Ship's body transform. */
	glm::mat4 transform() const;
private:
	std::unique_ptr<physicslib::box> m_body;
};

}
