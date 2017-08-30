#include <cuboidslib/crate.h>
#include <cuboidslib/ivisitor.h>
#include <cuboidslib/imutable_visitor.h>
#include <physicslib/world.h>
#include <cuboidslib/spray_gun.h>
#include <cuboidslib/wingman.h>
#include <memory>
#include <chrono>


using namespace std::chrono_literals;

namespace cuboidslib {

crate::crate(
	physicslib::world& w,
	const glm::vec3& pos,
	const glm::vec3& velocity,
	const glm::vec3& rotation,
	const gun_model model
)
	: cuboid{ w, pos, velocity, {1, 1, 1}, rotation },
	m_gun{ model }
{}

void crate::visit(imutable_visitor& v) {
	v.on_visit(*this);
}

void crate::visit(ivisitor& v) const {
	v.on_visit(*this);
}

std::unique_ptr<iprojectile_factory> crate::gun() {
	switch (m_gun) {
	case gun_model::spray3:
		return std::make_unique<spray_gun>(650ms, 3, 50);
	case gun_model::spray5:
		return std::make_unique<spray_gun>(750ms, 5, 25);
	default:
		return std::make_unique<wingman>(300ms, 50);
	}
}

}
