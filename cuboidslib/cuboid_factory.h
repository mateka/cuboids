#pragma once

#include <cuboidslib/icuboid_factory.h>
#include <utils/cooldown_timer.h>


namespace cuboidslib {

/*! \brief Cuboids factory */
class cuboid_factory : public icuboid_factory {
public:
	cuboid_factory(const seconds& cooldown);

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override;

	/*! \brief Collection of cuboid objects.
	*   \param w physics world.
	*   \param pos starting position of bullets. */
	std::vector<std::unique_ptr<icuboid>> create(physicslib::world& w) override;
private:
	utils::cooldown_timer m_cooldown;
};

}
