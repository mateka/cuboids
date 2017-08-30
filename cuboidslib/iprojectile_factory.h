#pragma once

#include <cuboidslib/iprojectile.h>
#include <glm/vec3.hpp>
#include <memory>
#include <vector>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Interface for projectiles factory. */
class iprojectile_factory {
public:
	virtual ~iprojectile_factory() {}

	/*! \brief Update object state.
	*   \param delta time from last update. */
	virtual void update(const seconds delta) = 0;

	/*! \brief Collection of projectile objects.
	*   \param w physics world.
	*   \param pos starting position of bullet. */
	virtual std::vector<std::unique_ptr<iprojectile>>
		create(physicslib::world& w, const glm::vec3& pos) = 0;

	/*! \brief Check if gun is still working.
	*   \return false, if player can shoot from this gun. */
	virtual bool jammed() const = 0;
};

}
