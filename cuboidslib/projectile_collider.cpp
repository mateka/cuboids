#include <cuboidslib/projectile_collider.h>
#include <cuboidslib/iprojectile.h>
#include <cuboidslib/cuboid.h>


namespace cuboidslib {

projectile_collider::projectile_collider(game& g, iprojectile& projectile)
	: m_game(g), m_projectile(projectile)
{}

void projectile_collider::on_visit(cuboid& c) {
	m_projectile.die();
	c.die();
	m_game.on_cuboid_killed();
}

}
