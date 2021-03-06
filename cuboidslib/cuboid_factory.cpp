#include <cuboidslib/cuboid_factory.h>
#include <physicslib/world.h>
#include <cuboidslib/cuboid.h>
#include <cuboidslib/crate.h>
#include <chrono>


using namespace std::chrono_literals;

namespace cuboidslib {

cuboid_factory::cuboid_factory(
	const std::mt19937_64::result_type seed, 
	const seconds& cooldown,
	const float worldSize,
	const float killPenalty,
	const float crateProbability
)
	: m_cooldown(std::chrono::duration_cast<std::chrono::nanoseconds>(cooldown)),
	m_engine{ seed },
	m_size{ 0.5f, 2.5f },
	m_pos{ -worldSize , worldSize },
	m_velocity{ -1, 1 },
	m_rotation{ -1.5, 1.5 },
	m_crateDistribution{ 0, 1 },
	m_gunsDistribution{ 0, 1 },
	m_killPenalty{ killPenalty }, m_additional{ 0 },
	m_crateProbability{ crateProbability }
{}

void cuboid_factory::update(const seconds delta) {
	m_cooldown.update(std::chrono::duration_cast<std::chrono::nanoseconds>(delta));
}

std::vector<std::unique_ptr<icuboid>> cuboid_factory::create(physicslib::world& w) {
	std::vector<std::unique_ptr<icuboid>> result;
	m_cooldown.execute([this, &result, &w]() {
		for (std::size_t i = 0; i < 1 + m_additional; ++i) {
			auto c = new_cuboid(w, glm::vec3{ m_pos(m_engine), 0, -5.0f });
			result.push_back(std::move(c));
		}
		m_additional = 0;
	});
	return result;
}

void cuboid_factory::on_killed() {
	m_additional += m_killPenalty;
}

std::unique_ptr<icuboid> cuboid_factory::new_cuboid(physicslib::world& w, const glm::vec3& pos) {
	const auto draw = m_crateDistribution(m_engine);
	if (draw < m_crateProbability)
		return new_crate(w, pos);

	return std::make_unique<cuboid>(
		w,
		pos,
		glm::vec3{ m_velocity(m_engine), 0, 2.0f },
		glm::vec3{ m_size(m_engine), m_size(m_engine), m_size(m_engine) },
		glm::vec3{ m_rotation(m_engine), m_rotation(m_engine), m_rotation(m_engine) }
	);
}

std::unique_ptr<icuboid> cuboid_factory::new_crate(physicslib::world& w, const glm::vec3& pos) {
	const auto draw = m_gunsDistribution(m_engine);
	auto model = gun_model::wingman;
	if (draw < 0.20f)
		model = gun_model::spray3;
	else if (draw < 0.35f)
		model = gun_model::spray5;
	else if (draw < 0.50f)
		model = gun_model::bazooka;
	else if (draw < 0.65f)
		model = gun_model::patriots;
	else if (draw < 0.80f)
		model = gun_model::boombastic3;
	
	return std::make_unique<crate>(
		w,
		pos,
		glm::vec3{ m_velocity(m_engine), 0, 2.0f },
		glm::vec3{ m_rotation(m_engine), m_rotation(m_engine), m_rotation(m_engine) },
		model
	);
}

}
