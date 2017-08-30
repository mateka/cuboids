#pragma once

#include <gllib/vbo.h>
#include <gllib/program.h>
#include <utils/seconds.h>
#include <glm/glm.hpp>
#include <array>
#include <initializer_list>


namespace painterslib {

/*! \brief Base class for OpenGL painters. */
template<typename Vertex, typename Instance>
class painter {
public:
	using vertex = Vertex;	//!< Type for vertices data
	using instance = Instance;	//!< Type for instances data

	/*! \brief Creates new painter.
	*   \param vertices vertices data.
	*   \param maxInstances max count of instances.
	*   \param shaders shaders for this painter. */
	painter(
		const std::initializer_list<vertex>& vertices,
		const std::size_t maxInstances,
		const std::initializer_list<gllib::shader>& shaders
	)
		: m_vertices{
			m_vbo.create_buffer<vertex>(vertices.size(), gl::GLenum::GL_ARRAY_BUFFER, gl::GLenum::GL_STATIC_DRAW)
		}, m_instances{
			m_vbo.create_buffer<instance>(maxInstances, gl::GLenum::GL_ARRAY_BUFFER, gl::GLenum::GL_DYNAMIC_DRAW)
		}, m_glsl{ shaders }
	{
		std::copy(
			std::cbegin(vertices), std::cend(vertices),
			static_cast<vertex*>(m_vertices.map(gl::GLenum::GL_WRITE_ONLY))
		);
	}

	// moving is disabled
	painter(painter&&) = delete;
	painter& operator=(painter&&) = delete;

	// copying is disabled
	painter(const painter&) = delete;
	painter& operator=(const painter&) = delete;

	virtual ~painter() {}

	/*! \brief Update painter's state.
	*   \param pv project-view matrix.
	*   \param delta time from last update. */
	void update(const glm::mat4& pv, const utils::seconds delta) {
		m_glsl.matrix("pv", pv);
	}

	/*! \brief Paints pyramids. */
	void paint(const std::vector<instance>& instances) const {
		m_glsl.use();

		// Prepare vertex buffer
		m_vertices.bind();
		auto attribute = vertex::enable_attribs(m_vbo, 0);

		// Prepare instances  buffer
		m_instances.bind();
		std::copy(
			std::cbegin(instances), std::cend(instances),
			static_cast<instance*>(m_instances.map(gl::GLenum::GL_WRITE_ONLY))
		);
		attribute = instance::enable_attribs(m_vbo, attribute);

		// Draw
		gl::glDrawArraysInstanced(
			gl::GLenum::GL_TRIANGLES, 0,
			static_cast<gl::GLsizei>(m_vertices.size()),
			static_cast<gl::GLsizei>(instances.size())
		);
	}
private:
	gllib::vbo m_vbo;
	gllib::buffer<vertex> m_vertices;
	gllib::buffer<instance> m_instances;
	gllib::program m_glsl;
};

}
