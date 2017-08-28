#include <cuboidslib/moving_ship.h>
#include <cuboidslib/ivisitor.h>
#include <physicslib/world.h>
#include <chrono>


using namespace std::chrono_literals;

namespace cuboidslib {

moving_ship::moving_ship(
	physicslib::world& w,
	const float size,
	const glm::vec3& pos,
	const float speed
)
	: m_defaultGun{1s}, m_gun {&m_defaultGun},
	m_body{ w.create_dynamic_box(size, {size, size, size}, {pos[0], pos[1], pos[2]} ) },
	m_gunPosition{0, 0, -0.5},
	m_size{ size }, m_speed{ speed }
{
	m_body->constrain_movement(true, false, false); // Ship can only move on x axis
	m_body->constrain_rotation(false, false, true); // Ship can only rotate around z axis
}

void moving_ship::update(const seconds delta) {
	m_body->velocity({ 0, 0, 0 });
	m_body->angular_velocity({ 0, 0, 0 });
	m_gun->update(delta);
}

void moving_ship::visit(ivisitor& v) const {
	v.on_visit(*this);
}

bool moving_ship::alive() const {
	return true;
}

void moving_ship::left() {
	m_body->velocity({ -m_speed, 0, 0 });
	m_body->angular_velocity({ 0, 0, 0.5f * m_speed });
}

void moving_ship::right() {
	m_body->velocity({ m_speed, 0, 0 });
	m_body->angular_velocity({ 0, 0, -0.5f * m_speed });
}

std::vector<std::unique_ptr<iprojectile>> moving_ship::shot(physicslib::world& w) {
	const auto pos = transform() * glm::vec4{ m_gunPosition, 1};
	return m_gun->create(w, { pos[0], pos[1], pos[2] });
}

float moving_ship::size() const {
	return m_size;
}

glm::mat4 moving_ship::transform() const {
	return m_body->transform();
}

}
