#include <cuboidslib/moving_ship.h>
#include <cuboidslib/ivisitor.h>
#include <physicslib/world.h>
#include <array>
#include <iostream>


namespace cuboidslib {

moving_ship::moving_ship(
	physicslib::world& w,
	const float size,
	const glm::vec3& pos,
	const float speed
)
	: m_body{ w.create_dynamic_box(size, {size, size, size}, {pos[0], pos[1], pos[2]} ) },
	m_size{ size }, m_speed{ speed }
{
	m_body->constrain_movement(true, false, false); // Ship can only move on x axis
	m_body->constrain_rotation(false, false, true); // Ship can only rotate around z axis
}

void moving_ship::update(const seconds delta) {
	m_body->velocity({ 0, 0, 0 });
	m_body->angular_velocity({ 0, 0, 0 });
}

void moving_ship::visit(ivisitor& v) const {
	v.on_visit(*this);
}

void moving_ship::left() {
	m_body->velocity({ -m_speed, 0, 0 });
	m_body->angular_velocity({ 0, 0, 0.5f * m_speed });
}

void moving_ship::right() {
	m_body->velocity({ m_speed, 0, 0 });
	m_body->angular_velocity({ 0, 0, -0.5f * m_speed });
}

std::unique_ptr<iprojectile> moving_ship::shot() {
	return nullptr;
}

float moving_ship::size() const {
	return m_size;
}

glm::mat4 moving_ship::transform() const {
	return m_body->transform();
}

}
