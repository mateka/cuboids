#pragma once

#include <cuboidslib/icuboid_object.h>


namespace cuboidslib {

/*! \brief Projectile interface */
class iprojectile : public icuboid_object {
public:
	/*! \brief Creates projectile with limited lifespan.
	*   \projectile lifeSpan projectile's life span. */
	iprojectile(const seconds lifeSpan);

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override;

	/*! \brief Test if projectile is alive.
	*   \return true if projective lived less than its life span.*/
	bool alive() const;
private:
	const seconds m_lifeSpan;
	seconds m_lived;
};

}
