#pragma once

#include <cuboidslib/iprojectile_factory.h>
#include <cuboidslib/default_gun.h>
#include <array>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Two guns on wings. */
class wingman : public iprojectile_factory {
public:
	/*! \brief Creates gun, which shots 2 simple bullets with given cooldown.
	*   \param cooldown cooldown between two shots.
	*   \param ammo number of shots before gun will be jammed. */
	wingman(
		const seconds& cooldown,
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
	std::array<default_gun, 2> m_guns;
	std::size_t m_ammo;
};

}
#pragma once
