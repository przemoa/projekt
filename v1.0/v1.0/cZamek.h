#pragma once
#include "naglowki.h"



struct sWIEZA
{
	int typWiezy;			// TEKSTURA_WIEZA1 TEKSTURA_WIEZA2 itd jak tekstury
	int pozycja;			// 100*kolumna + wiersz, liczac od lewej dolnej strony
	float obrazenia;
	float zasieg;
};


class cZamek
{
public:
	float zycie;

	cZamek(void);
	cZamek(float _x, float _y);
	~cZamek(void);
	void Rysuj();

	float rozmiar;
	float rozmiarWiezy;

	float x;	// srodek zamq
	float y;	// spod zamq

	vector < sWIEZA > tabWiez;

	void DodajWieze(int _typWiezy, int pozycja);			// pozycja = 100, 200, lub 300

};

