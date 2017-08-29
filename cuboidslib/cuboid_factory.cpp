#include <cuboidslib/cuboid_factory.h>
#include <physicslib/world.h>
#include <cuboidslib/cuboid.h>
#include <chrono>


using namespace std::chrono_literals;

namespace cuboidslib {

cuboid_factory::cuboid_factory(
	const std::mt19937_64::result_type seed, 
	const seconds& cooldown
)
	: m_cooldown(std::chrono::duration_cast<std::chrono::nanoseconds>(cooldown)),
	m_engine{ seed },
	m_size{ 0.5f, 2.5f },
	m_velocity{ -1, 1 },
	m_rotation{ -1.5, 1.5 }
{}

void cuboid_factory::update(const seconds delta) {
	m_cooldown.update(std::chrono::duration_cast<std::chrono::nanoseconds>(delta));
}

std::vector<std::unique_ptr<icuboid>> cuboid_factory::create(physicslib::world& w) {
	std::vector<std::unique_ptr<icuboid>> result;
	m_cooldown.execute([this, &result, &w]() {
		result.push_back(std::make_unique<cuboid>(
			w,
			glm::vec3{ 0, 0, -5.0f },
			glm::vec3{ m_velocity(m_engine), 0, 2.0f },
			glm::vec3{ m_size(m_engine), m_size(m_engine), m_size(m_engine) },
			glm::vec3{ m_rotation(m_engine), m_rotation(m_engine), m_rotation(m_engine) }
		));
	});
	return result;
}

}
