#include <cuboids/cuboids_glapp.h>
#include <glapp/include_glfw.h>
#include <iostream>
#include <chrono>


using namespace std::chrono_literals;

namespace cuboids {

cuboids_glapp::cuboids_glapp(const cuboids_glapp::params_type& params)
	: app{ params }, m_gameSize{ 6.0f }, m_shipFactory{ {0, 0, 5}, 5.0f },
	m_game{ new_game() },
	m_painter{ m_gameSize, m_game->max_bullets(), m_game->max_cuboids(), m_game->max_explosions() },
	m_showFPS{ false }
{
	std::cout
		<< "OpenGL version: " << glversion() << "\n"
		<< "\nKeys:\n"
		<< "\t left arrow\t- move left\n"
		<< "\t right arrow\t- move right\n"
		<< "\t space\t- shoot\n"
		<< "\t f\t- show FPS\n"
		<< "\t b\t- show bunding boxes"
		<< std::endl;
}

void cuboids_glapp::update(const seconds delta) {
	handle_input();

	const auto ratio = view_resolution().width() / float(view_resolution().height());
	m_game->update(ratio, delta);
	m_painter.update(ratio, delta);

	m_painter.paint(*m_game);

	if (!m_game->playable())
		m_game = new_game();

	if (m_showFPS)
		std::cout << "FPS: " << 1.0 / delta.count() << std::endl;
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
	else
		m_game->stop();

	// other keys
	static bool b_was_pressed = false;
	b_was_pressed = get_key(GLFW_KEY_B) == GLFW_PRESS;
	if (b_was_pressed && get_key(GLFW_KEY_B) == GLFW_RELEASE)
		m_painter.toogle_boxes();

	static bool f_was_pressed = false;
	f_was_pressed = get_key(GLFW_KEY_F) == GLFW_PRESS;
	if (f_was_pressed && get_key(GLFW_KEY_F) == GLFW_RELEASE)
		m_showFPS = !m_showFPS;
}

std::unique_ptr<cuboidslib::cuboid_factory> cuboids_glapp::cuboids_factory() {
	return std::make_unique<cuboidslib::cuboid_factory>(
		m_randomness(), 2s, m_gameSize, 1.5f, 0.10f
	);
}

std::unique_ptr<cuboidslib::game> cuboids_glapp::new_game() {
	return std::make_unique<cuboidslib::game>(
		m_gameSize, m_shipFactory, cuboids_factory(), 1024, 1024, 1024
	);
}

}
