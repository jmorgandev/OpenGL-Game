#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "LoadParameters.h"
#include "Transform3D.h"
#include "Material.h"

class GameObject {
public:
	GameObject(){ m_bRender = true; }
	virtual ~GameObject(){}

	virtual void load(const LoadParameters parameters);

	virtual void draw(){}
	virtual void update(){}
	virtual void clean(){}

	virtual std::string getName(){ return m_objectName; }

	virtual std::string getTag(){ return m_objectTag; }

	virtual void collision(std::string object) {}

	virtual bool toRemove(){ return false; }

	Transform3D& Transform() { return m_transform; }

	void setMaterial(Material* material) { m_material = material; }

	void setDrawable(bool r) { m_bRender = r; }

protected:

	std::string m_objectName;
	std::string m_objectTag;

	Transform3D m_transform;

	Material* m_material;

	bool m_bRender;
};

#endif