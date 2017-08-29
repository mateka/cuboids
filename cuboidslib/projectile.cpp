#include <cuboidslib/projectile.h>

namespace cuboidslib {

projectile::projectile(const seconds lifeSpan)
	: m_lifeSpan{ lifeSpan }, m_lived{ 0.0f }
{}

void projectile::update(const seconds delta) {
	m_lived += delta;
}

seconds projectile::life_span() const {
	return m_lifeSpan;
}

seconds projectile::lived() const {
	return m_lived;
}

bool projectile::alive() const {
	return lived() < life_span();
}

}