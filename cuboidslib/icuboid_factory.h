#pragma once

#include <cuboidslib/icuboid.h>
#include <glm/vec3.hpp>
#include <memory>
#include <vector>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Interface for cuboids factory. */
class icuboid_factory {
public:
	virtual ~icuboid_factory() {}

	/*! \brief Update object state.
	*   \param delta time from last update. */
	virtual void update(const seconds delta) = 0;

	/*! \brief Collection of cuboid objects.
	*   \param w physics world. */
	virtual std::vector<std::unique_ptr<icuboid>> create(physicslib::world& w) = 0;

	/*! \brief Notify factory, that player killed one cuboid. */
	virtual void on_killed() = 0;
};

}
