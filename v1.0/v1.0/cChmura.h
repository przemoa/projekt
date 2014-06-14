#pragma once
#include "cObiekt.h"
#include "naglowki.h"


class cChmura :
	public cObiekt
{
private:
	int typChmury;
	float rozmiar;
	float speed;

public:
	cChmura();
	cChmura(int _typChmury, float _x, float _y, float _rozmiar, float _kat, float _speed);
	~cChmura(void);
	void Rysuj();
	void Ruszaj();
	void SprawdzZasieg();
};

