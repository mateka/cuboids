#pragma once

#include <cuboidslib/projectile_collider.h>
#include <cuboidslib/game.h>
#include <cuboidslib/rocket.h>


namespace cuboidslib {

/*! \brief Class for handling collisions with rocket and something. */
class rocket_collider : public projectile_collider {
public:
	/*! \brief Memorizes game and projectile objects.
	*   \param g game in which collision happened.
	*   \param r rocket colliding with some object. */
	rocket_collider(game& g, rocket& r);

	/*! \brief Visits projectile. */
	void on_visit(bullet&) override;

	/*! \brief Visits rocket. */
	void on_visit(rocket&) override {}

	/*! \brief Visits cuboid. */
	void on_visit(cuboid&) override;

	/*! \brief Visits crate. */
	void on_visit(crate&) override;

	/*! \brief Visits explosion. */
	void on_visit(explosion&) override;
private:
	rocket& colliding_rocket() const;

	void explode(rocket& r) const;
};

}

