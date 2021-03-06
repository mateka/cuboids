#pragma once

#include <array>
#include <vector>
#include <unordered_map>
#include <cuboidslib/iship.h>
#include <cuboidslib/iprojectile.h>
#include <cuboidslib/iship_factory.h>
#include <cuboidslib/icuboid_factory.h>
#include <cuboidslib/explosion.h>
#include <cuboidslib/iexplosive.h>
#include <physicslib/world.h>
#include <physicslib/body.h>


namespace cuboidslib {

/*! \brief Class for cuboids game. */
class game final : public iexplosive {
public:
	/*! \brief Creates new game.
	*   \param worldSize size of the world simulation.
	*   \param ship_factory object for creating new ship.
	*   \param cuboids_factory object for creating new cuboids.
	*   \param maxBullets how many bullets can be in the simulation.
	*   \param maxCuboids how many cuboids can be in the simulation.
	*   \param maxExplosions how many explosions can be in the simulation. */
	game(
		const float worldSize,
		iship_factory& ship_factory,
		std::unique_ptr<icuboid_factory> cuboids_factory,
		const std::size_t maxBullets,
		const std::size_t maxCuboids,
		const std::size_t maxExplosions
	);

	// moving is disabled
	game(game&&) = delete;
	game& operator=(game&&) = delete;

	// copying is disabled
	game(const game&) = delete;
	game& operator=(const game&) = delete;

	/*! \brief Game world size accessor.
	*   \return Game world size.*/
	float world_size() const;

	/*! \brief Max count of bullets accessor.
	*   \return Max count of bullets.*/
	std::size_t max_bullets() const;

	/*! \brief Max count of cuboids accessor.
	*   \return Max count of cuboids.*/
	std::size_t max_cuboids() const;

	/*! \brief Max count of explosions accessor.
	*   \return Max count of explosions.*/
	std::size_t max_explosions() const;

	/*! \brief Test if game is still playable.
	*   \return true if player has not collided with cuboid. */
	bool playable() const;

	/*! \brief Move ship to the left. */
	void left();

	/*! \brief Move ship to the right. */
	void right();

	/*! \brief Stops player movement. */
	void stop();

	/*! \brief Shot. */
	void shot();

	/*! \brief Create explosion.
	*   \param pos position of the explosion.
	*   \param size size of the explosion. */
	void explode(const glm::vec3& pos, const float size) override;

	/*! \brief Update object state.
	*   \param screenRatio window's dimensions ratio.
	*   \param delta time from last update. */
	void update(const float screenRatio, const seconds delta);

	/*! \brief Visits game world.
	*   \param v visitor object. */
	void visit(ivisitor& v) const;

	/*! \brief Notify game, that player killed one cuboid. */
	void on_cuboid_killed();
private:
	physicslib::world m_world;
	std::array<std::unique_ptr<physicslib::box>, 2> m_walls;
	std::unique_ptr<iship> m_player;
	std::unique_ptr<icuboid_factory> m_cuboidsFactory;
	std::vector<std::unique_ptr<iprojectile>> m_bullets;
	std::vector<std::unique_ptr<icuboid>> m_cuboids;
	std::vector<std::unique_ptr<explosion>> m_explosions;
	std::unordered_map<const physicslib::body*, icuboid_object*> m_objects;
	float m_worldSize;
	std::size_t m_maxBullets;
	std::size_t m_maxCuboids;
	std::size_t m_maxExplosions;
};

}
