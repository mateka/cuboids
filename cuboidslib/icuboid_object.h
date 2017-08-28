#pragma once

#include <utils/seconds.h>


namespace cuboidslib {

using seconds = utils::seconds; //!< Type for seconds count with fractional part

class ivisitor;

/*! \brief Base class for all cuboids lib objects. */
class icuboid_object {
public:
	icuboid_object() = default;
	virtual ~icuboid_object() {}

	// moving is disabled
	icuboid_object(icuboid_object&& other) = delete;
	icuboid_object& operator=(icuboid_object&& other) = delete;

	// copying is disabled
	icuboid_object(const icuboid_object&) = delete;
	icuboid_object& operator=(const icuboid_object&) = delete;

	/*! \brief Update object state.
	*   \param delta time from last update. */
	virtual void update(const seconds delta) = 0;

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	virtual void visit(ivisitor& v) const = 0;

	/*! \brief Checks if object is alive (dead should be destroyed).
	*   \return true if object should stay in game. */
	virtual bool alive() const = 0;
};

}
