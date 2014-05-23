#pragma once
#include "cBohater.h"
#include "naglowki.h"
#include "cZamek.h"
#include "cStworek.h"

class cGracz
{
public:
	cGracz(void);
	~cGracz(void);
	cGracz(float _x, float _y, int _kierunek);
	
	sKOLOR kolor;
	int kierunek;		// 1 w prawo, -1 w lewo

	float x;
	float y;

	vector < cBohater* > tabBohaterow;
	vector < cZamek* > tabZamkow;
	vector < cStworek* > tabStworkow;

	void Dzialaj();			// wywolywana timerem co 20ms
	void DodajBohatera(float _x, float _y);
	void RuszajBohatera(float dVx, float dVy);
	void Rysuj();

	int wybranyBohater;

	void DodajZamek(float _x, float _y);
	void DodajStworka(float _x, int _typStworka);




};

