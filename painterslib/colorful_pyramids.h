#pragma once

#include <painterslib/painter.h>


namespace painterslib {

namespace details {
namespace colorful_pyramids {

/*! \brief Data for each pyramid vertex. */
struct vertex {
	glm::vec3 position;	//!< Vertex position
	glm::vec4 color;	//!< Vertex color

	/*! \brief Creates vertex data.
	*   \param v vertex position. 
	*   \param c vertex position. */
	vertex(const glm::vec3& v = glm::vec3(), const glm::vec4& c = glm::vec4())
		: position{ v }, color{ c }
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

	/*! \brief Creates instance data.
	*   \param m model matrix. */
	instance(const glm::mat4& m)
		: model(m)
	{}

	/*! \brief Enable generic vertex attributes in vbo from index idx.
	*   \param vbo vertex buffer object.
	*   \param idx index of first free attribute.
	*   \return Index of next, free generic vertex attribute. */
	static gl::GLuint enable_attribs(const gllib::vbo& vbo, const gl::GLuint idx);
};

}
}


/*! \brief Class for painting colorful pyramids in OpenGL. */
class colorful_pyramids final : public painter<
	details::colorful_pyramids::vertex, details::colorful_pyramids::instance
> {
public:
	/*! \brief Creates painter, which paints pyramids
	*   with different color in each vertex.
	*   \param maxInstances max count of instances.
	*   \param apex apex color.
	*   \param left_top color of the top left vertex.
	*   \param right_top color of the top right vertex.
	*   \param left_bottom color of the bottom left vertex.
	*   \param right_bottom color of the bottom right vertex.*/
	colorful_pyramids(
		const std::size_t maxInstances,
		const glm::vec4& apex,
		const glm::vec4& leftTop,
		const glm::vec4& rightTop,
		const glm::vec4& leftBottom,
		const glm::vec4& rightBottom
	);
};

}
