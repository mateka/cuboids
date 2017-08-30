#include <cuboidslib/wingman.h>
#include <physicslib/world.h>
#include <cuboidslib/bullet.h>
#include <chrono>


using namespace std::chrono_literals;

namespace cuboidslib {

wingman::wingman(
	const seconds& cooldown,
	const std::size_t ammo
)
	: m_ammo{ ammo }, m_guns{
		default_gun{ cooldown, glm::vec3{ 0, 0, -7.0f }, 2s, 0.5f },
		default_gun{ cooldown, glm::vec3{ 0, 0, -7.0f }, 2s, 0.5f }
	}
{}

void wingman::update(const seconds delta) {
	for (auto& g : m_guns)
		g.update(delta);
}

std::vector<std::unique_ptr<iprojectile>>
wingman::create(physicslib::world& w, const glm::vec3& pos) {
	auto left = m_guns[0].create(w, pos - glm::vec3{0.25, 0, 0});
	auto right = m_guns[1].create(w, pos + glm::vec3{0.25, 0, 0});
	if (left.size() > 0 || right.size() > 0)
		--m_ammo;

	std::vector<std::unique_ptr<iprojectile>> result;
	std::move(
		std::begin(left), std::end(left),
		std::back_inserter(result)
	);
	std::move(
		std::begin(right), std::end(right),
		std::back_inserter(result)
	);
	return result;
}

bool wingman::jammed() const {
	return m_ammo == 0;
}

}
