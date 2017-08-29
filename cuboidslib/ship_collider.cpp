#include <cuboidslib/ship_collider.h>
#include <cuboidslib/moving_ship.h>
#include <cuboidslib/bullet.h>
#include <cuboidslib/cuboid.h>


namespace cuboidslib {

ship_collider::ship_collider(game& g, iship& ship)
	: m_game(g), m_ship(ship)
{}

void ship_collider::on_visit(cuboid& c) {
	m_ship.die();
}

}
