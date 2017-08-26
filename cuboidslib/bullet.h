#pragma once

#include <cuboidslib/iprojectile.h>
#include <memory>
#include <glm/vec3.hpp>
#include <physicslib/box.h>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Simple bullet */
class bullet : public iprojectile {
public:
	bullet(
		physicslib::world& w,
		const glm::vec3& pos,
		const glm::vec3& velocity,
		const seconds lifeSpan
	);

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(ivisitor& v) const override;
private:
	std::unique_ptr<physicslib::box> m_body;
};

}
