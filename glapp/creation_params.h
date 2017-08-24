#pragma once

#include <string>
#include <boost/optional.hpp>
#include <glapp/version.h>
#include <glapp/resolution.h>


struct GLFWwindow;
struct GLFWmonitor;

namespace glapp {

/*! \brief Helper class for storing OpenGL creation parameters. */
class creation_params final {
public:
	/*! \brief Create default parameters set */
	creation_params() = default;

	creation_params(creation_params&&) = default;
	creation_params(const creation_params&) = default;
	creation_params& operator=(creation_params&&) = default;
	creation_params& operator=(const creation_params&) = default;

	/*! \brief Set OpenGL version parameter.
	*   \param v version to set.
	*   \return Modified this object. */
	creation_params& set_glversion(const boost::optional<version>& v);

	/*! \brief Set screen resolution parameter.
	*   \param r resolution to set.
	*   \return Modified this object. */
	creation_params& set_resolution(const boost::optional<resolution>& r);

	/*! \brief Set fullscreen flag.
	*   \param value flag value.
	*   \return Modified this object. */
	creation_params& set_fullscreen(const bool value);

	/*! \brief Set title parameter.
	*   \param t title to set.
	*   \return Modified this object. */
	creation_params& set_title(const std::string& t);

	/*! \brief Creates glfw window with this parameters.
	*   \return Pointer to glfw window.*/
	GLFWwindow* create_glfw_window() const;
private:
	resolution desired_resolution() const;
	GLFWmonitor* desired_monitor() const;
	void handle_glversion() const;

	boost::optional<version> m_version;
	boost::optional<resolution> m_resolution;
	std::string m_title;
	bool m_fullscreen;
};

}
