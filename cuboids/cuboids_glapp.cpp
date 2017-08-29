#include <cuboids/cuboids_glapp.h>
#include <iostream>
#include <glapp/include_glfw.h>
#include <cuboidslib/cuboid_factory.h>
#include <chrono>


using namespace std::chrono_literals;

namespace cuboids {

cuboids_glapp::cuboids_glapp(const cuboids_glapp::params_type& params)
	: app{ params }, m_shipFactory{ {0, 0, 5}, 3.0f },
	m_game{ std::make_unique<cuboidslib::game>(6.0f, m_shipFactory, std::make_unique<cuboidslib::cuboid_factory>(2s)) },
	m_painter{ m_game->worldSize() }
{
	std::cout << "OpenGL version: " << glversion() << std::endl;
}

void cuboids_glapp::update(const seconds delta) {
	handle_input();

	const auto ratio = view_resolution().width() / float(view_resolution().height());
	m_game->update(ratio, delta);
	m_painter.update(ratio, delta);

	m_painter.paint(*m_game);

	if (!m_game->playable())
		m_game = std::make_unique<cuboidslib::game>(6.0f, m_shipFactory, std::make_unique<cuboidslib::cuboid_factory>(2s));

	//std::cout << "FPS: " << 1.0 / delta.count() << std::endl;
}

void cuboids_glapp::handle_input() {
	const auto left = get_key(GLFW_KEY_LEFT) == GLFW_PRESS;
	const auto right = get_key(GLFW_KEY_RIGHT) == GLFW_PRESS;
	const auto space = get_key(GLFW_KEY_SPACE) == GLFW_PRESS;

	if (space)
		m_game->shot();
	if (left && !right)
		m_game->left();
	else if (!left && right)
		m_game->right();
}

}
