#include <cuboidslib/default_gun.h>
#include <physicslib/world.h>
#include <cuboidslib/bullet.h>


using namespace std::chrono_literals;

namespace cuboidslib {

default_gun::default_gun(
	const seconds& cooldown,
	const glm::vec3& velocity,
	const seconds& lifetime
)
	: m_cooldown(std::chrono::duration_cast<std::chrono::nanoseconds>(cooldown)),
	m_velocity{ velocity }, m_lifetime{ lifetime }
{}

void default_gun::update(const seconds delta) {
	m_cooldown.update(std::chrono::duration_cast<std::chrono::nanoseconds>(delta));
}

std::vector<std::unique_ptr<iprojectile>>
default_gun::create(physicslib::world& w, const glm::vec3& pos) {
	std::vector<std::unique_ptr<iprojectile>> result;
	m_cooldown.execute([this, &result, &w, &pos]() {
		result.push_back(std::make_unique<bullet>(
			w, pos, m_velocity, m_lifetime
		));
	});
	return result;
}

bool default_gun::jammed() const {
	return false;
}

}
