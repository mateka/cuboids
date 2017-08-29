#pragma once

#include <cuboidslib/imutable_visitor.h>
#include <cuboidslib/game.h>
#include <cuboidslib/iprojectile.h>


namespace cuboidslib {

/*! \brief Class for handling collisions with projectile and something. */
class projectile_collider : public imutable_visitor {
public:
	/*! \brief Memorizes game and projectile objects. */
	projectile_collider(game& g, iprojectile& projectile);

	/*! \brief Visits ship. */
	void on_visit(moving_ship&) override {}

	/*! \brief Visits projectile. */
	void on_visit(bullet&) override {}

	/*! \brief Visits cuboid. */
	void on_visit(cuboid&) override;
private:
	game& m_game;
	iprojectile& m_projectile;
};

}

