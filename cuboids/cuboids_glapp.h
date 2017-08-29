#pragma once

#include <glapp/app.h>
#include <cuboids/game_painter.h>
#include <cuboidslib/game.h>
#include <cuboidslib/ship_factory.h>
#include <cuboidslib/cuboid_factory.h>
#include <memory>
#include <random>


namespace cuboids {

/*! \brief Cuboids app. */
class cuboids_glapp : public glapp::app {
public:
	/*! \brief Initializes OpenGL libraries, creates window
	*   and initializes game's objects.
	*   \param params window ang OpenGL context creation parameters. */
	explicit cuboids_glapp(const params_type& params);
protected:
	void update(const seconds delta) override;
private:
	void handle_input();
	std::unique_ptr<cuboidslib::cuboid_factory> cuboids_factory();
	std::unique_ptr<cuboidslib::game> new_game();

	const float m_gameSize;

	std::random_device m_randomness;
	cuboidslib::ship_factory m_shipFactory;
	std::unique_ptr<cuboidslib::game> m_game;
	game_painter m_painter;
	bool m_showFPS;
};

}
