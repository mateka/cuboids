#pragma once

#include <cuboidslib/iprojectile_factory.h>
#include <cuboidslib/jamming_policies.h>
#include <utils/cooldown_timer.h>
#include <physicslib/world.h>
#include <chrono>


namespace cuboidslib {

/*! \brief Template for simple launcher gun. */
template<typename BulletType, typename JammingPolicy = jamming::no_jam>
class launcher : public iprojectile_factory {
public:
	using type = BulletType;	//!< Type of bullets
	using jamming_policy = JammingPolicy;	//!< Type of jamming policy

	/*! \brief Creates gun, which shots simple bullets with given cooldown.
	*   \param cooldown cooldown between two shots.
	*   \param velocity velocity of bullets.
	*   \param lifetime lifetime of bullets.
	*   \param size size of bullets.
	*   \param jammingPolicy jamming policy. */
	launcher(
		const seconds& cooldown,
		const glm::vec3& velocity,
		const seconds& lifetime,
		const float size,
		jamming_policy jammingPolicy
	)
		: m_jamming{ jammingPolicy },
		m_cooldown(std::chrono::duration_cast<std::chrono::nanoseconds>(cooldown)),
		m_velocity{ velocity }, m_lifetime{ lifetime }, m_size{ size }
	{}

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override {
		m_cooldown.update(std::chrono::duration_cast<std::chrono::nanoseconds>(delta));
		m_jamming.update(delta);
	}

	/*! \brief Collection of projectile objects.
	*   \param w physics world.
	*   \param pos starting position of bullets.
	*   \param ex explosive object, which can explode. */
	std::vector<std::unique_ptr<iprojectile>> create(
		physicslib::world& w,
		const glm::vec3& pos,
		iexplosive& ex
	) override {
		std::vector<std::unique_ptr<iprojectile>> result;
		m_cooldown.execute([this, &result, &w, &pos, &ex]() {
			result.push_back(std::make_unique<type>(
				w, ex, pos, m_velocity, m_lifetime, m_size
			));
		});
		m_jamming.on_shot(result);
		return result;
	}

	/*! \brief Check if gun is still working.
	*   \return false, if player can shoot from this gun. */
	bool jammed() const override {
		return m_jamming.jammed();
	}
private:
	jamming_policy m_jamming;
	utils::cooldown_timer m_cooldown;
	glm::vec3 m_velocity;
	seconds m_lifetime;
	float m_size;
};

}
