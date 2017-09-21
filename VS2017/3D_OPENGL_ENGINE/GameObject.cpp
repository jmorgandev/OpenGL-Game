#include "GameObject.h"
#include "Game.h"

//Load gameobject
void GameObject::load(const LoadParameters parameters) {
	m_transform.Position().set(parameters.getPosition());
	m_transform.Rotation().set(parameters.getRotation());
	m_transform.Scale().set(parameters.getScale());
	
	m_objectName = parameters.getName();

	m_objectTag = parameters.getTag();
}