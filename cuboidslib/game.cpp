#include <cuboidslib/game.h>
#include <cuboidslib/ivisitor.h>


namespace cuboidslib {

game::game(const float worldSize, iship_factory& ship_factory)
	: m_player{ ship_factory.create(m_world) },
	m_walls{
		m_world.create_static_box({ 0.5f, 0.5, worldSize },{ -1.5f * worldSize, 0, 0 }),
		m_world.create_static_box({ 0.5f, 0.5, worldSize },{ 1.5 * worldSize, 0, 0 }),
    },
	m_worldSize(worldSize)
{
	m_world.gravity({ 0, 0, 0 });
}

float game::worldSize() const {
	return m_worldSize;
}

bool game::alive() const {
	return m_player->alive();
}

void game::left() {
	m_player->left();
}

void game::right() {
	m_player->right();
}

void game::shot() {
	auto newBullets = m_player->shot(m_world);
	std::move(
		std::begin(newBullets), std::end(newBullets),
		std::back_inserter(m_bullets)
	);
}

void game::update(const seconds delta) {
	m_world.update(delta);
	// Update objects
	m_player->update(delta);
	for (auto& b : m_bullets)
		b->update(delta);
	// Remove dead entities
	m_bullets.erase(
		std::remove_if(std::begin(m_bullets), std::end(m_bullets),
					   [](const auto& b) {return !b->alive(); }),
		m_bullets.end()
	);
}

void game::visit(ivisitor& v) const {
	// other objects
	for (const auto& b : m_bullets)
		b->visit(v);
	m_player->visit(v);
}

}
