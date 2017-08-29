#pragma once

#include <cuboidslib/iship.h>
#include <memory>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Interface for ships factory. */
class iship_factory {
public:
	virtual ~iship_factory() {}

	/*! \brief Creates ship.
	*   \param w physics world in which object will be registered. */
	virtual std::unique_ptr<iship> create(physicslib::world& w) = 0;
};

}
