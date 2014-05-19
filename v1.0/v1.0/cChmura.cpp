#include "cChmura.h"


cChmura::cChmura(void)
{
}

cChmura::cChmura(int _typChmury, float _x, float _y, float _z, sKOLOR _kolor, float _rozmiar, float _kat, float _speed)
{
	UstawPozycje(_x, _y, _z);
	UstawKat(_kat);
	typChmury = _typChmury;
	kolor = _kolor;
	rozmiar = _rozmiar;
	speed = _speed;
}

cChmura::~cChmura(void)
{
}


void cChmura::Rysuj()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(kat, 0, 0, 1);
		glBindTexture(GL_TEXTURE_2D, typChmury);
		glEnable(GL_TEXTURE_2D);
		glColor4f(kolor.r, kolor.g, kolor.b, 1);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(-2.5*rozmiar, -rozmiar);
			glTexCoord2f(1.0f, 0.0f); glVertex2f( 2.5*rozmiar, -rozmiar);
			glTexCoord2f(1.0f, 1.0f); glVertex2f( 2.5*rozmiar,  rozmiar);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(-2.5*rozmiar,  rozmiar);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void cChmura::Ruszaj()
{
	x += speed / SZYBKOSC_CHMUR;
}

void cChmura::SprawdzZasieg()
{
	if (x > KAMERA_MAX_POLOZENIE_X) x = -KAMERA_MAX_POLOZENIE_X;
}