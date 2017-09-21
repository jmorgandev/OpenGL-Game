#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <vector>
#include "BoxCollider.h"

typedef unsigned char byte;

#define COLLISION_NONE		0
#define COLLISION_WALL		1
#define COLLISION_ELEVATOR  2

struct ColliderPair {
	BoxCollider* A;
	BoxCollider* B;
};

bool xSort(BoxCollider* A, BoxCollider* B);
class CollisionHandler {
public:
	CollisionHandler(){}
	~CollisionHandler(){}

	static CollisionHandler* instance();

	void registerCollider(BoxCollider* col);
	void removeCollider(BoxCollider* col);

	void createWorldRegistry(int xSize, int zSize);
	void setWorldCollision(int x, int z, byte collision) { m_worldRegistry[z][x] = collision; }
	byte getWorldCollision(int x, int z);

	void clean();

	void handleCollisions();

private:
	int mapSizeX, mapSizeZ;
	int gridSize, gridSubdivisions;

	std::vector<BoxCollider*> m_colliderRegistry;

	std::vector<ColliderPair> m_possibleCollisions;
	byte** m_worldRegistry;

	void broadPhase();
	void narrowPhase();

};

#endif