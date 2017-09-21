#include "CollisionHandler.h"
#include <algorithm>

CollisionHandler* CollisionHandler::instance() {
	static CollisionHandler collisionHandler_instance;
	return &collisionHandler_instance;
}

void CollisionHandler::registerCollider(BoxCollider* col) {
	for (std::vector<BoxCollider*>::iterator it = m_colliderRegistry.begin(); it != m_colliderRegistry.end(); it++) {
		if (col == (*it)) return;
	}
	m_colliderRegistry.push_back(col);
}

void CollisionHandler::removeCollider(BoxCollider* col) {
	for (std::vector<BoxCollider*>::iterator it = m_colliderRegistry.begin(); it != m_colliderRegistry.end(); it++) {
		if (col == (*it)) {
			m_colliderRegistry.erase(it);
			return;
		}
	}
}

void CollisionHandler::createWorldRegistry(int xSize, int zSize) {
	mapSizeX = xSize; mapSizeZ = zSize;

	m_worldRegistry = new byte*[zSize];

	for (int i = 0; i < zSize; i++) {
		m_worldRegistry[i] = new byte[xSize];
	}
}

byte CollisionHandler::getWorldCollision(int x, int z) {
	if (x >= 0 && x < mapSizeX && z >= 0 && z < mapSizeZ) return m_worldRegistry[z][x];
	else return COLLISION_WALL;
}

void CollisionHandler::handleCollisions() {
	if (m_colliderRegistry.size() < 2) return;

	broadPhase();
	narrowPhase();
	m_possibleCollisions.clear();
}

void CollisionHandler::broadPhase() {
	//Single AXIS SAP

	//Sort Objects by Minimum X-Axis
	std::sort(m_colliderRegistry.begin(), m_colliderRegistry.end(), xSort);

	//Perform SAP
	for (std::vector<BoxCollider*>::iterator it = m_colliderRegistry.begin(); it != m_colliderRegistry.end() - 1; it++) {
		for (std::vector<BoxCollider*>::iterator jt = m_colliderRegistry.begin() + 1; jt != m_colliderRegistry.end(); jt++) {
			if ((*it)->getMaximum().getX() > (*jt)->getMinimum().getX()) {
				ColliderPair p = { (*it), (*jt) };
				m_possibleCollisions.push_back(p);
			}
		}
	}
}

void CollisionHandler::narrowPhase() {
	for (std::vector<ColliderPair>::iterator it = m_possibleCollisions.begin(); it != m_possibleCollisions.end(); it++) {
		BoxCollider* A = it->A;
		BoxCollider* B = it->B;
		if (A->intersect(*B)) {
			A->getParent()->collision(B->getParent()->getTag());
			B->getParent()->collision(A->getParent()->getTag());
		}
	}
}

bool xSort(BoxCollider* A, BoxCollider* B) {
	return (A->getMinimum().getX()) < (B->getMinimum().getX());
}

void CollisionHandler::clean() {
	m_colliderRegistry.clear();
	if (m_worldRegistry != NULL) {
		for (int i = 0; i < mapSizeZ; i++) {
			delete[] m_worldRegistry[i];
		}
		delete[] m_worldRegistry;
	}
}