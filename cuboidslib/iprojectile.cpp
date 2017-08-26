#include <cuboidslib/iprojectile.h>

namespace cuboidslib {

iprojectile::iprojectile(const seconds lifeSpan)
	: m_lifeSpan{ lifeSpan }, m_lived{ 0.0f }
{}

void iprojectile::update(const seconds delta) {
	m_lived += delta;
}

bool iprojectile::alive() const {
	return m_lived < m_lifeSpan;
}

}
