#include <cuboidslib/explosion_collider.h>
#include <cuboidslib/bullet.h>
#include <cuboidslib/rocket.h>
#include <cuboidslib/cuboid.h>
#include <cuboidslib/crate.h>
#include <cuboidslib/rocket_collider.h>


namespace cuboidslib {

explosion_collider::explosion_collider(game& g, explosion& e)
	: m_game{ g }, m_explosion{ e }
{}

void explosion_collider::on_visit(bullet& b) {
	b.die();
}

void explosion_collider::on_visit(rocket& r) {
	m_explosion.visit(rocket_collider{m_game, r});
}

void explosion_collider::on_visit(cuboid& c) {
	c.die();
	m_game.on_cuboid_killed();
}

void explosion_collider::on_visit(crate& c) {
	c.die();
}

}
