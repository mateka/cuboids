#pragma once

#include <cuboidslib/icuboid_object.h>
#include <cuboidslib/iprojectile.h>
#include <memory>


namespace cuboidslib {

/*! \brief Ship interface */
class iship : public icuboid_object {
public:
    /*! \brief Move ship to the left. */
    virtual void left() = 0;

    /*! \brief Move ship to the right. */
    virtual void right() = 0;

    /*! \brief Shot.
    *   \return Projectile object. */
    virtual std::unique_ptr<iprojectile> shot() = 0;
};

}