#pragma once

#include <gllib/vbo.h>
#include <gllib/program.h>
#include <utils/seconds.h>
#include <glm/glm.hpp>


namespace painterslib {

/*! \brief Base class for painting cuboids in OpenGL. */
class cuboids {
public:
	/*! \brief Data for each pyramid instance. */
	struct instance {
		glm::mat4 model;	//!< model matrix

		/*! \brief Creates instance data.
		*   \param m model matrix. */
		instance(const glm::mat4& m)
			: model(m)
		{}
	};

	/*! \brief Creates painter, which paints cuboids
	* with the same color in each vertex.
	*   \param max_instances max count of instances.
	*   \param color vertices color.*/
	cuboids(
		const std::size_t max_instances,
		const glm::vec4& color
	);

	virtual ~cuboids() {}

	// moving is disabled
	cuboids(cuboids&&) = delete;
	cuboids& operator=(cuboids&&) = delete;

	// copying is disabled
	cuboids(const cuboids&) = delete;
	cuboids& operator=(const cuboids&) = delete;

	/*! \brief Update painter's state.
	*   \param pv project-view matrix.
	*   \param delta time from last update. */
	void update(const glm::mat4& pv, const utils::seconds delta);

	/*! \brief Paints cuboids. */
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
