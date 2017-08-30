#include <cuboidslib/rocket.h>
#include <cuboidslib/ivisitor.h>
#include <cuboidslib/imutable_visitor.h>
#include <physicslib/world.h>


namespace cuboidslib {

rocket::rocket(
	physicslib::world& w,
	const glm::vec3& pos,
	const glm::vec3& velocity,
	const seconds lifeSpan,
	const float size
)
	: bullet{w, pos, velocity * 0.75f, lifeSpan * 1.15f, size * 1.5f }
{}

void rocket::visit(imutable_visitor& v) {
	v.on_visit(*this);
}

void rocket::visit(ivisitor& v) const {
	v.on_visit(*this);
}

}