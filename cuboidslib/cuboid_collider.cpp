#include <cuboidslib/cuboid_collider.h>
#include <cuboidslib/moving_ship.h>
#include <cuboidslib/bullet.h>
#include <cuboidslib/icuboid.h>
#include <cuboidslib/ship_collider.h>
#include <cuboidslib/projectile_collider.h>


namespace cuboidslib {

cuboid_collider::cuboid_collider(game& g, icuboid& cuboid)
	: m_game(g), m_cuboid(cuboid)
{}

void cuboid_collider::on_visit(moving_ship& s) {
	m_cuboid.visit(ship_collider(m_game, s));
}

void cuboid_collider::on_visit(bullet& b) {
	m_cuboid.visit(projectile_collider(m_game, b));
}

}
