#pragma once

#include <cuboidslib/projectile.h>
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
	*   \param pos starting position of the bullet.
	*   \param velocity linear velocity of the bullet.
	*   \param lifeSpan how long bullet will live. */
	bullet(
		physicslib::world& w,
		const glm::vec3& pos,
		const glm::vec3& velocity,
		const seconds lifeSpan
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

	/*! \brief Returns model matrix of the ship.
	*   \return Ship's body transform. */
	glm::mat4 transform() const;
private:
	std::unique_ptr<physicslib::box> m_body;
};

}
