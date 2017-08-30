#pragma once

#include <painterslib/painter.h>


namespace painterslib {

namespace details {
namespace cuboids {

/*! \brief Data for each cuboid vertex. */
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


/*! \brief Data for each cuboid instance. */
struct instance {
	glm::mat4 model;	//!< model matrix
	glm::vec4 color;	//!< instance color

	/*! \brief Creates instance data.
	*   \param m model matrix.
	*   \param c instance color. */
	instance(const glm::mat4& m, const glm::vec4& c)
		: model(m), color(c)
	{}

	/*! \brief Enable generic vertex attributes in vbo from index idx.
	*   \param vbo vertex buffer object.
	*   \param idx index of first free attribute.
	*   \return Index of next, free generic vertex attribute. */
	static gl::GLuint enable_attribs(const gllib::vbo& vbo, const gl::GLuint idx);
};

}
}


/*! \brief Class for painting cuboids in OpenGL. */
class cuboids final : public painter<
	details::cuboids::vertex, details::cuboids::instance
> {
public:
	/*! \brief Creates painter, which paints cuboids
	*   with the same color in each vertex.
	*   \param maxInstances max count of instances. */
	cuboids(const std::size_t maxInstances);
};

}
