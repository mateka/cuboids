#pragma once

#include <cuboidslib/iprojectile.h>
#include <utils/seconds.h>


namespace cuboidslib {

/*! \brief Projectile interface */
class projectile : public iprojectile {
public:
	/*! \brief Creates projectile with limited lifespan.
	*   \projectile lifeSpan projectile's life span. */
	projectile(const seconds lifeSpan);

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override;

	/*! \brief Test if projectile is alive.
	*   \return true if projective lived less than its life span.*/
	bool alive() const override;
private:
	const seconds m_lifeSpan;
	seconds m_lived;
};

}
