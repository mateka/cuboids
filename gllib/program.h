#pragma once

#include <string>
#include <stdexcept>
#include <unordered_map>
#include <initializer_list>
#include <glm/mat4x4.hpp>
#include <gllib/gl.h>
#include <gllib/error.h>
#include <gllib/shader.h>


namespace gllib {

/*! \brief Class for program linkage error */
class program_link_error : public std::runtime_error, error {
public:
	program_link_error();
};


/*! \brief Class for creating OpenGL shaders into OpenGL program. */
class program final {
public:
	/*! \brief Creates OpenGL program from given shaders.
	*   \param shaders shaders, which should be linked into program. */
	program(std::initializer_list<shader> shaders);

	program(program&& other);
	program& operator=(program&& other);

	~program();

	// copying is disabled
	program(const program&) = delete;
	program& operator=(const program&) = delete;

	/*! \brief Using program in current OpenGL context.
	*   \return true if program is currently in use. */
	bool use() const;

	/*! \brief Set uniform 4x4 matrix.
	*   \param name name of matrix.
	*   \param mat matrix. */
	void matrix(const std::string& name, const glm::mat4& mat);
private:
	std::unordered_map<std::string, gl::GLint> m_uniforms;
	gl::GLuint m_programid;
};

}
