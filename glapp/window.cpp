#include <glapp/window.h>
#include <glapp/include_glfw.h>


namespace glapp {

window::window(const creation_params& params)
    : m_window { params.create_glfw_window() }
{
    if(!m_window)
        throw window_creation_error();
    glfwMakeContextCurrent(m_window);
    glbinding::Binding::initialize();

	glfwSwapInterval(1);	// vsync
	set_glviewport();
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, 1);
	glfwSetFramebufferSizeCallback(
		m_window,
		[](GLFWwindow* wnd, int w, int h) {
			glViewport(0, 0, w, h);
	});

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}


bool window::should_close() const {
    return glfwWindowShouldClose(m_window);
}

void window::present() const {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

version window::glversion() const {
	return version(
		glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MAJOR),
		glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MINOR),
		glfwGetWindowAttrib(m_window, GLFW_CONTEXT_REVISION)
	);
}

int window::get_key(const int key) const {
	return glfwGetKey(m_window, key);
}

void window::set_glviewport() const {
	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);
	gl::glViewport(0, 0, width, height);
}


window_creation_error::window_creation_error()
    : runtime_error("glfwCreateWindow failed")
{}

}
