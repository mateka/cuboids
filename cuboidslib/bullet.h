#pragma once

#include <cuboidslib/projectile.h>
#include <cuboidslib/iexplosive.h>
#include <memory>
#include <glm/vec3.hpp>
#include <physicslib/box.h>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Simple bullet */
class bullet : public projectile {
public:
	/*! \brief Creates bullet.
	*   \param w physics world in which bullet will be registered.
	*   \param ex explosive object, which can explode.
	*   \param pos starting position of the bullet.
	*   \param velocity linear velocity of the bullet.
	*   \param lifeSpan how long bullet will live.
	*   \param size size of the bullet (default: 1.0f). */
	bullet(
		physicslib::world& w,
		iexplosive& ex,
		const glm::vec3& pos,
		const glm::vec3& velocity,
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

	/*! \brief Returns model matrix of the bullet.
	*   \return Bullet's body transform. */
	glm::mat4 transform() const;

	/*! \brief Returns position of the bullet.
	*   \return Bullet's position. */
	glm::vec3 position() const;
protected:
	iexplosive& explosive() const;
private:
	std::unique_ptr<physicslib::box> m_body;
	iexplosive& m_explosive;
};

}
