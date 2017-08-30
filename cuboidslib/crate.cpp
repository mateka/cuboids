#include <cuboidslib/crate.h>
#include <cuboidslib/ivisitor.h>
#include <cuboidslib/imutable_visitor.h>
#include <physicslib/world.h>
#include <glm/gtc/matrix_transform.hpp>


namespace cuboidslib {

crate::crate(
	physicslib::world& w,
	const glm::vec3& pos,
	const glm::vec3& velocity,
	const glm::vec3& rotation
)
	: cuboid{ w, pos, velocity, {1, 1, 1}, rotation }
{}

void crate::visit(imutable_visitor& v) {
	v.on_visit(*this);
}

void crate::visit(ivisitor& v) const {
	v.on_visit(*this);
}

}
