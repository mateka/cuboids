#pragma once

#include <cuboidslib/iship_factory.h>
#include <cuboidslib/iship.h>
#include <glm/vec3.hpp>


namespace cuboidslib {

/*! \brief Simple ship factory, which always create moving_ship. */
class ship_factory : public cuboidslib::iship_factory {
public:
	/*! \brief Creates factory.
	*   \param pos ship starting position.
	*   \param speed ship speed. */
	ship_factory(const glm::vec3& pos, const float speed);

	/*! \brief Creates moving_ship instance.
	*   \param w physics world in which object will be registered. */
	std::unique_ptr<cuboidslib::iship> create(physicslib::world& w) override;
private:
	glm::vec3 m_shipPosition;
	float m_shipSpeed;
};

}
