#include <glapp/glfw_wrapper.h>
#include <glapp/include_glfw.h>


namespace glapp {

glfw_error::glfw_error(int error, const char* description)
	: runtime_error(description), m_code(error)
{}


glfw_wrapper::glfw_wrapper() {
    if(!glfwInit())
        throw glfw_creation_error();
	glfwSetErrorCallback([](int error, const char* description) {
		throw glfw_error(error, description);
	});
}

glfw_wrapper::~glfw_wrapper() {
    glfwTerminate();
}

glfw_creation_error::glfw_creation_error()
    : runtime_error("glfwInit failed")
{}

}
