#pragma once
#include "cObiekt.h"
#include "naglowki.h"

class cPunktStabilny :
	public cObiekt
{
public:
	cPunktStabilny(void);
	cPunktStabilny(float _x, float _y, float _z);
	~cPunktStabilny(void);
	void Rysuj();
	bool CzyKliknieto(float px, float py);
	void ObracajSie();
};

