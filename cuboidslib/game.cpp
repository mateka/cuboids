#include <cuboidslib/game.h>
#include <cuboidslib/ivisitor.h>


namespace cuboidslib {

game::game(
	const float worldSize,
	iship_factory& ship_factory,
	std::unique_ptr<icuboid_factory> cuboids_factory
)
	: m_player{ ship_factory.create(m_world) },
	m_cuboidsFactory{ std::move(cuboids_factory) },
	m_walls{
		m_world.create_static_box({ 0.5f, 0.5, worldSize },{ -worldSize - 0.5, 0, 0 }),
		m_world.create_static_box({ 0.5f, 0.5, worldSize },{ worldSize + 0.5, 0, 0 }),
    },
	m_worldSize(worldSize)
{
	m_world.gravity({ 0, 0, 0 });
	m_walls[0]->restitution(0.5f);
	m_walls[1]->restitution(0.5f);
}

float game::worldSize() const {
	return m_worldSize;
}

bool game::playable() const {
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

void game::update(const float screenRatio, const seconds delta) {
	// Move walls to screen edges
	m_walls[0]->position({ -screenRatio * m_worldSize - 0.5, 0, 0 });
	m_walls[1]->position({ screenRatio * m_worldSize + 0.5, 0, 0 });
	// Update simulation
	m_world.update(delta);
	// Update objects
	m_player->update(delta);
	m_cuboidsFactory->update(delta);
	for (auto& b : m_bullets)
		b->update(delta);
	for (auto& c : m_cuboids)
		c->update(delta);
	// Add new cuboids
	auto newCuboids = m_cuboidsFactory->create(m_world);
	std::move(
		std::begin(newCuboids), std::end(newCuboids),
		std::back_inserter(m_cuboids)
	);
	// Remove dead entities
	m_bullets.erase(
		std::remove_if(std::begin(m_bullets), std::end(m_bullets),
					   [](const auto& b) {return !b->alive(); }),
		m_bullets.end()
	);
	m_cuboids.erase(
		std::remove_if(std::begin(m_cuboids), std::end(m_cuboids),
			[](const auto& c) {return !c->alive(); }),
		m_cuboids.end()
	);
}

void game::visit(ivisitor& v) const {
	for (const auto& c : m_cuboids)
		c->visit(v);
	for (const auto& b : m_bullets)
		b->visit(v);
	m_player->visit(v);
}

}
