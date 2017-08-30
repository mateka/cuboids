#pragma once

#include <cuboidslib/iship.h>
#include <cuboidslib/iprojectile_factory.h>
#include <cuboidslib/default_gun.h>
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
	/*! \brief Creates ship, which slides left or right.
	*   \param w physics world in which bullet will be registered.
	*   \param size size of the ship.
	*   \param pos starting position of the ship.
	*   \param speed how fast ship can move. */
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
	void visit(imutable_visitor& v) override;

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(ivisitor& v) const override;

	/*! \brief Checks if object is alive (dead should be destroyed).
	*   \return true if object should stay in game. */
	bool alive() const override;

	/*! \brief Kills object. */
	void die() override;

	/*! \brief Obtains physics body from cuboid.
	*   \return Body associated with cuboid. */
	const physicslib::body* body() const override;

	/*! \brief Move ship to the left. */
	void left() override;

	/*! \brief Move ship to the right. */
	void right() override;

	/*! \brief Stops ship movement. */
	void stop() override;

	/*! \brief Shot.
	*   \param w physics world
	*   \return Collection of projectile objects. */
	std::vector<std::unique_ptr<iprojectile>> shot(physicslib::world& w) override;

	/*! \brief Changes ship's gun.
	*   \param gun new gun. */
	void change_gun(std::unique_ptr<iprojectile_factory> gun) override;

	/*! \brief Returns model matrix of the ship.
	*   \return Ship's body transform. */
	glm::mat4 transform() const;
private:
	default_gun m_defaultGun;
	std::unique_ptr<iprojectile_factory> m_fancyGun;
	iprojectile_factory* m_gun;
	std::unique_ptr<physicslib::box> m_body;
	glm::vec3 m_gunPosition;
	float m_speed;
	bool m_alive;
};

}