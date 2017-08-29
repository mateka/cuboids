#include <physicslib/world.h>
#include <iostream>


namespace physicslib {

world::world(collision_callback cc)
	: m_collisionDispatcher{ &m_collisionConfiguration },
	m_worldSimulation{ &m_collisionDispatcher, &m_broadPhaseAlgorithm, &m_solver, &m_collisionConfiguration },
	m_collisionCallback{ std::move(cc) }
{}

glm::vec3 world::gravity() const {
	const auto gv = m_worldSimulation.getGravity();
	return { gv.x(), gv.y(), gv.z() };
}

void world::gravity(const glm::vec3& gv) {
	m_worldSimulation.setGravity({ gv.x, gv.y, gv.z });
}

void world::update(const utils::seconds time, const int subSteps) {
	m_worldSimulation.stepSimulation(btScalar(time.count()), subSteps);

	int numManifolds = m_worldSimulation.getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++)
	{
		btPersistentManifold* contactManifold = m_worldSimulation.getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();

		int numContacts = contactManifold->getNumContacts();
		for (int j = 0; j < numContacts; j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance() < 0.f)
			{
				const auto itA = m_bodies.find(obA);
				const auto itB = m_bodies.find(obB);
				if (itA != m_bodies.end() && itB != m_bodies.end())
					m_collisionCallback(itA->second, itB->second);
				break;
			}
		}
	}
}

void world::add_body(body& b) {
	m_worldSimulation.addRigidBody(&b.m_rigidBody);
	m_bodies[&b.m_rigidBody] = &b;
}

void world::remove_body(body& b) {
	m_worldSimulation.removeRigidBody(&b.m_rigidBody);
	m_bodies.erase(&b.m_rigidBody);
}

std::unique_ptr<box> world::create_dynamic_box(
	const float mass,
	const glm::vec3& size,
	const btTransform& startTransform
) {
	return std::make_unique<box>(*this, mass, size, startTransform);
}

std::unique_ptr<box> world::create_dynamic_box(
	const float mass,
	const glm::vec3& size,
	const glm::vec3& startPosition
) {
	return std::make_unique<box>(*this, mass, size, startPosition);
}

std::unique_ptr<box> world::create_static_box(
	const glm::vec3& size, const btTransform& startTransform
) {
	return std::make_unique<box>(*this, size, startTransform);
}

std::unique_ptr<box> world::create_static_box(
	const glm::vec3& size, const glm::vec3& startPosition
) {
	return std::make_unique<box>(*this, size, startPosition);
}

}
