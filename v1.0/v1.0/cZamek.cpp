#include "cZamek.h"


cZamek::cZamek(void)
{
}


cZamek::~cZamek(void)
{
}



cZamek::cZamek(float _x, float _y)
{
	x = _x;
	y = _y;
}

void cZamek::DodajWieze(eTYPWIEZY _typWiezy, int pozycja)
{
	sWIEZA nowaWieza;
	for (int i = 0; i < tabWiez.size(); i++)
	{
		if (pozycja/100 == tabWiez[i].pozycja/100)
		{
			if (pozycja < tabWiez[i].pozycja) pozycja = tabWiez[i].pozycja;
		}
	}
	pozycja++;

	nowaWieza.pozycja = pozycja;
	nowaWieza.typWiezy = _typWiezy;

	tabWiez.push_back(nowaWieza);

}

void cZamek::Rysuj()
{

}