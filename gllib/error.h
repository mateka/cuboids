#pragma once

#include <stdexcept>


namespace gllib {

/*! \brief Helper class for tagging error classes from gllib library. */
class error {};


/*! \brief OpenGL error */
class glerror : public std::runtime_error, error {
public:
	/*! \brief Gets last OpenGL error and converts it to string. */
	glerror();
};

}