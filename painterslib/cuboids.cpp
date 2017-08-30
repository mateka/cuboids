#include <painterslib/cuboids.h>
#include <gllib/shader.h>
#include "cuboid_geometry.glsl"
#include "cuboid_vertex.glsl"
#include "cuboid_fragment.glsl"


namespace painterslib {

cuboids::cuboids(const std::size_t maxInstances)
	: painter{
		{
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
		},
		maxInstances,
		{
			gllib::shader{ gl::GLenum::GL_VERTEX_SHADER, cuboid::vertex },
			gllib::shader{ gl::GLenum::GL_GEOMETRY_SHADER, cuboid::geometry },
			gllib::shader{ gl::GLenum::GL_FRAGMENT_SHADER, cuboid::fragment }
		}
	}
{}


namespace details {
namespace cuboids {

gl::GLuint vertex::enable_attribs(const gllib::vbo& vbo, const gl::GLuint idx) {
	vbo.enable_array(idx);
	gl::glVertexAttribDivisor(idx, 0);
	gl::glVertexAttribPointer(idx, 3, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(vertex), nullptr);
	return idx + 1;
}

gl::GLuint instance::enable_attribs(const gllib::vbo& vbo, const gl::GLuint idx) {
	vbo.enable_array(idx);
	gl::glVertexAttribDivisor(idx, 1);
	gl::glVertexAttribPointer(idx, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(instance), nullptr);
	vbo.enable_array(idx + 1);
	gl::glVertexAttribDivisor(idx + 1, 1);
	gl::glVertexAttribPointer(idx + 1, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(instance), (void*)sizeof(glm::vec4));
	vbo.enable_array(idx + 2);
	gl::glVertexAttribDivisor(idx + 2, 1);
	gl::glVertexAttribPointer(idx + 2, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(instance), (void*)(2 * sizeof(glm::vec4)));
	vbo.enable_array(idx + 3);
	gl::glVertexAttribDivisor(idx + 3, 1);
	gl::glVertexAttribPointer(idx + 3, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(instance), (void*)(3 * sizeof(glm::vec4)));

	vbo.enable_array(idx + 4);
	gl::glVertexAttribDivisor(idx + 4, 1);
	gl::glVertexAttribPointer(idx + 4, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(instance), (void*)sizeof(instance::model));
	return idx + 5;
}

}
}

}
