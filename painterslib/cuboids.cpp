#include <painterslib/cuboids.h>
#include <gllib/shader.h>
#include "cuboid_geometry.glsl"
#include "cuboid_vertex.glsl"
#include "cuboid_fragment.glsl"


namespace painterslib {

cuboids::cuboids(const std::size_t max_instances)
	: m_vertices{
		m_vbo.create_buffer<vertex>(3 * 2 * 6, gl::GLenum::GL_ARRAY_BUFFER, gl::GLenum::GL_STATIC_DRAW)
	}, m_instances{
		m_vbo.create_buffer<instance>(max_instances, gl::GLenum::GL_ARRAY_BUFFER, gl::GLenum::GL_DYNAMIC_DRAW)
	}, m_glsl{
		gllib::shader{ gl::GLenum::GL_VERTEX_SHADER, cuboid::vertex },
		gllib::shader{ gl::GLenum::GL_GEOMETRY_SHADER, cuboid::geometry },
		gllib::shader{ gl::GLenum::GL_FRAGMENT_SHADER, cuboid::fragment }
	}
{
	const std::array<vertex, 3 * 2 * 6> data{
		// top
		vertex{ { -0.5f, 0.5f, -0.5f } },
		vertex{ { 0.5f, 0.5f, -0.5f } },
		vertex{ { 0.5f, 0.5f, 0.5f } },

		vertex{ { -0.5f, 0.5f, -0.5f } },
		vertex{ { 0.5f, 0.5f, 0.5f } },
		vertex{ { -0.5f, 0.5f, 0.5f } },
		// bottom
		vertex{ { -0.5f, -0.5f, -0.5f } },
		vertex{ { 0.5f, -0.5f, 0.5f } },
		vertex{ { 0.5f, -0.5f, -0.5f } },

		vertex{ { -0.5f, -0.5f, -0.5f } },
		vertex{ { -0.5f, -0.5f, 0.5f } },
		vertex{ { 0.5f, -0.5f, 0.5f } },
		// right
		vertex{ { 0.5f, 0.5f, -0.5f } },
		vertex{ { 0.5f, -0.5f, 0.5f } },
		vertex{ { 0.5f, 0.5f, 0.5f } },

		vertex{ { 0.5f, -0.5f, 0.5f } },
		vertex{ { 0.5f, 0.5f, -0.5f } },
		vertex{ { 0.5f, -0.5f, -0.5f } },
		// left
		vertex{ { -0.5f, 0.5f, -0.5f } },
		vertex{ { -0.5f, 0.5f, 0.5f } },
		vertex{ { -0.5f, -0.5f, 0.5f } },

		vertex{ { -0.5f, -0.5f, 0.5f } },
		vertex{ { -0.5f, -0.5f, -0.5f } },
		vertex{ { -0.5f, 0.5f, -0.5f } },
		// front
		vertex{ { -0.5f, 0.5f, -0.5f } },
		vertex{ { 0.5f, 0.5f, -0.5f } },
		vertex{ { -0.5f, -0.5f, -0.5f } },

		vertex{ { 0.5f, -0.5f, -0.5f } },
		vertex{ { 0.5f, 0.5f, -0.5f } },
		vertex{ { -0.5f, -0.5f, -0.5f } },
		// back
		vertex{ { -0.5f, 0.5f, 0.5f } },
		vertex{ { -0.5f, -0.5f, 0.5f } },
		vertex{ { 0.5f, 0.5f, 0.5f } },

		vertex{ { 0.5f, -0.5f, 0.5f } },
		vertex{ { -0.5f, -0.5f, 0.5f } },
		vertex{ { 0.5f, 0.5f, 0.5f } }
	};

	std::copy(
		std::cbegin(data), std::cend(data),
		static_cast<vertex*>(m_vertices.map(gl::GLenum::GL_WRITE_ONLY))
	);
}

void cuboids::update(const glm::mat4& pv, const utils::seconds delta) {
	m_glsl.matrix("pv", pv);
}

void cuboids::paint(const std::vector<instance>& instances) const {
	m_glsl.use();
	
	// Prepare vertex buffer
	m_vertices.bind();

	m_vbo.enable_array(0);
	gl::glVertexAttribDivisor(0, 0);
	gl::glVertexAttribPointer(0, 3, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(vertex), nullptr);

	// Prepare instances buffer
	m_instances.bind();

	std::copy(
		std::cbegin(instances), std::cend(instances),
		static_cast<instance*>(m_instances.map(gl::GLenum::GL_WRITE_ONLY))
	);

	m_vbo.enable_array(1);
	gl::glVertexAttribDivisor(1, 1);
	gl::glVertexAttribPointer(1, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(instance), nullptr);
	m_vbo.enable_array(2);
	gl::glVertexAttribDivisor(2, 1);
	gl::glVertexAttribPointer(2, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(instance), (void*)sizeof(glm::vec4));
	m_vbo.enable_array(3);
	gl::glVertexAttribDivisor(3, 1);
	gl::glVertexAttribPointer(3, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(instance), (void*)(2 * sizeof(glm::vec4)));
	m_vbo.enable_array(4);
	gl::glVertexAttribDivisor(4, 1);
	gl::glVertexAttribPointer(4, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(instance), (void*)(3 * sizeof(glm::vec4)));

	m_vbo.enable_array(5);
	gl::glVertexAttribDivisor(5, 1);
	gl::glVertexAttribPointer(5, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(instance), (void*)sizeof(instance::model));

	// Draw
	gl::glDrawArraysInstanced(
		gl::GLenum::GL_TRIANGLES, 0,
		static_cast<gl::GLsizei>(m_vertices.size()),
		static_cast<gl::GLsizei>(instances.size())
	);
}

}
