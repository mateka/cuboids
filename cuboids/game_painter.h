#pragma once

#include <cuboidslib/ivisitor.h>
#include <cuboidslib/game.h>
#include <utils/seconds.h>
#include <painterslib/pyramids.h>
#include <painterslib/cuboids.h>


namespace cuboids {

/*! \brief Class for painting cuboids game. */
class game_painter : public cuboidslib::ivisitor {
public:
	/*! \brief Creates painter. */
	game_painter(
		const float worldSize,
		const std::size_t maxBullets,
		const std::size_t maxCuboids
	);

	/*! \brief Update painter's state.
	*   \param screenRatio window's dimensions ratio.
	*   \param delta time from last update. */
	void update(const float screenRatio, const utils::seconds delta);

	/*! \brief Paints whole game.
	*   \param game game to paint. */
	void paint(const cuboidslib::game& game);

	/*! \brief Visits moving ship. */
	void on_visit(const cuboidslib::moving_ship&) override;

	/*! \brief Visits bullet. */
	void on_visit(const cuboidslib::bullet&) override;

	/*! \brief Visits cuboid. */
	void on_visit(const cuboidslib::cuboid&) override;
private:
	// painters
	painterslib::pyramids m_shipPainter;
	painterslib::pyramids m_bulletsPainter;
	painterslib::cuboids m_cuboidsPainter;
	// cached instances to paint
	std::vector<painterslib::pyramids::instance> m_bullets;
	std::vector<painterslib::cuboids::instance> m_cuboids;
	// other
	glm::mat4 m_pv;
	float m_worldSize;
};

}
