#pragma once

#include <cuboidslib/icuboid.h>
#include <physicslib/box.h>
#include <memory>


namespace cuboidslib {

/*! \brief Cuboid object */
class cuboid : public icuboid {
public:
	/*! \brief Creates cuboid.
	*   \param w physics world in which cuboid will be registered.
	*   \param pos starting position of the cuboid.
	*   \param velocity linear velocity of the cuboid.
	*   \param scale scale of the cuboid.
	*   \param rotation angular velocity of the cuboid. */
	cuboid(
		physicslib::world& w,
		const glm::vec3& pos,
		const glm::vec3& velocity,
		const glm::vec3& scale,
		const glm::vec3& rotation
	);

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta) override;

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(imutable_visitor& v) override;

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(ivisitor& v) const override;

	/*! \brief Test if cuboid is alive.
	*   \return true if cuboid is on game screen.*/
	bool alive() const override;

	/*! \brief Kills object. */
	void die() override;

	/*! \brief Obtains physics body from cuboid.
	*   \return Body associated with cuboid. */
	const physicslib::body* body() const override;

	/*! \brief Returns model matrix of the cuboid.
	*   \return Cuboid's body transform. */
	glm::mat4 transform() const;
private:
	std::unique_ptr<physicslib::box> m_body;
};

}
