#pragma once
#include "cIstota.h"

class cBohater : public cIstota
{
public:
	float x2;
	float y2;
	float fazaKol;

	sKOLOR kolor;
	float rozmiar;
	cBohater(void);
	cBohater(float _x, float _y);
	~cBohater(void);
	void Rysuj();
	bool CzyKliknieto(float px, float py);
	void Ruszaj(float dx);
	void Opadaj();
	void ZmienKat(float dkat);
	void UstawX2();
	void UstawY2();

	void 
};

