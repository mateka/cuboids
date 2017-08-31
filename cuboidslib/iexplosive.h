#pragma once

#include <glm/vec3.hpp>


namespace cuboidslib {

/*! \brief Interface for explosive objects. */
class iexplosive {
public:
	virtual ~iexplosive() {}

	/*! \brief Create explosion.
	*   \param pos position of the explosion.
	*   \param size size of the explosion. */
	virtual void explode(const glm::vec3& pos, const float size) = 0;
};

}
