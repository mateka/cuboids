#include <cuboidslib/projectile_collider.h>
#include <cuboidslib/iprojectile.h>
#include <cuboidslib/cuboid.h>
#include <cuboidslib/crate.h>
#include <cuboidslib/explosion_collider.h>
#include <cuboidslib/rocket_collider.h>


namespace cuboidslib {

projectile_collider::projectile_collider(game& g, iprojectile& projectile)
	: m_game{ g }, m_projectile{ projectile }
{}

void projectile_collider::on_visit(rocket& r) {
	colliding_projectile().visit(rocket_collider{ current_game(), r });
}

void projectile_collider::on_visit(cuboid& c) {
	colliding_projectile().die();
	c.die();
	current_game().on_cuboid_killed();
}

void projectile_collider::on_visit(crate& c) {
	colliding_projectile().die();
	c.die();
}

void projectile_collider::on_visit(explosion& e) {
	colliding_projectile().visit(explosion_collider{ current_game(), e});
}

game& projectile_collider::current_game() const {
	return m_game;
}

iprojectile& projectile_collider::colliding_projectile() const {
	return m_projectile;
}

}
