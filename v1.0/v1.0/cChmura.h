#pragma once
#include "cObiekt.h"
#include "naglowki.h"


class cChmura :
	public cObiekt
{
private:
	int typChmury;
	sKOLOR kolor;
	float rozmiar;
	float speed;

public:
	cChmura();
	cChmura(int _typChmury, float _x, float _y, float _z, sKOLOR _kolor, float _rozmiar, float _kat, float _speed);
	~cChmura(void);
	void Rysuj();
	void Ruszaj();
	void SprawdzZasieg();
};

