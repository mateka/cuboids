#include <cuboids/game_painter.h>
#include <cuboidslib/moving_ship.h>
#include <cuboidslib/bullet.h>
#include <cuboidslib/cuboid.h>
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
	m_bulletsPainter{ 512, glm::vec4{ 0.85f, 0.65f, 0, 1 } },
	m_cuboidsPainter{ 512, glm::vec4{ 0.65f, 0.65f, 0.65f, 1 } },
	m_worldSize(worldSize)
{
	gl::glClearColor(0, 0, 0, 1.0f);
}

void game_painter::update(const float screenRatio, const utils::seconds delta) {
	const auto projection = glm::ortho(
		screenRatio * -m_worldSize, screenRatio * m_worldSize,
		-m_worldSize, m_worldSize,
		0.1f, 100.0f
	);
	const auto camera = glm::lookAt(glm::vec3{ 0, 15, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0, -1 });
	m_pv = projection * camera;

	m_shipPainter.update(m_pv, delta);
	m_bulletsPainter.update(m_pv, delta);
	m_cuboidsPainter.update(m_pv, delta);
}

void game_painter::paint(const cuboidslib::game& game) {
	// paint some fireworks
	game.visit(*this); // paint or gather instances to paint

	// paint cached objects
	m_bulletsPainter.paint(m_bullets);
	m_cuboidsPainter.paint(m_cuboids);

	// clear caches
	m_bullets.clear();
	m_cuboids.clear();
}

void game_painter::on_visit(const cuboidslib::moving_ship& s) {
	m_shipPainter.paint({ s.transform() });
}

void game_painter::on_visit(const cuboidslib::bullet& b) {
	m_bullets.push_back({
		b.transform(),
		1.0f - static_cast<float>(b.lived() / b.life_span())
	});
}

void game_painter::on_visit(const cuboidslib::cuboid& c) {
	m_cuboids.push_back({ c.transform() });
}

}
