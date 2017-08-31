#include <cuboidslib/cuboid.h>
#include <cuboidslib/ivisitor.h>
#include <cuboidslib/imutable_visitor.h>
#include <physicslib/world.h>
#include <glm/gtc/matrix_transform.hpp>


namespace cuboidslib {

cuboid::cuboid(
	physicslib::world& w,
	const glm::vec3& pos,
	const glm::vec3& velocity,
	const glm::vec3& scale,
	const glm::vec3& rotation
)
	: m_body{ w.create_dynamic_box(static_cast<float>(scale.length()), scale, pos) }
{
	m_body->constrain_movement(true, false, true); // Cuboid can only move on xz plane
	m_body->restitution(1.0f);	// cuboids like to bounce

	m_body->velocity(velocity);
	m_body->angular_velocity(rotation);
}

void cuboid::update(const seconds delta) {
}

void cuboid::visit(imutable_visitor& v) {
	v.on_visit(*this);
}

void cuboid::visit(ivisitor& v) const {
	v.on_visit(*this);
}

bool cuboid::alive() const {
	return m_body->position().z < 10.0f;
}

void cuboid::die() {
	const auto pos = m_body->position();
	m_body->position({ pos.x, pos.y, 100.0f });
}

const physicslib::body* cuboid::body() const {
	return m_body.get();
}

glm::mat4 cuboid::transform() const {
	return m_body->transform();
}

}
