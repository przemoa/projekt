#include "cObiekt.h"



cObiekt::cObiekt()
{
	x = 0;
	y = 0;
	z = 0;

	kat = 0;
}

void cObiekt::Przesun(float dx, float dy, float dz)
{
	x += dx;
	y += dy;
	z += dz;
}

void cObiekt::UstawPozycje(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}


void cObiekt::Obroc(float dkat)
{
	kat += dkat;
}

void cObiekt::UstawKat(float _kat)
{
	kat = _kat;
}


float cObiekt::GetX()
{
	return x;
}

float cObiekt::GetY()
{
	return y;
}

float cObiekt::GetZ()
{
	return z;
}

float cObiekt::GetKat()
{
	return kat;
}