#include <cuboids/game_painter.h>
#include <cuboidslib/moving_ship.h>
#include <cuboidslib/bullet.h>
#include <cuboidslib/rocket.h>
#include <cuboidslib/cuboid.h>
#include <gllib/gl.h>
#include <glm/gtc/matrix_transform.hpp>


namespace cuboids {

game_painter::game_painter(
	const float worldSize,
	const std::size_t maxBullets,
	const std::size_t maxCuboids,
	const std::size_t maxExplosions
)
	: m_shipPainter{
	    1,
		glm::vec4{1, 1, 1, 1},
		glm::vec4{1, 0, 0, 1}, glm::vec4{1, 1, 0, 1},
		glm::vec4{0, 1, 0, 1}, glm::vec4{0, 0, 1, 1}
	},
	m_bulletsPainter{ maxBullets + 5 * maxCuboids },
	m_cuboidsPainter{ 1 + maxCuboids + maxBullets + maxExplosions },
	m_bulletColor{ 0.85f, 0.65f, 0, 1 }, m_rocketColor{ 0.85f, 0, 0, 1 },
	m_worldSize{ worldSize }, m_showBoxes{ false }
{
	gl::glClearColor(0, 0, 0, 0);

	m_bullets.reserve(maxBullets + 5 * maxCuboids);
	m_cuboids.reserve(maxCuboids + maxBullets + maxExplosions);
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
		b.transform(), m_bulletColor,
		1.0f - static_cast<float>(b.lived() / b.life_span())
	});
	if (m_showBoxes)
		m_cuboids.push_back({ b.transform(), glm::vec4{ 0, 0.95f, 0, 1 } });
}

void game_painter::on_visit(const cuboidslib::rocket& r) {
	m_bullets.push_back({
		r.transform(), m_rocketColor,
		1.0f - static_cast<float>(r.lived() / r.life_span())
	});
	if (m_showBoxes)
		m_cuboids.push_back({ r.transform(), glm::vec4{ 0, 0.95f, 0, 1 } });
}

void game_painter::on_visit(const cuboidslib::cuboid& c) {
	m_cuboids.push_back({ c.transform(), glm::vec4{ 0.65f, 0.65f, 0.65f, 1 } });
}

void game_painter::on_visit(const cuboidslib::crate& c) {
	const auto transform = c.transform();
	m_cuboids.push_back({ transform, glm::vec4{ 0.55f, 0.27f, 0.08f, 1 } });
	add_crate_contents(transform, c.model());
}

void game_painter::on_visit(const cuboidslib::explosion& e) {
	const auto ratio = e.lived() / e.life_span();
	m_cuboids.push_back({ e.transform(), glm::vec4{ 1, 1 - ratio, 0, 0.5 } });
}

namespace {

int bullets_count(const cuboidslib::gun_model gun) {
	switch (gun) {
	case cuboidslib::gun_model::wingman:
		return 2;
	case cuboidslib::gun_model::spray3:
		return 3;
	case cuboidslib::gun_model::spray5:
		return 5;
	case cuboidslib::gun_model::bazooka:
		return 1;
	case cuboidslib::gun_model::patriots:
		return 2;
	case cuboidslib::gun_model::boombastic3:
		return 3;
	default:
		return 1;
	}
}

}

void game_painter::add_crate_contents(
	const glm::mat4& transform,
	const cuboidslib::gun_model gun
) {
	using namespace cuboidslib;

	const auto color = gun_color(gun);
	const auto count = bullets_count(gun);
	auto world = transform;
	world *= glm::rotate(glm::mat4{}, 45.0f, glm::vec3{ 0, 1, 1 });
	world *= glm::scale(glm::mat4{}, (count > 1 ? 0.5f: 1.0f) * glm::vec3{ 1 });
	const auto item_scale = glm::scale(glm::mat4{}, 0.3f * glm::vec3{ 1, 1, 2 });
	// Add pyramids
	if (gun == gun_model::wingman || gun == gun_model::patriots) {
		const auto left = glm::translate(glm::mat4(), glm::vec3{ -0.3f, 0, 0 });
		const auto right = glm::translate(glm::mat4(), glm::vec3{ 0.3f, 0, 0 });
		m_bullets.push_back({ world * left * item_scale, color, 1.0 });
		m_bullets.push_back({ world * right * item_scale, color, 1.0 });
	}
	else {
		for (int i = 0; i < count; ++i) {
			const auto a = i - count / 2;
			auto model = glm::translate(glm::mat4{}, glm::vec3{ 0, 0, 1 });
			model *= glm::rotate(glm::mat4{}, a * 0.5f, glm::vec3{ 0, 1, 0 });
			model *= glm::translate(glm::mat4{}, glm::vec3{ 0, 0, -1 });
			model *= item_scale;
			m_bullets.push_back({world * model, color, 1.0 });
		}
	}
}

glm::vec4 game_painter::gun_color(const cuboidslib::gun_model gun) {
	switch (gun) {
	case cuboidslib::gun_model::bazooka:
	case cuboidslib::gun_model::patriots:
	case cuboidslib::gun_model::boombastic3:
		return m_rocketColor;
	default:
		return m_bulletColor;
	}
}

}
