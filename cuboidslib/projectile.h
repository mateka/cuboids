#pragma once

#include <cuboidslib/iprojectile.h>
#include <utils/seconds.h>


namespace cuboidslib {

/*! \brief Projectile base class */
class projectile : public iprojectile {
public:
	/*! \brief Creates projectile with limited lifespan.
	*   \projectile lifeSpan projectile's life span. */
	projectile(const seconds lifeSpan);

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override;

	/*! \brief Life span accessor.
	*   \return How much time projectili will live. */
	seconds life_span() const;

	/*! \brief Time of life accessor.
	*   \return How much time projectile lived. */
	seconds lived() const;

	/*! \brief Test if projectile is alive.
	*   \return true if projective lived less than its life span. */
	bool alive() const override;

	/*! \brief Kills object. */
	void die() override;
private:
	const seconds m_lifeSpan;
	seconds m_lived;
};

}
