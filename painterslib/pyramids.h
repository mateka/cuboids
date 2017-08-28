#pragma once

#include <gllib/vbo.h>
#include <gllib/program.h>
#include <utils/seconds.h>
#include <glm/glm.hpp>


namespace painterslib {

/*! \brief Base class for painting pyramids in OpenGL. */
class pyramids {
public:
	/*! \brief Data for each pyramid instance. */
	struct instance {
		glm::mat4 model;	//!< model matrix
		float intensity;	//!< color intensity

		/*! \brief Creates instance data.
		*   \param m model matrix.
		*   \param i color intensity. */
		instance(const glm::mat4& m, const float i = 1.0f)
			: model(m), intensity(i)
		{}
	};

	/*! \brief Creates painter, which paints pyramids
	* with different color in each vertex.
	*   \param max_instances max count of instances.
	*   \param apex apex color.
	*   \param left_top color of the top left vertex.
	*   \param right_top color of the top right vertex.
	*   \param left_bottom color of the bottom left vertex.
	*   \param right_bottom color of the bottom right vertex.*/
	pyramids(
		const std::size_t max_instances,
		const glm::vec4& apex,
		const glm::vec4& left_top,
		const glm::vec4& right_top,
		const glm::vec4& left_bottom,
		const glm::vec4& right_bottom
	);

	/*! \brief Creates painter, which paints pyramids
	* with the same color in each vertex.
	*   \param max_instances max count of instances.
	*   \param color vertices color.*/
	pyramids(
		const std::size_t max_instances,
		const glm::vec4& color
	);

	virtual ~pyramids() {}

	// moving is disabled
	pyramids(pyramids&&) = delete;
	pyramids& operator=(pyramids&&) = delete;

	// copying is disabled
	pyramids(const pyramids&) = delete;
	pyramids& operator=(const pyramids&) = delete;

	/*! \brief Update painter's state.
	*   \param pv project-view matrix.
	*   \param delta time from last update. */
	void update(const glm::mat4& pv, const utils::seconds delta);

	/*! \brief Paints pyramids. */
	void paint(const std::vector<instance>& instances) const;
private:
	// Helper vertex struct
	struct vertex {
		glm::vec3 position;
		glm::vec4 color;

		vertex(const glm::vec3& v = glm::vec3(), const glm::vec4& c = glm::vec4())
			: position{ v }, color{ c }
		{}
	};

	gllib::vbo m_vbo;
	gllib::buffer<vertex> m_vertices;
	gllib::buffer<instance> m_instances;
	gllib::program m_glsl;
};

}
