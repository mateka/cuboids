#pragma once

#include <cuboidslib/launcher.h>
#include <cuboidslib/bullet.h>


namespace cuboidslib {

/*! \brief Default gun. */
class default_gun : public launcher<bullet, jamming::no_jam> {
public:
	/*! \brief Creates gun, which shots simple bullets with given cooldown.
	*   \param cooldown cooldown between two shots.*/
	default_gun(const seconds& cooldown);
};

}
