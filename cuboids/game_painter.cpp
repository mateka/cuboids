#include <cuboids/game_painter.h>
#include <cuboidslib/moving_ship.h>
#include <cuboidslib/bullet.h>
#include <gllib/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace cuboids {

game_painter::game_painter(const float worldSize)
	: m_shipPainter{
	    2,
		glm::vec4{1, 1, 1, 1},
		glm::vec4{1, 0, 0, 1}, glm::vec4{1, 1, 0, 1},
		glm::vec4{0, 1, 0, 1}, glm::vec4{0, 0, 1, 1}
	},
	m_bulletsPainter{512, glm::vec4{ 0.85f, 0, 0, 1 } },
	m_worldSize(worldSize)
{
	gl::glClearColor(0, 0, 0.5f, 1.0f);
}

void game_painter::update(const glapp::resolution& res, const utils::seconds delta) {
	/*const auto projection = glm::perspective(
		glm::radians(45.0f),
		res.width() / float(res.height()),
		0.1f, 100.0f
	);*/
	const auto ratio = res.width() / float(res.height());
	const auto projection = glm::ortho(
		ratio * -m_worldSize, ratio * m_worldSize,
		-m_worldSize, m_worldSize,
		0.1f, 100.0f
	);
	const auto camera = glm::lookAt(glm::vec3{ 0, 15, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0, -1 });
	m_pv = projection * camera;

	m_shipPainter.update(m_pv, delta);
	m_bulletsPainter.update(m_pv, delta);
}

void game_painter::paint(const cuboidslib::game& game) {
	// paint some fireworks
	game.visit(*this); // paint or gather instances to paint

	// paint cached objects
	m_bulletsPainter.paint(m_bullets);

	m_bullets.clear();
}

void game_painter::on_visit(const cuboidslib::moving_ship& s) {
	painterslib::pyramids::instance instance{ s.transform() };
	m_shipPainter.paint({ instance });
}

void game_painter::on_visit(const cuboidslib::bullet& b) {
	m_bullets.push_back(b.transform());
}

}
