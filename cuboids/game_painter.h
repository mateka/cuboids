#pragma once

#include <cuboidslib/ivisitor.h>
#include <cuboidslib/game.h>
#include <utils/seconds.h>
#include <glapp/resolution.h>
#include <painterslib/pyramids.h>


namespace cuboids {

/*! \brief Class for painting cuboids game. */
class game_painter : public cuboidslib::ivisitor {
public:
	/*! \brief Creates painter. */
	game_painter(const float worldSize);

	/*! \brief Update painter's state.
	*   \param res windows resolution.
	*   \param delta time from last update. */
	void update(const glapp::resolution& res, const utils::seconds delta);

	/*! \brief Paints whole game.
	*   \param game game to paint. */
	void paint(const cuboidslib::game& game);

	/*! \brief Visits moving ship. */
	void on_visit(const cuboidslib::moving_ship&) override;
private:
	painterslib::pyramids m_shipPainter;
	glm::mat4 m_pv;
	float m_worldSize;
};

}
