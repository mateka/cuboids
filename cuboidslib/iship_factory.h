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

	/*! \brief Creates ship. */
	virtual std::unique_ptr<iship> create(
		physicslib::world& w, const float worldSize) = 0;
};

}
