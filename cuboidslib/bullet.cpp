#include <cuboidslib/bullet.h>
#include <cuboidslib/ivisitor.h>
#include <physicslib/world.h>
#include <glm/gtc/matrix_transform.hpp>


namespace cuboidslib {

bullet::bullet(
	physicslib::world& w,
	const glm::vec3& pos,
	const glm::vec3& velocity,
	const seconds lifeSpan
)
	: projectile{ lifeSpan },
	m_body{ w.create_dynamic_box(0.1f,{ 0.1f, 0.1f, 0.2f },{ pos[0], pos[1], pos[2] }) }
{
	m_body->constrain_movement(true, false, true); // Bullet can only move on xz plane
	m_body->constrain_rotation(false, false, true); // Bullet can only rotate around z axis

	m_body->velocity({ velocity[0], velocity[1], velocity[2] });
	m_body->angular_velocity({0, 0, 2.0f * velocity.length()});
}

void bullet::visit(ivisitor& v) const {
	v.on_visit(*this);
}

glm::mat4 bullet::transform() const {
	static const auto scale = glm::scale(glm::mat4(), glm::vec3{ 0.2, 0.2, 0.4 });
	return m_body->transform() * scale;
}

}
