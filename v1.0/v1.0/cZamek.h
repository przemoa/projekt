#pragma once
#include "naglowki.h"

enum eTYPWIEZY {KAMIEN = 1, LUK = 2, OGIEN = 3, POCISK = 4, LASER = 5};

struct sWIEZA
{
	eTYPWIEZY typWiezy;
	int pozycja;			// 100*kolumna + wiersz, liczac od lewej dolnej strony
};


class cZamek
{
public:
	cZamek(void);
	cZamek(float _x, float _y);
	~cZamek(void);
	void Rysuj();

	float x;	// srodek zamq
	float y;	// spod zamq

	vector < sWIEZA > tabWiez;

	void DodajWieze(eTYPWIEZY _typWiezy, int pozycja);			// pozycja = 100, 200, lub 300

};

