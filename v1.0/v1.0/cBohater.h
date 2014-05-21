#pragma once
#include "cIstota.h"

class cBohater : public cIstota
{
public:
	float x2;			// wspolrzedne mniejszego kola
	float y2;			
	float fazaKol;		// kat miedzy kolami w poziomie

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
	void Przesun(float dx, float dy);
};

