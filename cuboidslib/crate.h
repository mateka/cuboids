#pragma once

#include <cuboidslib/cuboid.h>
#include <memory>


namespace cuboidslib {

/*! \brief Crate object */
class crate : public cuboid {
public:
	/*! \brief Creates crate with random gun in it.
	*   \param w physics world in which crate will be registered.
	*   \param pos starting position of the crate.
	*   \param velocity linear velocity of the crate.
	*   \param rotation angular velocity of the crate. */
	crate(
		physicslib::world& w,
		const glm::vec3& pos,
		const glm::vec3& velocity,
		const glm::vec3& rotation
	);

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(imutable_visitor& v) override;

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(ivisitor& v) const override;
private:
};

}
