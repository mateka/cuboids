#pragma once

#include <cuboidslib/iship.h>
#include <physicslib/box.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Moving ship class */
class moving_ship : public iship {
public:
	moving_ship(
		physicslib::world& w,
		const float size,
		const glm::vec3& pos,
		const float speed
	);

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override;

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(ivisitor& v) const override;

	/*! \brief Move ship to the left. */
	void left() override;

	/*! \brief Move ship to the right. */
	void right() override;

	/*! \brief Shot.
	*   \return Projectile object. */
	std::unique_ptr<iprojectile> shot() override;

	/*! \brief Ship's size accessor.
	*   \return Size of the ship. */
	float size() const;

	/*! \brief Returns model matrix of the ship.
	*   \return Ship's body transform. */
	glm::mat4 transform() const;
private:
	std::unique_ptr<physicslib::box> m_body;
	float m_size;
	float m_speed;
};

}