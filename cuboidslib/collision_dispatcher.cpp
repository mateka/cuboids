#include <cuboidslib/collision_dispatcher.h>
#include <cuboidslib/moving_ship.h>
#include <cuboidslib/bullet.h>
#include <cuboidslib/rocket.h>
#include <cuboidslib/cuboid.h>
#include <cuboidslib/crate.h>
#include <cuboidslib/ship_collider.h>
#include <cuboidslib/projectile_collider.h>
#include <cuboidslib/rocket_collider.h>
#include <cuboidslib/cuboid_collider.h>
#include <cuboidslib/explosion_collider.h>


namespace cuboidslib {

collision_dispatcher::collision_dispatcher(game& g, icuboid_object& other)
	: m_game{ g }, m_other{ other }
{}

void collision_dispatcher::on_visit(moving_ship& s) {
	m_other.visit(ship_collider{ m_game, s });
}

void collision_dispatcher::on_visit(bullet& b) {
	m_other.visit(projectile_collider{ m_game, b });
}

void collision_dispatcher::on_visit(rocket& r) {
	m_other.visit(rocket_collider{ m_game, r });
}

void collision_dispatcher::on_visit(cuboid& c) {
	m_other.visit(cuboid_collider{ m_game, c });
}

void collision_dispatcher::on_visit(crate& c) {
	m_other.visit(cuboid_collider{ m_game , c });
}

void collision_dispatcher::on_visit(explosion& e) {
	m_other.visit(explosion_collider{ m_game , e });
}

}
