#include <cuboidslib/rocket_collider.h>
#include <cuboidslib/rocket.h>
#include <cuboidslib/cuboid.h>
#include <cuboidslib/crate.h>
#include <cuboidslib/explosion_collider.h>


namespace cuboidslib {

rocket_collider::rocket_collider(game& g, rocket& r)
	: projectile_collider{ g, r }
{}

void rocket_collider::on_visit(bullet& b) {
	b.die();
	explode(colliding_rocket());
}

void rocket_collider::on_visit(cuboid& c) {
	c.die();
	explode(colliding_rocket());
}

void rocket_collider::on_visit(crate& c) {
	c.die();
	explode(colliding_rocket());
}

void rocket_collider::on_visit(explosion&) {
	explode(colliding_rocket());
}

rocket& rocket_collider::colliding_rocket() const {
	return dynamic_cast<rocket&>(colliding_projectile());
}

void rocket_collider::explode(rocket& r) const {
	current_game().explode(r.position(), r.size());
	r.die();
}

}
