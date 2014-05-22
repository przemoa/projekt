#include "cGracz.h"


cGracz::cGracz(void)
{
}


cGracz::~cGracz(void)
{
}

cGracz::cGracz(float _x, float _y)
{
	wybranyBohater = -1;
	DodajBohatera(_x, _y);

	x = _x;
	y = _y;
}


void cGracz::Dzialaj()
{
	tabBohaterow[wybranyBohater]->Opadaj();
}

void cGracz::DodajBohatera(float _x, float _y)
{
	if (wybranyBohater == -1) wybranyBohater = 0;
	cBohater * nowyBohater = new cBohater(_x, _y);
	tabBohaterow.push_back(nowyBohater);
}

void cGracz::RuszajBohatera(float dVx, float dVy)
{
	tabBohaterow[wybranyBohater]->Przyspieszaj(dVx, dVy);
}

void cGracz::Rysuj()
{
	for (int i = 0; i < tabBohaterow.size(); i++)
	{
		tabBohaterow[i]->Rysuj();
	}
}