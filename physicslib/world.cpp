#include <physicslib/world.h>
#include <iostream>


namespace physicslib {

world::world()
	: m_collisionDispatcher{ &m_collisionConfiguration },
	m_worldSimulation{ &m_collisionDispatcher, &m_broadPhaseAlgorithm, &m_solver, &m_collisionConfiguration }
{}

btVector3 world::gravity() const {
	return m_worldSimulation.getGravity();
}

void world::gravity(const btVector3& gv) {
	m_worldSimulation.setGravity(gv);
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
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				//std::cout << "Collision: " << ptA.x() << "," << ptA.y() << "," << ptA.z() << std::endl;
			}
		}
	}
}

std::unique_ptr<box> world::create_dynamic_box(
	const float mass,
	const btVector3& size,
	const btTransform& startTransform
) {
	return std::make_unique<box>(m_worldSimulation, mass, size, startTransform);
}

std::unique_ptr<box> world::create_dynamic_box(
	const float mass,
	const btVector3& size,
	const btVector3& startPosition
) {
	return std::make_unique<box>(m_worldSimulation, mass, size, startPosition);
}

std::unique_ptr<box> world::create_static_box(
	const btVector3& size, const btTransform& startTransform
) {
	return std::make_unique<box>(m_worldSimulation, size, startTransform);
}

std::unique_ptr<box> world::create_static_box(
	const btVector3& size, const btVector3& startPosition
) {
	return std::make_unique<box>(m_worldSimulation, size, startPosition);
}

}
