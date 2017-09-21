#include "Material.h"
#include "TextureManager.h"

Material::Material() {
	m_texture = 0;
	resetColor();
}

Material::Material(Color3f diffuse, Color3f ambient, Color3f specular, Color3f emission, float shininess, Texture texture) {
	diffuse.toMatrix(m_diffuse);
	ambient.toMatrix(m_ambient);
	specular.toMatrix(m_specular);
	m_shininess = shininess;
	m_texture = texture;
}

Material::Material(float dR, float dG, float dB, float dA, float aR, float aG, float aB, float aA, float sR, float sG, float sB, float sA, float eR, float eG, float eB, float eA, Texture texture) {
	m_diffuse[0] = dR; m_diffuse[1] = dG; m_diffuse[2] = dB; m_diffuse[3] = dA;
	m_ambient[0] = aR; m_ambient[1] = aG; m_ambient[2] = aB; m_ambient[3] = aA;
	m_specular[0] = sR; m_specular[1] = sG; m_specular[2] = sB; m_specular[3] = sA;
	m_emission[0] = eR; m_emission[1] = eG; m_emission[2] = eB; m_emission[3] = sA;
	m_texture = texture;
}

Material::Material(Texture texture) {
	m_texture = texture;
	resetColor();
}

void Material::updateMaterial() {

	if (m_texture > 0) {
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}
	else glBindTexture(GL_TEXTURE_2D, 0);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, m_shininess * 128.0f);
	glMaterialfv(GL_FRONT, GL_EMISSION, m_emission);
	
}

void Material::setTexture(std::string textureName) {
	m_texture = TextureManager::instance()->getTexture(textureName);
}


//SET MATERIAL BY TYPE//
void Material::setDiffuse(float r, float g, float b, float a) {
	m_diffuse[0] = r;
	m_diffuse[1] = g;
	m_diffuse[2] = b;
	m_diffuse[3] = a;
}
void Material::setDiffuse(Color3f diffuse) { setDiffuse(diffuse.getR(), diffuse.getG(), diffuse.getB(), diffuse.getA()); }

void Material::setAmbient(float r, float g, float b, float a) {
	m_ambient[0] = r;
	m_ambient[1] = g;
	m_ambient[2] = b;
	m_ambient[3] = a;
}
void Material::setAmbient(Color3f ambient) { setAmbient(ambient.getR(), ambient.getG(), ambient.getB(), ambient.getA()); }

void Material::setSpecular(float r, float g, float b, float a) {
	m_specular[0] = r;
	m_specular[1] = g;
	m_specular[2] = b;
	m_specular[3] = a;
}
void Material::setSpecular(Color3f specular) { setSpecular(specular.getR(), specular.getG(), specular.getB(), specular.getA()); }

void Material::setEmission(float r, float g, float b, float a) {
	m_emission[0] = r;
	m_emission[1] = g;
	m_emission[2] = b;
	m_emission[3] = a;
}
void Material::setEmission(Color3f emission) { setEmission(emission.getR(), emission.getG(), emission.getB(), emission.getA()); }

void Material::setShininess(float shine) {
	m_shininess = shine;
}



//GET MATERIAL BY TYPE//
Color3f Material::getDiffuse() { return Color3f(m_diffuse[0], m_diffuse[1], m_diffuse[2], m_diffuse[3]); }
Color3f Material::getAmbient() { return Color3f(m_ambient[0], m_ambient[1], m_ambient[2], m_ambient[3]); }
Color3f Material::getSpecular() { return Color3f(m_specular[0], m_specular[1], m_specular[2], m_specular[3]); }
Color3f Material::getEmission() { return Color3f(m_emission[0], m_emission[1], m_emission[2], m_emission[3]); }
float Material::getShininess() { return m_shininess; }



Material::~Material() {
}

void Material::resetColor() {
	Color3f(1.0f, 1.0f, 1.0f, 1.0f).toMatrix(m_diffuse);
	Color3f(0.5f, 0.5f, 0.5f, 1.0f).toMatrix(m_ambient);
	Color3f(1.0f, 1.0f, 1.0f, 1.0f).toMatrix(m_specular);
	Color3f(0.0f, 0.0f, 0.0f, 1.0f).toMatrix(m_emission);
	m_shininess = 0.0f;
}