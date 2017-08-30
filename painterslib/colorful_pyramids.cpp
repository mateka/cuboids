#include <painterslib/colorful_pyramids.h>
#include <gllib/shader.h>
#include "colorful_pyramid_geometry.glsl"
#include "colorful_pyramid_vertex.glsl"
#include "colorful_pyramid_fragment.glsl"


namespace painterslib {

colorful_pyramids::colorful_pyramids(
	const std::size_t maxInstances,
	const glm::vec4& apex,
	const glm::vec4& leftTop,
	const glm::vec4& rightTop,
	const glm::vec4& leftBottom,
	const glm::vec4& rightBottom
)
	: painter{
		{
			// top
			vertex{ { 0.0f, 0.0f, -0.5f }, apex },
			vertex{ { -0.5f, 0.5f, 0.5f }, leftTop },
			vertex{ { 0.5f, 0.5f, 0.5f }, rightTop },
			// right
			vertex{ { 0.0f, 0.0f, -0.5f }, apex },
			vertex{ { 0.5f, 0.5f, 0.5f }, rightTop },
			vertex{ { 0.5f, -0.5f, 0.5f }, rightBottom },
			// bottom
			vertex{ { 0.0f, 0.0f, -0.5f }, apex },
			vertex{ { -0.5f, -0.5f, 0.5f }, leftBottom },
			vertex{ { 0.5f, -0.5f, 0.5f }, rightBottom },
			// left
			vertex{ { 0.0f, 0.0f, -0.5f }, apex },
			vertex{ { -0.5f, -0.5f, 0.5f }, leftBottom },
			vertex{ { -0.5f, 0.5f, 0.5f }, leftTop },
			// back of the ship
			vertex{ { -0.5f, 0.5f, 0.5f }, leftTop },
			vertex{ { -0.5f, -0.5f, 0.5f }, leftBottom },
			vertex{ { 0.5f, 0.5f, 0.5f }, rightTop },
			vertex{ { 0.5f, -0.5f, 0.5f }, rightBottom },
			vertex{ { 0.5f, 0.5f, 0.5f }, rightTop },
			vertex{ { -0.5f, -0.5f, 0.5f }, leftBottom }
		},
		maxInstances,
		{
			gllib::shader{ gl::GLenum::GL_VERTEX_SHADER, colorful_pyramid::vertex },
			gllib::shader{ gl::GLenum::GL_GEOMETRY_SHADER, colorful_pyramid::geometry },
			gllib::shader{ gl::GLenum::GL_FRAGMENT_SHADER, colorful_pyramid::fragment }
		}
	}
{}


namespace details {
namespace colorful_pyramids {

gl::GLuint vertex::enable_attribs(const gllib::vbo& vbo, const gl::GLuint idx) {
	vbo.enable_array(idx);
	gl::glVertexAttribDivisor(idx, 0);
	gl::glVertexAttribPointer(idx, 3, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(vertex), nullptr);

	vbo.enable_array(idx + 1);
	gl::glVertexAttribDivisor(idx + 1, 0);
	gl::glVertexAttribPointer(idx + 1, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(vertex), (void*)sizeof(vertex::position));
	return idx + 2;

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
	return idx + 4;

}

}
}

}
