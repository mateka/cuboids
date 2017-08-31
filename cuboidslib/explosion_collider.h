#pragma once

#include <cuboidslib/imutable_visitor.h>
#include <cuboidslib/game.h>
#include <cuboidslib/explosion.h>


namespace cuboidslib {

/*! \brief Class for handling collisions with explosion and something. */
class explosion_collider : public imutable_visitor {
public:
	/*! \brief Memorizes game and explosion objects.
	*   \param g game in which collision happened.
	*   \param e explosion colliding with some object. */
	explosion_collider(game& g, explosion& e);

	/*! \brief Visits ship. */
	void on_visit(moving_ship&) override {}

	/*! \brief Visits projectile. */
	void on_visit(bullet&) override;

	/*! \brief Visits rocket. */
	void on_visit(rocket&) override;

	/*! \brief Visits cuboid. */
	void on_visit(cuboid&) override;

	/*! \brief Visits crate. */
	void on_visit(crate&) override;

	/*! \brief Visits explosion. */
	void on_visit(explosion&) override {}
private:
	game& m_game;
	explosion& m_explosion;
};

}

