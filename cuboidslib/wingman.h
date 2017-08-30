#pragma once

#include <cuboidslib/iprojectile_factory.h>
#include <cuboidslib/default_gun.h>
#include <array>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Two guns on wings. */
template<typename BulletType, typename JammingPolicy>
class wingman : public iprojectile_factory {
public:
	using type = BulletType;	//!< Type of bullets
	using jamming_policy = JammingPolicy;	//!< Type of jamming policy

	/*! \brief Creates gun, which shots 2 simple bullets with given cooldown.
	*   \param cooldown cooldown between two shots.
	*   \param jammingPolicy jamming policy. */
	wingman(
		const seconds& cooldown,
		jamming_policy jammingPolicy
	)
		: m_guns{
			gun_type{ cooldown, glm::vec3{ 0, 0, -7.0f }, 2s, 0.5f, jamming::no_jam{} },
			gun_type{ cooldown, glm::vec3{ 0, 0, -7.0f }, 2s, 0.5f, jamming::no_jam{} }
		}, m_jamming{ jammingPolicy }
	{}

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override {
		for (auto& g : m_guns)
			g.update(delta);
		m_jamming.update(delta);
	}

	/*! \brief Collection of projectile objects.
	*   \param w physics world.
	*   \param pos starting position of bullets. */
	std::vector<std::unique_ptr<iprojectile>>
		create(physicslib::world& w, const glm::vec3& pos) override {
		auto left = m_guns[0].create(w, pos - glm::vec3{ 0.25, 0, 0 });
		auto right = m_guns[1].create(w, pos + glm::vec3{ 0.25, 0, 0 });

		std::vector<std::unique_ptr<iprojectile>> result;
		std::move(
			std::begin(left), std::end(left),
			std::back_inserter(result)
		);
		std::move(
			std::begin(right), std::end(right),
			std::back_inserter(result)
		);
		m_jamming.on_shot(result);
		return result;
	}

	/*! \brief Check if gun is still working.
	*   \return false, if player can shoot from this gun. */
	bool jammed() const override {
		return m_jamming.jammed();
	}
private:
	using gun_type = launcher<BulletType, jamming::no_jam>;
	
	std::array<gun_type, 2> m_guns;
	jamming_policy m_jamming;
};

}
#pragma once
