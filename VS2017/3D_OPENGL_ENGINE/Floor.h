#ifndef FLOOR_H
#define FLOOR_H

#include "GameObject.h"

class Floor : public GameObject {
public:
	Floor(){}
	~Floor(){}

	virtual void load(const LoadParameters parameters){ GameObject::load(parameters); }

	virtual void draw();
	virtual void update(){}
	virtual void clean(){}
};

#endif