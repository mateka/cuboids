#include <cuboidslib/bullet.h>
#include <cuboidslib/ivisitor.h>
#include <cuboidslib/imutable_visitor.h>
#include <physicslib/world.h>


namespace cuboidslib {

bullet::bullet(
	physicslib::world& w,
	iexplosive& ex,
	const glm::vec3& pos,
	const glm::vec3& velocity,
	const seconds lifeSpan,
	const float size
)
	: projectile{ lifeSpan },
	m_body{ w.create_dynamic_box(0.1f * size, size * glm::vec3{ 0.2f, 0.2f, 0.4f }, pos) },
	m_explosive{ ex }
{
	m_body->constrain_movement(true, false, true); // Bullet can only move on xz plane
	m_body->constrain_rotation(false, false, true); // Bullet can only rotate around z axis
	m_body->restitution(1.0f);	// bullets like to bounce

	m_body->velocity(velocity);
	m_body->angular_velocity({0, 0, 2.0f * velocity.length()});
}

void bullet::visit(imutable_visitor& v)  {
	v.on_visit(*this);
}

void bullet::visit(ivisitor& v) const {
	v.on_visit(*this);
}

const physicslib::body* bullet::body() const {
	return m_body.get();
}

glm::mat4 bullet::transform() const {
	return m_body->transform();
}

glm::vec3 bullet::position() const {
	return m_body->position();
}

iexplosive& bullet::explosive() const {
	return m_explosive;
}

}
