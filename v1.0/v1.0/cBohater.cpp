#include "cBohater.h"


cBohater::cBohater(void)
{
}


cBohater::~cBohater(void)
{
}

cBohater::cBohater(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
	kat = 0;
	rozmiar = 2;
}

void cBohater::Rysuj()
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(kat, 0, 0, 1);
	glColor3f(1,0,0);
	glCallList(LISTA_BOHATER);
	glPopMatrix();

}

bool cBohater::CzyKliknieto(float px, float py)
{
	return false;
}


void cBohater::Ruszaj(float dx)
{


}