#include <cuboidslib/crate.h>
#include <cuboidslib/ivisitor.h>
#include <cuboidslib/imutable_visitor.h>
#include <physicslib/world.h>
#include <cuboidslib/spray_gun.h>
#include <cuboidslib/wingman.h>
#include <cuboidslib/rocket.h>
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
	switch (model()) {
	case gun_model::spray3:
		return std::make_unique<spray_gun<bullet, jamming::ammo_count_jam>>(450ms, 3, 50);
	case gun_model::spray5:
		return std::make_unique<spray_gun<bullet, jamming::ammo_count_jam>>(550ms, 5, 25);
	case gun_model::bazooka:
		return std::make_unique<launcher<rocket, jamming::ammo_count_jam>>(400ms, glm::vec3{ 0, 0, -5.0f }, 5s, 1.0f, 15);
	case gun_model::patriots:
		return std::make_unique<wingman<rocket, jamming::ammo_count_jam>>(300ms, 25);
	case gun_model::boombastic3:
		return std::make_unique<spray_gun<rocket, jamming::ammo_count_jam>>(650ms, 3, 10);
	default:
		return std::make_unique<wingman<bullet, jamming::ammo_count_jam>>(150ms, 50);
	}
}

gun_model crate::model() const {
	return m_gun;
}

}
