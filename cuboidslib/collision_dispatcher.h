#pragma once

#include <cuboidslib/imutable_visitor.h>
#include <cuboidslib/game.h>


namespace cuboidslib {

/*! \brief Class for dispatching collisions to proper visitors. */
class collision_dispatcher : public imutable_visitor {
public:
	/*! \brief Memorizes game and other object.
	*   \param g game in which collision happened.
	*   \param other other object colliding with some object.*/
	collision_dispatcher(game& g, icuboid_object& other);

	/*! \brief Visits ship. */
	void on_visit(moving_ship&) override;

	/*! \brief Visits projectile. */
	void on_visit(bullet&) override;

	/*! \brief Visits projectile. */
	void on_visit(rocket&) override;

	/*! \brief Visits cuboid. */
	void on_visit(cuboid&) override;

	/*! \brief Visits crate. */
	void on_visit(crate&) override;

	/*! \brief Visits explosion. */
	void on_visit(explosion&) override;
private:
	game& m_game;
	icuboid_object& m_other;
};

}
