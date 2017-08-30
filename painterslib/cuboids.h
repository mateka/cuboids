#pragma once

#include <gllib/vbo.h>
#include <gllib/program.h>
#include <utils/seconds.h>
#include <glm/glm.hpp>


namespace painterslib {

/*! \brief Class for painting cuboids in OpenGL. */
class cuboids final {
public:
	/*! \brief Data for each pyramid instance. */
	struct instance {
		glm::mat4 model;	//!< model matrix
		glm::vec4 color;	//!< instance color

		/*! \brief Creates instance data.
		*   \param m model matrix.
		*   \param c instance color. */
		instance(const glm::mat4& m, const glm::vec4& c)
			: model(m), color(c)
		{}
	};

	/*! \brief Creates painter, which paints cuboids
	* with the same color in each vertex.
	*   \param max_instances max count of instances. */
	cuboids(const std::size_t max_instances);

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

		vertex(const glm::vec3& v = glm::vec3())
			: position{ v }
		{}
	};

	gllib::vbo m_vbo;
	gllib::buffer<vertex> m_vertices;
	gllib::buffer<instance> m_instances;
	gllib::program m_glsl;
};

}
