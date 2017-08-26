#include <cuboidslib/bullet.h>
#include <cuboidslib/ivisitor.h>
#include <physicslib/world.h>


namespace cuboidslib {

bullet::bullet(
	physicslib::world& w,
	const glm::vec3& pos,
	const glm::vec3& velocity,
	const seconds lifeSpan
)
	: iprojectile{ lifeSpan },
	m_body{ w.create_dynamic_box(0.1f,{ 0.1f, 0.1f, 0.2f },{ pos[0], pos[1], pos[2] }) }
{}

void bullet::visit(ivisitor& v) const {
	v.on_visit(*this);
}

}
