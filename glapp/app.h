#pragma once

#include <glapp/error.h>
#include <glapp/glfw_wrapper.h>
#include <glapp/version.h>
#include <glapp/window.h>
#include <glapp/creation_params.h>
#include <utils/seconds.h>


namespace glapp {

/*! \brief Base class for OpenGL single window app. */
class app {
public:
    using seconds = utils::seconds;	//!< Type for update delta
	using params_type = creation_params;	//!< type of app creation parameters

    /*! \brief Initializes OpenGL libraries and creates window. */
    explicit app(const params_type& params);
    app(app&&) = delete;
    app(const app&) = delete;

    virtual ~app() {}

    app& operator=(app&&) = delete;
    app& operator=(const app&) = delete;

	/*! \brief Get context's OpenGL version.
	*   \return OpenGL version used by app's OpenGL context. */
	version glversion() const;

	/*! \brief Retrive state of given key.
	*   \param key key, for which state has to be checked
	*   \return State of given key. */
	int get_key(const int key) const;

    /*! \brief Executes application's game loop. */
    void run();
protected:
    /*! \brief Updates app state.
    *   \param delta Time from last update (in seconds). */
    virtual void update(const seconds delta) {}

private:
    glfw_wrapper m_glfw;
    window m_window;
};

}
