#pragma once
#include "cIstota.h"

class cBohater : public cIstota
{
public:
	sKOLOR kolor;
	float rozmiar;
	cBohater(void);
	cBohater(float _x, float _y);
	~cBohater(void);
	void Rysuj();
	bool CzyKliknieto(float px, float py);
	void Ruszaj(float dx);
	void Opadaj();
};

