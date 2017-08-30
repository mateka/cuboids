#pragma once

#include <cuboidslib/imutable_visitor.h>
#include <cuboidslib/game.h>
#include <cuboidslib/icuboid.h>


namespace cuboidslib {

/*! \brief Class for handling collisions with cuboid and something. */
class cuboid_collider : public imutable_visitor {
public:
	/*! \brief Memorizes game and cuboid objects.
	*   \param g game in which collision happened.
	*   \param c cuboid colliding with some object.*/
	cuboid_collider(game& g, icuboid& c);

	/*! \brief Visits ship. */
	void on_visit(moving_ship&) override;

	/*! \brief Visits projectile. */
	void on_visit(bullet&) override;

	/*! \brief Visits projectile. */
	void on_visit(rocket&) override;

	/*! \brief Visits cuboid. */
	void on_visit(cuboid&) override {}

	/*! \brief Visits crate. */
	void on_visit(crate&) override {}
private:
	game& m_game;
	icuboid& m_cuboid;
};

}

