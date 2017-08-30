#include <cuboids/game_painter.h>
#include <cuboidslib/moving_ship.h>
#include <cuboidslib/bullet.h>
#include <cuboidslib/cuboid.h>
#include <cuboidslib/crate.h>
#include <gllib/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace cuboids {

game_painter::game_painter(
	const float worldSize,
	const std::size_t maxBullets,
	const std::size_t maxCuboids
)
	: m_shipPainter{
	    1,
		glm::vec4{1, 1, 1, 1},
		glm::vec4{1, 0, 0, 1}, glm::vec4{1, 1, 0, 1},
		glm::vec4{0, 1, 0, 1}, glm::vec4{0, 0, 1, 1}
	},
	m_bulletsPainter{ maxBullets },
	m_cuboidsPainter{ maxCuboids + 1 + maxBullets },
	m_worldSize{ worldSize }, m_showBoxes{ false }
{
	gl::glClearColor(0, 0, 0, 0);
}

void game_painter::toogle_boxes() {
	m_showBoxes = !m_showBoxes;
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
	// TODO: paint some fireworks in the background

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
	if (m_showBoxes)
		m_cuboids.push_back({ s.transform(), glm::vec4{ 0, 0.95f, 0, 1 } });
}

void game_painter::on_visit(const cuboidslib::bullet& b) {
	m_bullets.push_back({
		b.transform(), glm::vec4{ 0.85f, 0.65f, 0, 1 },
		1.0f - static_cast<float>(b.lived() / b.life_span())
	});
	if (m_showBoxes)
		m_cuboids.push_back({ b.transform(), glm::vec4{ 0, 0.95f, 0, 1 } });
}

void game_painter::on_visit(const cuboidslib::cuboid& c) {
	m_cuboids.push_back({ c.transform(), glm::vec4{ 0.65f, 0.65f, 0.65f, 1 } });
}

void game_painter::on_visit(const cuboidslib::crate& c) {
	m_cuboids.push_back({ c.transform(), glm::vec4{ 0.55f, 0.27f, 0.08f, 1 } });
}

}
