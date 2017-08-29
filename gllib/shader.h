#pragma once

#include <stdexcept>
#include <gllib/gl.h>
#include <gllib/error.h>


namespace gllib {

/*! \brief Class for shader compilation error */
class shader_compilation_error : public std::runtime_error, error {
public:
	shader_compilation_error();
};

class program;


/*! \brief Class for transforming shader code into OpenGL shader. */
class shader final {
public:
	/*! \brief Creates OpenGL shader from string code.
	*   \param type type of shader.
	*   \param code string with shader code. */
	explicit shader(const gl::GLenum type, const char* code);

	shader(shader&& other);
	shader& operator=(shader&& other);

	~shader();

	// copying is disabled
	shader(const shader&) = delete;
	shader& operator=(const shader&) = delete;
private:
	friend class program;

	gl::GLuint m_shaderid;
};

}
