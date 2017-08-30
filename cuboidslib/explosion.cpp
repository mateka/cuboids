#include <cuboidslib/explosion.h>
#include <cuboidslib/ivisitor.h>
#include <cuboidslib/imutable_visitor.h>
#include <physicslib/world.h>
#include <chrono>


using namespace std::chrono_literals;

namespace cuboidslib {

explosion::explosion(
	physicslib::world& w,
	const glm::vec3& pos,
	const seconds lifeSpan,
	const float size
)
	: m_body{ w.create_dynamic_box(size, size * glm::vec3{ 1.0f, 1.0f, 1.0f }, pos) },
	m_lifeSpan{ lifeSpan }, m_lived{ 0 }
{
	m_body->constrain_movement(false, false, false); // Explosions do not move
	m_body->angular_velocity({15, 15, 15});
}

void explosion::visit(imutable_visitor& v) {
	v.on_visit(*this);
}

void explosion::visit(ivisitor& v) const {
	v.on_visit(*this);
}

const physicslib::body* explosion::body() const {
	return m_body.get();
}

glm::mat4 explosion::transform() const {
	return m_body->transform();
}

void explosion::update(const seconds delta) {
	m_lived += delta;
	auto scale = lived() / life_span();
	m_body->local_scale({ scale, scale, scale });
}

seconds explosion::life_span() const {
	return m_lifeSpan;
}

seconds explosion::lived() const {
	return m_lived;
}

bool explosion::alive() const {
	return lived() < life_span();
}

void explosion::die() {
	m_lived = life_span() + 3600s;
}

}
