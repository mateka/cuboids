#pragma once

#include <cuboidslib/icuboid_object.h>
#include <cuboidslib/iprojectile.h>
#include <cuboidslib/iprojectile_factory.h>
#include <memory>
#include <vector>


namespace physicslib {
class world;
}

namespace cuboidslib {

/*! \brief Ship interface */
class iship : public icuboid_object {
public:
    /*! \brief Move ship to the left. */
    virtual void left() = 0;

    /*! \brief Move ship to the right. */
    virtual void right() = 0;

	/*! \brief Stops ship movement. */
	virtual void stop() = 0;

    /*! \brief Shot.
	*   \param w physics world
    *   \return Collection of projectile objects. */
    virtual std::vector<std::unique_ptr<iprojectile>> shot(physicslib::world& w) = 0;

	/*! \brief Changes ship's gun.
	*   \param gun new gun. */
	virtual void change_gun(std::unique_ptr<iprojectile_factory> gun) = 0;
};

}