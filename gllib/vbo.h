#pragma once

#include <gllib/gl.h>
#include <gllib/buffer.h>


namespace gllib {

/*! \brief Class for OpenGL vertex array object. */
class vbo final {
public:
	/*! \brief Creates OpenGL vertex array object. */
	vbo();

	vbo(vbo&& other);
	vbo& operator=(vbo&& other);

	~vbo();

	// copying is disabled
	vbo(const vbo&) = delete;
	vbo& operator=(const vbo&) = delete;

	/*! \brief Binds this vertex array to OpenGL context.
	*   \return true if buffer was bound. */
	bool bind() const;

	/*! \brief Enables n-th vertex attribute array.
	*   \param n array'a index. */
	void enable_array(const gl::GLuint n) const;

	/*! \brief Disables n-th vertex attribute array.
	*   \param n array'a index. */
	void disable_array(const gl::GLuint n) const;

	/*! \brief Creates single OpenGL buffer
	*   \param size buffer size.
	*   \param target OpenGL target of buffer data.
	*   \param usage buffer usage type.*/
	template<typename Element>
	buffer<Element> create_buffer(
		const typename buffer<Element>::size_type size,
		const gl::GLenum target,
		const gl::GLenum usage
	) const {
		return { *this, size, target, usage };
	}
private:
	gl::GLuint m_arrayid;
};

}
