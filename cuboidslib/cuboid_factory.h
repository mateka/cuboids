#pragma once

#include <cuboidslib/icuboid_factory.h>
#include <utils/cooldown_timer.h>
#include <random>


namespace cuboidslib {

/*! \brief Cuboids factory */
class cuboid_factory : public icuboid_factory {
public:
	/*! \brief Creates default cuboids factory.
	*   \param seed seed for random number generator engine.
	*   \param cooldown time between generating waves of cuboids.
	*   \param worldSize size of world in which cuboids will be generated.
	*   \param how many additional cuboids will be spawned for each cuboid,
	*   which was killed by player.
	*   \param crateProbability probability of dropping crate instead of cuboid. */
	cuboid_factory(
		const std::mt19937_64::result_type seed,
		const seconds& cooldown,
		const float worldSize,
		const float killPenalty,
		const float crateProbability
	);

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override;

	/*! \brief Collection of cuboid objects.
	*   \param w physics world.
	*   \param pos starting position of bullets. */
	std::vector<std::unique_ptr<icuboid>> create(physicslib::world& w) override;

	/*! \brief Notify factory, that player killed one cuboid. */
	void on_killed() override;
private:
	std::unique_ptr<icuboid> new_cuboid(physicslib::world& w, const glm::vec3& pos);
	std::unique_ptr<icuboid> new_crate(physicslib::world& w, const glm::vec3& pos);

	utils::cooldown_timer m_cooldown;
	std::mt19937_64 m_engine;
	std::uniform_real_distribution<float> m_pos;
	std::uniform_real_distribution<float> m_size;
	std::uniform_real_distribution<float> m_velocity;
	std::uniform_real_distribution<float> m_rotation;
	std::uniform_real_distribution<float> m_crateDistribution;
	std::uniform_real_distribution<float> m_gunsDistribution;
	float m_killPenalty;
	float m_additional;
	float m_crateProbability;
};

}
