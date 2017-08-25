#pragma once

#include <gllib/gl.h>


namespace gllib {

template<typename Element>
class buffer;

/*! \brief Class for RAII buffer data pointer.
*   \param Element type of elements stored in buffer. */
template<typename Element>
class buffer_data final {
public:
	using type = Element;	//!< Type of stored elements in buffer

	/*! \brief Moves data from other buffer */
	buffer_data(buffer_data&& other)
		: m_data{ other.m_data }, m_target{ other.m_target }
	{
		other.m_data = nullptr;
	}

	/*! \brief Moves data from other buffer */
	buffer_data& operator=(buffer_data&& other) {
		if (this != &other) {
			m_data = other.m_data;
			m_target = other.m_target;
			other.m_data = nullptr;
		}
		return *this;
	}

	// copying is disabled
	buffer_data(const buffer_data&) = delete;
	buffer_data& operator=(const buffer_data&) = delete;

	/*! \brief Unmaps buffer */
	~buffer_data() {
		if (m_data) {
			gl::glUnmapBuffer(m_target);
			m_data = nullptr;
		}
	}

	/*! \brief Converts buffer data object to pointer to data.
	*   \return Pointer to buffer data. */
	operator type*() const {
		return m_data;
	}

	/*! \brief Converts buffer data object to bool.
	*   \return true if buffer data exists. */
	explicit operator bool() const {
		return m_data != nullptr;
	}
private:
	friend class buffer<Element>;

	/*! \brief Creates empty buffer data object */
	buffer_data() : m_data{ nullptr }, m_target{ gl::GLenum::GL_ARRAY_BUFFER }
	{}

	/*! \brief Stores buffer target and its data.
	*   \param data pointer to data.
	*   \param target OpenGL target of buffer data. */
	buffer_data(type* const data, const gl::GLenum target)
		: m_data(data), m_target(target)
	{
		if (!m_data)
			throw glerror();
	}

	/*! \brief Maps whole gl buffer.
	*   \param target OpenGL target of buffer data.
	*   \param access buffer access type. */
	buffer_data(const gl::GLenum target, const gl::GLenum access)
		: buffer_data{ static_cast<type*>(gl::glMapBuffer(target, access)), target }
	{}

	/*! \brief Maps part of gl buffer.
	*   \param target OpenGL target of buffer data. 
	*   \param offset buffer offset.
	*   \param length buffer length.
	*   \param access buffer access type flags. */
	buffer_data(const gl::GLenum target, const gl::GLintptr offset, const gl::GLsizeiptr length, const gl::GLbitfield access)
		: buffer_data{ static_cast<type*>(gl::glMapBufferRange(target, offset, length, access)), target }
	{}

	type* m_data;
	gl::GLenum m_target;
};

/*! \brief Class for OpenGL buffer.
*   \param Element type of elements stored in buffer.
*   \param Target OpenGL target of buffer data. */
template<typename Element>
class buffer final {
public:
	using pointer = buffer_data<Element>;	//!< Buffer pointer type
	using size_type = gl::GLsizeiptr;

	/*! \brief Moves data from other buffer */
	buffer(buffer&& other)
		: m_glid(other.m_glid), m_target(other.m_target), m_usage(other.m_usage)
	{
		other.m_glid = none;
	}

	/*! \brief Moves data from other buffer */
	buffer& operator=(buffer&& other) {
		if (this != &other) {
			m_glid = other.m_glid;
			m_target = other.m_target;
			m_usage = other.m_usage;
			other.m_glid = none;
		}
		return *this;
	}

	// copying is disabled
	buffer(const buffer&) = delete;
	buffer& operator=(const buffer&) = delete;

	/*! \brief Deletes gl buffer */
	~buffer() {
		if (m_glid != none)
			gl::glDeleteBuffers(1, &m_glid);
	}

	/*! \return Number of elements in buffer. */
	size_type size() const {
		return m_size;
	}

	/*! \brief Binds buffer for OpenGL operations.
	*   \return true if buffer was bound. */
	bool bind() const {
		if (m_glid != none) {
			if (m_owner.bind()) {
				gl::glBindBuffer(m_target, m_glid);
				return true;
			}
		}

		return false;
	}

	/*! \brief Maps whole gl buffer.
	*   \return RAII wrapper on pointer to data buffer. */
	pointer map(const gl::GLenum access) const {
		if (bind())
			return { m_target, access };
		return {};
	}

	/*! \brief Maps part of gl buffer.
	*   \param offset buffer offset.
	*   \param length buffer length.
	*   \param access buffer access type flags.
	*   \return RAII wrapper on pointer to data buffer. */
	pointer map_range(const gl::GLintptr offset, const gl::GLsizeiptr length, const gl::GLbitfield access) const {
		if (bind())
			return { m_target, offset, length, access };
		return {};
	}
private:
	friend class vbo;

	/*! \brief Creates single OpenGL buffer
	*   \param owner vertex array object in which this buffer was created.
	*   \param size buffer size.
	*   \param target OpenGL target of buffer data.
	*   \param usage buffer usage type.*/
	buffer(const vbo& owner, const size_type size, const gl::GLenum target, const gl::GLenum usage)
		: m_owner(owner), m_glid(none), m_target(target), m_usage(usage), m_size(size)
	{
		gl::GLuint glid;
		gl::glGenBuffers(1, &glid);
		m_glid = glid;
		bind();
		gl::glBufferData(m_target, m_size * sizeof(Element), nullptr, m_usage);
	}

	static constexpr gl::GLuint none = 0;
	const vbo& m_owner;
	gl::GLuint m_glid;
	gl::GLenum m_target;
	gl::GLenum m_usage;
	size_type m_size;
};

}
