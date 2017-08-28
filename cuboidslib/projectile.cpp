#include <cuboidslib/projectile.h>

namespace cuboidslib {

projectile::projectile(const seconds lifeSpan)
	: m_lifeSpan{ lifeSpan }, m_lived{ 0.0f }
{}

void projectile::update(const seconds delta) {
	m_lived += delta;
}

bool projectile::alive() const {
	return m_lived < m_lifeSpan;
}

}
