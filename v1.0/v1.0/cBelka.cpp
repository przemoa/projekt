#include "cBelka.h"


cBelka::cBelka(void)
{
}

cBelka::cBelka(float xp, float yp, float xk, float yk, float wytrzymalosc)
{
	x_poczatku = xp;
	x_konca = xk;
	y_poczatku = yp;
	y_konca = yk;
	this->wytrzymalosc = wytrzymalosc;
	kolor_r = 0.6;
	kolor_g = 0.3;
	kolor_b = 0;
	z = 0;
}

cBelka::~cBelka(void)
{
}

void cBelka::Rysuj()
{
	glPushMatrix();
	glTranslatef(0.5 * (x_poczatku + x_konca), 0.5 * (y_poczatku + y_konca), z);
	glRotatef(atan2((y_konca - y_poczatku),(x_konca - x_poczatku)), 0, 0, 1);
	glColor3f(kolor_r, kolor_g, kolor_b);
	//glBegin(GL_QUADS);
			//glTexCoord2f(0.0f, 0.0f); glVertex2f(-2.5*rozmiar, -rozmiar);
			//glTexCoord2f(1.0f, 0.0f); glVertex2f( 2.5*rozmiar, -rozmiar);
			//glTexCoord2f(1.0f, 1.0f); glVertex2f( 2.5*rozmiar,  rozmiar);
			//glTexCoord2f(0.0f, 1.0f); glVertex2f(-2.5*rozmiar,  rozmiar);
	//glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


