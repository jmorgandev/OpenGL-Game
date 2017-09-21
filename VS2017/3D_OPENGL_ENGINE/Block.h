#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject.h"

#define BLOCK_HEIGHT 2.0f
#define BLOCK_WIDTH 1.0f
#define BLOCK_HALFWIDTH 0.5f

#define LIGHT_HEIGHT BLOCK_HEIGHT - 0.25f

class Block : public GameObject {
public:
	Block(){}
	virtual ~Block(){}

	virtual void load(const LoadParameters parameters){ GameObject::load(parameters); }

	virtual void draw();
	virtual void update();
	virtual void clean(){}
};

#endif