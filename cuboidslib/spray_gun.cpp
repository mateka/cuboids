#include <cuboidslib/spray_gun.h>
#include <physicslib/world.h>
#include <cuboidslib/bullet.h>
#include <chrono>


using namespace std::chrono_literals;

namespace cuboidslib {

spray_gun::spray_gun(
	const seconds& cooldown,
	const std::size_t n,
	const std::size_t ammo
)
	: m_ammo{ ammo }
{
	for (std::size_t i = 0; i < n; ++i) {
		const auto x = (i - 0.5f * n) * 0.3;
		m_guns.emplace_back(cooldown, glm::vec3{ x, 0, -4.0f }, 3s, 0.75f);
	}
}

void spray_gun::update(const seconds delta) {
	for (auto& g : m_guns)
		g.update(delta);
}

std::vector<std::unique_ptr<iprojectile>>
spray_gun::create(physicslib::world& w, const glm::vec3& pos) {
	std::vector<std::unique_ptr<iprojectile>> result;
	std::size_t ammo_loss = 0;
	for (auto& g : m_guns) {
		auto bullets = g.create(w, pos);
		if (bullets.size() > 0)
			ammo_loss = 1;
		std::move(
			std::begin(bullets), std::end(bullets),
			std::back_inserter(result)
		);
	}
	m_ammo -= ammo_loss;
	return result;
}

bool spray_gun::jammed() const {
	return m_ammo == 0;
}

}
