#pragma once

#include <painterslib/painter.h>


namespace painterslib {

namespace details {
namespace pyramids {

/*! \brief Data for each pyramid vertex. */
struct vertex {
	glm::vec3 position;	//!< Vertex position

	/*! \brief Creates vertex data.
	*   \param v vertex position. */
	vertex(const glm::vec3& v = glm::vec3())
		: position{ v }
	{}

	/*! \brief Enable generic vertex attributes in vbo from index idx.
	*   \param vbo vertex buffer object.
	*   \param idx index of first free attribute.
	*   \return Index of next, free generic vertex attribute. */
	static gl::GLuint enable_attribs(const gllib::vbo& vbo, const gl::GLuint idx);
};


/*! \brief Data for each pyramid instance. */
struct instance {
	glm::mat4 model;	//!< model matrix
	glm::vec4 color;	//!< instance color
	float intensity;	//!< color intensity

	/*! \brief Creates instance data.
	*   \param m model matrix.
	*   \param c instance color.
	*   \param i color intensity. */
	instance(const glm::mat4& m, const glm::vec4& c, const float i = 1.0f)
		: model(m), color(c), intensity(i)
	{}

	/*! \brief Enable generic vertex attributes in vbo from index idx.
	*   \param vbo vertex buffer object.
	*   \param idx index of first free attribute.
	*   \return Index of next, free generic vertex attribute. */
	static gl::GLuint enable_attribs(const gllib::vbo& vbo, const gl::GLuint idx);
};

}
}


/*! \brief Class for painting pyramids in OpenGL. */
class pyramids final : public painter<
	details::pyramids::vertex, details::pyramids::instance
> {
public:
	/*! \brief Creates painter, which paints pyramids
	*   with the same color in each vertex.
	*   \param maxInstances max count of instances. */
	pyramids(const std::size_t maxInstances);
};

}
