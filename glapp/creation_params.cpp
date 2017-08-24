#include <glapp/creation_params.h>
#include <glapp/include_glfw.h>


namespace glapp {

creation_params&
creation_params::set_glversion(const boost::optional<version>& v) {
	m_version = v;
	return *this;
}

creation_params&
creation_params::set_resolution(const boost::optional<resolution>& r) {
	m_resolution = r;
	return *this;
}

creation_params&
creation_params::set_fullscreen(const bool value) {
	m_fullscreen = value;
	return *this;
}

creation_params&
creation_params::set_title(const std::string& t) {
	m_title = t;
	return *this;
}

GLFWwindow* creation_params::create_glfw_window() const {
	const resolution dimensions = desired_resolution();
	handle_glversion();
	return glfwCreateWindow(
		static_cast<int>(dimensions.width()),
		static_cast<int>(dimensions.height()),
		m_title.c_str(),
		desired_monitor(), nullptr);
}

resolution creation_params::desired_resolution() const {
	resolution result{ 0,0 };
	if (!m_resolution) {
		auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		result = resolution(mode->width, mode->height);
	}
	else
		result = *m_resolution;
	return result;
}

GLFWmonitor* creation_params::desired_monitor() const {
	glfwWindowHint(GLFW_RESIZABLE, m_fullscreen ? GL_FALSE : GL_TRUE);
	glfwWindowHint(GLFW_DECORATED, m_fullscreen ? GL_FALSE : GL_TRUE);
	return m_fullscreen ? glfwGetPrimaryMonitor() : nullptr;
}

void creation_params::handle_glversion() const {
	if (m_version) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, static_cast<int>(m_version->major()));
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, static_cast<int>(m_version->minor()));
	}
}

}
