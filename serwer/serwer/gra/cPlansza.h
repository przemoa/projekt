#pragma once
#include "naglowki.h"
#include "cPunktStabilny.h"
#include "cGracz.h"
#include "cElement.h"
#include "cBelka.h"
#include "cTeownik.h"





class cPlansza
{
public:
	cPlansza(void);
	~cPlansza(void);

    void _Dzialaj(int value);
	void WczytajTeren();

	vector < cPunktStabilny* > tabPunktStab;
	vector < cGracz* > tabGraczy;

	float tabPol[50000];
	int tabTypowPol[50000];



	void DodajPunktStabilny(float _x, float _y);


	float TabDoX(int k);
	float TabDoY(int w);
	int XDoTab(float x);
	int YDoTab(float y);
	float Wysokosc(float x);		// wysokosc poziomu mapy
};

