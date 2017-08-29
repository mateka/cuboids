#include <cuboidslib/cuboid.h>
#include <cuboidslib/ivisitor.h>
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
	: m_body{ w.create_dynamic_box(
		static_cast<float>(scale.length()),
		{ scale.x / 2, scale.y / 2, scale.z / 2 },
		{ pos.x, pos.y, pos.z }
	) }
{
	m_body->constrain_movement(true, false, true); // Cuboid can only move on xz plane
	m_body->restitution(1.0f);	// cuboids like to bounce

	m_body->velocity({ velocity.x, velocity.y, velocity.z });
	m_body->angular_velocity({ rotation.x, rotation.y, rotation.z });
}

void cuboid::update(const seconds delta) {
}

void cuboid::visit(ivisitor& v) const {
	v.on_visit(*this);
}

bool cuboid::alive() const {
	return m_body->position().z < 10.0f;
}

glm::mat4 cuboid::transform() const {
	return m_body->transform();
}

}
