#pragma once

#include <glapp/error.h>
#include <stdexcept>


namespace glapp {

/*! \brief Class for error of failed glfw3 initialization. */
class glfw_creation_error : public error, public std::runtime_error {
public:
    glfw_creation_error();
};

/*! \brief Class for glfw3 errors. */
class glfw_error : public error, public std::runtime_error {
public:
	glfw_error(int error, const char* description);

	int code() const { return m_code; }
private:
	int m_code;
};


/*! \brief RAII wrapper for glfw library */
class glfw_wrapper final {
public:
    /*! \brief Initializes glfw library. */
    glfw_wrapper();
    glfw_wrapper(glfw_wrapper&&) = delete;
    glfw_wrapper(const glfw_wrapper&) = delete;

    /*! \brief Deinitializes glfw library. */
    ~glfw_wrapper();

    glfw_wrapper& operator=(glfw_wrapper&&) = delete;
    glfw_wrapper& operator=(const glfw_wrapper&) = delete;
};

}
