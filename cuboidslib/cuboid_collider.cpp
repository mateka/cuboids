#include <cuboidslib/cuboid_collider.h>
#include <cuboidslib/moving_ship.h>
#include <cuboidslib/bullet.h>
#include <cuboidslib/rocket.h>
#include <cuboidslib/icuboid.h>
#include <cuboidslib/ship_collider.h>
#include <cuboidslib/projectile_collider.h>
#include <cuboidslib/rocket_collider.h>
#include <cuboidslib/explosion_collider.h>


namespace cuboidslib {

cuboid_collider::cuboid_collider(game& g, icuboid& c)
	: m_game{ g }, m_cuboid{ c }
{}

void cuboid_collider::on_visit(moving_ship& s) {
	m_cuboid.visit(ship_collider{ m_game, s });
}

void cuboid_collider::on_visit(bullet& b) {
	m_cuboid.visit(projectile_collider{ m_game, b });
}

void cuboid_collider::on_visit(rocket& r) {
	m_cuboid.visit(rocket_collider{ m_game, r });
}

void cuboid_collider::on_visit(explosion& e) {
	m_cuboid.visit(explosion_collider{ m_game, e });
}

}
