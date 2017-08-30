#pragma once

#include <cuboidslib/iprojectile_factory.h>
#include <cuboidslib/default_gun.h>
#include <vector>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Spray gun. */
template<typename BulletType, typename JammingPolicy>
class spray_gun : public iprojectile_factory {
public:
	using type = BulletType;	//!< Type of bullets
	using jamming_policy = JammingPolicy;	//!< Type of jamming policy

	/*! \brief Creates gun, which shots n simple bullets with given cooldown.
	*   \param cooldown cooldown between two shots.
	*   \param n number of created bullets.
	*   \param jammingPolicy jamming policy. */
	spray_gun(
		const seconds& cooldown,
		const std::size_t n,
		jamming_policy jammingPolicy
	)
		: m_jamming{ jammingPolicy }
	{
		for (std::size_t i = 0; i < n; ++i) {
			const auto x = (i - 0.5f * n) * 0.3;
			m_guns.emplace_back(
				cooldown, glm::vec3{ x, 0, -4.0f },
				3s, 0.75f, jamming::no_jam{}
			);
		}
	}

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
		std::vector<std::unique_ptr<iprojectile>> result;
		for (auto& g : m_guns) {
			auto bullets = g.create(w, pos);
			std::move(
				std::begin(bullets), std::end(bullets),
				std::back_inserter(result)
			);
		}
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

	std::vector<gun_type> m_guns;
	jamming_policy m_jamming;
};

}
#pragma once
