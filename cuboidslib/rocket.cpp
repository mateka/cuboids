#include <cuboidslib/rocket.h>
#include <cuboidslib/ivisitor.h>
#include <cuboidslib/imutable_visitor.h>
#include <physicslib/world.h>


namespace cuboidslib {

rocket::rocket(
	physicslib::world& w,
	iexplosive& ex,
	const glm::vec3& pos,
	const glm::vec3& velocity,
	const seconds lifeSpan,
	const float size
)
	: bullet{w, ex, pos, velocity * 0.75f, lifeSpan * 1.15f, size * 1.5f },
	m_size{ size }
{}

void rocket::update(const seconds delta) {
	auto wasAlive = alive();
	bullet::update(delta);
	// Explode on death
	if (wasAlive != alive())
		explosive().explode(position(), size());
}

void rocket::visit(imutable_visitor& v) {
	v.on_visit(*this);
}

void rocket::visit(ivisitor& v) const {
	v.on_visit(*this);
}

float rocket::size() const {
	return m_size;
}

}
