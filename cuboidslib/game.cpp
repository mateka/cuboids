#include <cuboidslib/game.h>
#include <cuboidslib/ivisitor.h>
#include <cuboidslib/collision_dispatcher.h>
#include <chrono>

using namespace std::chrono_literals;

namespace cuboidslib {

namespace {

template<typename T>
void add_objects(
	std::vector<std::unique_ptr<T>>& newObjects,
	std::vector<std::unique_ptr<T>>& objects,
	std::unordered_map<const physicslib::body*, icuboid_object*>& objectsMap
) {
	for (auto& c : newObjects)
		objectsMap[c->body()] = c.get();
	std::move(
		std::begin(newObjects), std::end(newObjects),
		std::back_inserter(objects)
	);
}

template<typename T>
void update_objects(const seconds delta, const std::vector<std::unique_ptr<T>>& objects) {
	for (auto& o : objects)
		o->update(delta);
}

template<typename T>
void remove_dead_objects(
	std::vector<std::unique_ptr<T>>& objects,
	std::unordered_map<const physicslib::body*, icuboid_object*>& objectsMap
) {
	std::vector<const physicslib::body*> toRemove;
	for (const auto& o : objectsMap) {
		if (!o.second->alive())
			toRemove.push_back(o.first);
	}
	for (const auto pk : toRemove)
		objectsMap.erase(pk);

	objects.erase(
		std::remove_if(std::begin(objects), std::end(objects),
			[](const auto& b) {return !b->alive(); }),
		objects.end()
	);
}

template<typename T>
void remove_oldest_objects(
	std::vector<std::unique_ptr<T>>& objects,
	std::unordered_map<const physicslib::body*, icuboid_object*>& objectsMap,
	const std::size_t maxSize
) {
	const auto count = maxSize < objects.size() ? objects.size() - maxSize : 0;
	for (std::size_t i = 0; i < count; ++i)
		objects[i]->die();
	remove_dead_objects(objects, objectsMap);
}

}

game::game(
	const float worldSize,
	iship_factory& ship_factory,
	std::unique_ptr<icuboid_factory> cuboids_factory,
	const std::size_t maxBullets,
	const std::size_t maxCuboids,
	const std::size_t maxExplosions
)
	: m_world([this](const physicslib::body* a, const physicslib::body* b) -> void {
		const auto itA = m_objects.find(a);
		const auto itB = m_objects.find(b);
		if (itA != m_objects.end() && itB != m_objects.end())
			itA->second->visit(collision_dispatcher(*this, *itB->second));
	}),
	m_player{ ship_factory.create(m_world) },
	m_cuboidsFactory{ std::move(cuboids_factory) },
	m_walls{
		m_world.create_static_box({ 0.5f, 0.5, 2 * worldSize },{ -worldSize - 0.5, 0, 0 }),
		m_world.create_static_box({ 0.5f, 0.5, 2 * worldSize },{ worldSize + 0.5, 0, 0 }),
    },
	m_worldSize{ worldSize }, m_maxBullets{ maxBullets }, m_maxCuboids{ maxCuboids },
	m_maxExplosions{ maxExplosions }
{
	m_world.gravity({ 0, 0, 0 });
	m_walls[0]->restitution(0.5f);
	m_walls[1]->restitution(0.5f);

	m_objects[m_player->body()] = m_player.get();
}

float game::world_size() const {
	return m_worldSize;
}

std::size_t game::max_bullets() const {
	return m_maxBullets;
}

std::size_t game::max_cuboids() const {
	return m_maxCuboids;
}

std::size_t game::max_explosions() const {
	return m_maxExplosions;
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

void game::stop() {
	m_player->stop();
}

void game::shot() {
	add_objects(m_player->shot(m_world), m_bullets, m_objects);
}

void game::explode(const glm::vec3& pos, const float size) {
	auto e = std::make_unique<explosion>(m_world, pos, size * 250ms, 2 * size);
	m_objects[e->body()] = e.get();
	m_explosions.push_back(std::move(e));
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
	update_objects(delta, m_bullets);
	update_objects(delta, m_cuboids);
	update_objects(delta, m_explosions);
	// Add new cuboids
	add_objects(m_cuboidsFactory->create(m_world), m_cuboids, m_objects);
	// Remove dead entities
	remove_dead_objects(m_bullets, m_objects);
	remove_dead_objects(m_cuboids, m_objects);
	remove_dead_objects(m_explosions, m_objects);
	// Remove oldest objects, when there is too many
	remove_oldest_objects(m_bullets, m_objects, max_bullets());
	remove_oldest_objects(m_cuboids, m_objects, max_cuboids());
	remove_oldest_objects(m_explosions, m_objects, max_explosions());
}

void game::visit(ivisitor& v) const {
	for (const auto& c : m_cuboids)
		c->visit(v);
	for (const auto& b : m_bullets)
		b->visit(v);
	for (const auto& e : m_explosions)
		e->visit(v);
	m_player->visit(v);
}

void game::on_cuboid_killed() {
	m_cuboidsFactory->on_killed();
}

}
