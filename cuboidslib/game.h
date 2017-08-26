#pragma once

#include <array>
#include <cuboidslib/icuboid_object.h>
#include <cuboidslib/iship.h>
#include <cuboidslib/iship_factory.h>
#include <physicslib/world.h>


namespace cuboidslib {

/*! \brief Class for cuboids game. */
class game final : public icuboid_object {
public:
	game(const float worldSize, iship_factory& ship_factory);

	// movingis disabled
	game(game&&) = delete;
	game& operator=(game&&) = delete;

	// copying is disabled
	game(const game&) = delete;
	game& operator=(const game&) = delete;

	/*! \brief Game world size accessor.
	*   \return Game world size.*/
	float worldSize() const;

	/*! \brief Move ship to the left. */
	void left();

	/*! \brief Move ship to the right. */
	void right();

	/*! \brief Shot. */
	void shot();

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override;

	/*! \brief Visits game world.
	*   \param v visitor object. */
	void visit(ivisitor& v) const override;
private:
	physicslib::world m_world;
	std::array<std::unique_ptr<physicslib::box>, 2> m_walls;
	std::unique_ptr<iship> m_player;
	float m_worldSize;
};

}
#pragma once
