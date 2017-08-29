#include <cuboidslib/moving_ship.h>
#include <cuboidslib/ivisitor.h>
#include <cuboidslib/imutable_visitor.h>
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
	: m_defaultGun{500ms}, m_gun {&m_defaultGun},
	m_body{ w.create_dynamic_box(size, 0.5f * glm::vec3{size, size, size}, pos) },
	m_gunPosition{0, 0, -0.5},
	m_speed{ speed }, m_alive{ true }
{
	m_body->constrain_movement(true, false, false); // Ship can only move on x axis
	m_body->constrain_rotation(false, false, true); // Ship can only rotate around z axis
}

void moving_ship::update(const seconds delta) {
	m_gun->update(delta);
}

void moving_ship::visit(imutable_visitor& v) {
	v.on_visit(*this);
}

void moving_ship::visit(ivisitor& v) const {
	v.on_visit(*this);
}

bool moving_ship::alive() const {
	return m_alive;
}

void moving_ship::die() {
	m_alive = false;
}

const physicslib::body* moving_ship::body() const {
	return m_body.get();
}

void moving_ship::left() {
	if (-m_speed <= m_body->velocity().x)
		m_body->apply_force(glm::vec3{ -5, 0, 0 }, glm::vec3{ 0.5f, 0.5f, 0 });
}

void moving_ship::right() {
	if (m_body->velocity().x <= m_speed)
		m_body->apply_force(glm::vec3{ 5, 0, 0 }, glm::vec3{ -0.5f, 0.5f, 0 });
}

void moving_ship::stop() {
	m_body->velocity({ 0, 0, 0 });
	m_body->angular_velocity({ 0, 0, 0 });
}

std::vector<std::unique_ptr<iprojectile>> moving_ship::shot(physicslib::world& w) {
	const auto pos = transform() * glm::vec4{ m_gunPosition, 1};
	return m_gun->create(w, pos);
}

glm::mat4 moving_ship::transform() const {
	return m_body->transform();
}

}
