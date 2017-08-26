#include <cuboids/ship_factory.h>
#include <cuboidslib/moving_ship.h>
#include <physicslib/world.h>


namespace cuboids {

ship_factory::ship_factory(const glm::vec3& pos, const float speed)
	: m_shipPosition{ pos }, m_shipSpeed{ speed }
{}

std::unique_ptr<cuboidslib::iship>
ship_factory::create(physicslib::world& w) {
	return std::make_unique<cuboidslib::moving_ship>(w, 1.0f, m_shipPosition, m_shipSpeed);
}


}
