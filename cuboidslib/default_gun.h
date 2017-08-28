#pragma once

#include <cuboidslib/iprojectile_factory.h>
#include <utils/cooldown_timer.h>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Default gun. */
class default_gun : public iprojectile_factory {
public:
	/*! \brief Creates gun, which shots simple bullets with given cooldown.
	*   \param cooldown cooldown between two shots. */
	default_gun(const seconds& cooldown);

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override;

	/*! \brief Collection of projectile objects.
	*   \param w physics world.
	*   \param pos starting position of bullets. */
	std::vector<std::unique_ptr<iprojectile>> create(physicslib::world& w, const glm::vec3& pos) override;
private:
	utils::cooldown_timer m_cooldown;
};

}
