#include "cPunktStabilny.h"


cPunktStabilny::cPunktStabilny(void)
{
}

cPunktStabilny::cPunktStabilny(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

cPunktStabilny::~cPunktStabilny(void)
{
}


void cPunktStabilny::Rysuj()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(kat, 0, 0, 1);
		glColor4f(1,0,1,1);
		glCallList(LISTA_PUNKT_STABILNY);
	glPopMatrix();
}

bool cPunktStabilny::CzyKliknieto(float px, float py)
{
	if(abs(px-x) < ROZMIAR_PUNKTUSTABILNEGO && abs(py-y) < ROZMIAR_PUNKTUSTABILNEGO) return true;
	else return false;
}