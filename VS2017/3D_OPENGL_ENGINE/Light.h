#ifndef LIGHT_H
#define LIGHT_H

#include "GameObject.h"
#include "Color3.h"

class Light : public GameObject {
public:
	Light(Vector3f& position, int ID);
	Light(Vector3f& position, bool directional, int ID);
	Light(Vector3f& position, bool directional, int ID, Color3f diffuse, Color3f ambient = Color3f().Black(), Color3f specular = Color3f().Black());
	~Light(){}

	void draw();
	void update();
	void clean();

	void setDirectional(bool d) { m_bDirectional = d; }
	void setDiffuse(Color3f diffuse) { diffuse.toMatrix(m_diffuse); }
	void setAmbient(Color3f ambient) { ambient.toMatrix(m_ambient); }
	void setSpecular(Color3f specular) { specular.toMatrix(m_specular); }
	
	void setLightID(int id) { 
		glDisable(m_lightID);
		m_lightID = id + GL_LIGHT0;
		glEnable(m_lightID);
	}

private:
	GLfloat m_positionMatrix[4];
	
	GLfloat m_diffuse[4];
	GLfloat m_ambient[4];
	GLfloat m_specular[4];

	bool m_bDirectional;
	int m_lightID;

	void updateLight();
};

#endif