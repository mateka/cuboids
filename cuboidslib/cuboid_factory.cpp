#include <cuboidslib/cuboid_factory.h>
#include <physicslib/world.h>
#include <cuboidslib/cuboid.h>
#include <chrono>


using namespace std::chrono_literals;

namespace cuboidslib {

cuboid_factory::cuboid_factory(const seconds& cooldown)
	: m_cooldown(std::chrono::duration_cast<std::chrono::nanoseconds>(cooldown))
{}

void cuboid_factory::update(const seconds delta) {
	m_cooldown.update(std::chrono::duration_cast<std::chrono::nanoseconds>(delta));
}

std::vector<std::unique_ptr<icuboid>> cuboid_factory::create(physicslib::world& w) {
	std::vector<std::unique_ptr<icuboid>> result;
	m_cooldown.execute([&result, &w]() {
		result.push_back(std::make_unique<cuboid>(
			w,
			glm::vec3{ 0, 0, -5.0f },
			glm::vec3{ 0, 0, 2.0f },
			glm::vec3{ 1, 2, 1.0f },
			glm::vec3{ 1.25f, 0, 0 }
		));
	});
	return result;
}

}
