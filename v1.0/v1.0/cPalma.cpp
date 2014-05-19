#include "cPalma.h"


cPalma::cPalma(void)
{
}


cPalma::~cPalma(void)
{
}


cPalma::cPalma(int _typPalmy, float _rozmiar, float _kat, float _x, float _y, float _z)
{
	typPalmy = _typPalmy;
	UstawPozycje(_x, _y, _z);
	UstawKat(_kat);
	rozmiar = _rozmiar;

}


void cPalma::Rysuj()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(kat, 0, 0, 1);
		glBindTexture(GL_TEXTURE_2D, typPalmy);
		glEnable(GL_TEXTURE_2D);
		glColor4f(1, 1, 1, 0.7);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(-rozmiar, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex2f( rozmiar, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex2f( rozmiar,  4*rozmiar);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(-rozmiar,  4*rozmiar);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}