#pragma once
#include "cIstota.h"
class cBohater : public cIstota
{
public:
	float rozmiar;
	cBohater(void);
	cBohater(float _x, float _y, float _z);
	~cBohater(void);
	void Rysuj();
	bool CzyKliknieto(float px, float py);
	void Ruszaj(float dx, float dy);
};

