#pragma once
#include "cIstota.h"
#include "naglowki.h"

class cStworek : public cIstota
{
public:
	int kierunek;		// 1 w prawo, -1 w lewo
	cStworek(void);
	cStworek(float _x, float _z, int _typStworka, int _kierunek);
	~cStworek(void);
	void Rysuj();
	bool CzyKliknieto(float px, float py);
	void Ruszaj();

	float romiar;
	float wysokosc;			// wysokosc nad poziomem powierzchni
	int typStworka;
	sKOLOR kolor;

	float poziomZycia;
	float obrazenia;
	float zasieg;
	float predkosc;
	

};

