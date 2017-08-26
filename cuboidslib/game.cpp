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

void game::left() {
	m_player->left();
}

void game::right() {
	m_player->right();
}

void game::shot() {
	m_player->shot();
}

void game::update(const seconds delta) {
	m_world.update(delta);
	m_player->update(delta);
}

void game::visit(ivisitor& v) const {
	// other objects
	m_player->visit(v);
}

}
