#pragma once

#include <cuboidslib/icuboid_object.h>
#include <memory>
#include <glm/vec3.hpp>
#include <physicslib/box.h>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Explosion */
class explosion : public icuboid_object {
public:
	/*! \brief Creates explosion.
	*   \param w physics world in which explosion will be registered.
	*   \param pos position of the explosion.
	*   \param lifeSpan how long explosion will live.
	*   \param size size of the explosion (default: 1.0f). */
	explosion(
		physicslib::world& w,
		const glm::vec3& pos,
		const seconds lifeSpan,
		const float size = 1.0f
	);

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(imutable_visitor& v) override;

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(ivisitor& v) const override;

	/*! \brief Obtains physics body from cuboid.
	*   \return Body associated with cuboid. */
	const physicslib::body* body() const override;

	/*! \brief Returns model matrix of the explosion.
	*   \return Explosion's body transform. */
	glm::mat4 transform() const;

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
	std::unique_ptr<physicslib::box> m_body;
	const seconds m_lifeSpan;
	seconds m_lived;
	float m_size;
};

}
