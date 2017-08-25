#pragma once

#include <tuple>
#include <glapp/error.h>
#include <glapp/version.h>
#include <glapp/creation_params.h>


struct GLFWwindow;

namespace glapp {

/*! \brief Class for error of failed glfw3 window creation. */
class window_creation_error : public error, public std::runtime_error {
public:
    window_creation_error();
};


/*! \brief Base class for OpenGL window. */
class window final {
public:
    /*! \brief Creates window. */
    explicit window(const creation_params& params);
    window(window&&) = delete;
    window(const window&) = delete;

    window& operator=(window&&) = delete;
    window& operator=(const window&) = delete;

    /*! \brief Should window be closed.
    *   \return true, if window should be closed. */
    bool should_close() const;

    /*! \brief Presents window graphic to the screen and checks for new events.*/
    void present() const;

	/*! \brief Get context's OpenGL version.
	*   \return OpenGL version used by window's context. */
	version glversion() const;

	/*! \bref Get windows current dimensions.
	*   \return Current resolution of window. */
	resolution view_resolution() const;

	/*! \brief Retrive state of given key.
	*   \param key key, for which state has to be checked
	*   \return State of given key. */
	int get_key(const int key) const;
private:
	void set_glviewport() const;

    GLFWwindow* m_window;
};

}
