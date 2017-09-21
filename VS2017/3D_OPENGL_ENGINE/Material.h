#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color3.h"
#include <glut.h>
#include <string>

typedef unsigned int Texture;

class Material {
public:
	Material();
	Material(Color3f diffuse, Color3f ambient, Color3f specular, Color3f emission, float shininess, Texture texture = 0);
	Material(float dR, float dG, float dB, float dA, float aR, float aG, float aB, float aA, float sR, float sG, float sB, float sA, float eR, float eG, float eB, float eA, Texture texture = 0);
	Material(Texture texture);
	~Material();
	
	void setDiffuse(float r, float g, float b, float a);
	void setDiffuse(Color3f diffuse);

	void setAmbient(float r, float g, float b, float a);
	void setAmbient(Color3f ambient);

	void setSpecular(float r, float g, float b, float a);
	void setSpecular(Color3f specular);

	void setEmission(float r, float g, float b, float a);
	void setEmission(Color3f emission);

	void setShininess(float shine);

	void setTexture(std::string textureName);

	bool unlit() { return m_unlit; }

	Color3f getDiffuse();
	Color3f getAmbient();
	Color3f getSpecular();
	Color3f getEmission();
	float getShininess();

	Texture getTexture() { return m_texture; }

	void resetColor();

	void updateMaterial();
	
private:
	bool m_unlit;

	Texture m_texture;
	
	float m_diffuse[4];
	float m_ambient[4];
	float m_specular[4];
	float m_emission[4];
	float m_shininess;
};

#endif