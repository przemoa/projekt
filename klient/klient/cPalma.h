#pragma once
#include "cObiekt.h"
#include "naglowki.h"

class cPalma : public cObiekt
{
private:
	float rozmiar;
	int typPalmy;

public:
	cPalma(void);
	cPalma(int _typPalmy, float _rozmiar, float _kat, float _x, float _y, float _z);
	~cPalma(void);
	void Rysuj();
};

