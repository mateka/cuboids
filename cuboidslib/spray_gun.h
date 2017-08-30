#pragma once

#include <cuboidslib/iprojectile_factory.h>
#include <cuboidslib/default_gun.h>
#include <vector>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Default gun. */
class spray_gun : public iprojectile_factory {
public:
	/*! \brief Creates gun, which shots n simple bullets with given cooldown.
	*   \param cooldown cooldown between two shots.
	*   \param n number of created bullets.
	*   \param ammo number of shots before gun will be jammed. */
	spray_gun(
		const seconds& cooldown,
		const std::size_t n,
		const std::size_t ammo
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
	std::vector<default_gun> m_guns;
	std::size_t m_ammo;
};

}
#pragma once
