#include <cuboidslib/default_gun.h>
#include <physicslib/world.h>
#include <cuboidslib/bullet.h>
#include <chrono>


using namespace std::chrono_literals;

namespace cuboidslib {

default_gun::default_gun(const seconds& cooldown)
	: m_cooldown(std::chrono::duration_cast<std::chrono::nanoseconds>(cooldown))
{}

void default_gun::update(const seconds delta) {
	m_cooldown.update(std::chrono::duration_cast<std::chrono::nanoseconds>(delta));
}

std::vector<std::unique_ptr<iprojectile>>
default_gun::create(physicslib::world& w, const glm::vec3& pos) {
	std::vector<std::unique_ptr<iprojectile>> result;
	m_cooldown.execute([&result, &w, &pos]() {
		result.push_back(std::make_unique<bullet>(
			w, pos, glm::vec3{ 0, 0, -5.0f }, 2s
		));
	});
	return result;
}

}
