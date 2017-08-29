#pragma once

#include <cuboidslib/imutable_visitor.h>
#include <cuboidslib/game.h>
#include <cuboidslib/iship.h>


namespace cuboidslib {

/*! \brief Class for handling collisions with ship and something. */
class ship_collider : public imutable_visitor {
public:
	/*! \brief Memorizes game and ship objects. */
	ship_collider(game& g, iship& ship);

	/*! \brief Visits ship. */
	void on_visit(moving_ship&) override {}

	/*! \brief Visits projectile. */
	void on_visit(bullet&) override {}

	/*! \brief Visits cuboid. */
	void on_visit(cuboid&) override;
private:
	game& m_game;
	iship& m_ship;
};

}

