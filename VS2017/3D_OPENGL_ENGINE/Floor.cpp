#include "Floor.h"
#include "Block.h"



void Floor::draw() {
	m_material->updateMaterial();

	glPushMatrix();
	glTranslatef(m_transform.Position().getX(), m_transform.Position().getY(), m_transform.Position().getZ());

	glRotatef(m_transform.Rotation().getX(), 1.0f, 0.0f, 0.0f);
	glRotatef(m_transform.Rotation().getY(), 0.0f, 1.0f, 0.0f);
	glRotatef(m_transform.Rotation().getZ(), 0.0f, 0.0f, 1.0f);

	glScalef(m_transform.Scale().getX(), m_transform.Scale().getY(), m_transform.Scale().getZ());

	glBegin(GL_QUADS); {

		//BOTTOM FACE
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f); glVertex3f(1.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.5f); glVertex3f(0.0f, 0.0f, 1.0f);

		//TOP FACE
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, BLOCK_HEIGHT, 0.0f);
		glTexCoord2f(0.0f, 0.5f); glVertex3f(1.0f, BLOCK_HEIGHT, 1.0f);
		glTexCoord2f(1.0f, 0.5f); glVertex3f(0.0f, BLOCK_HEIGHT, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, BLOCK_HEIGHT, 0.0f);

	} glEnd();

	glPopMatrix();
}