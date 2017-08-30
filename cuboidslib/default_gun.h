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
	*   \param cooldown cooldown between two shots.
	*   \param velocity velocity of bullets (default: { 0, 0, -5.0f }).
	*   \param lifetime lifetime of bullets (default: 2s).
	*   \param size size of bullets (default: 1). */
	default_gun(
		const seconds& cooldown,
		const glm::vec3& velocity = glm::vec3{ 0, 0, -5.0f },
		const seconds& lifetime = seconds{2},
		const float size = 1.0f
	);

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override;

	/*! \brief Collection of projectile objects.
	*   \param w physics world.
	*   \param pos starting position of bullets. */
	std::vector<std::unique_ptr<iprojectile>> create(physicslib::world& w, const glm::vec3& pos) override;

	/*! \brief Check if gun is still working.
	*   \return false, if player can shoot from this gun. */
	bool jammed() const override;
private:
	utils::cooldown_timer m_cooldown;
	glm::vec3 m_velocity;
	seconds m_lifetime;
	float m_size;
};

}
