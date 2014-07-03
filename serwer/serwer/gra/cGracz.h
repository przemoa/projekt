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
	cGracz(float _x, float _y, int _wlascicel);
	

	int wlasciciel;		// 1 w prawo (gracz1), -1 w lewo (gracz2)

	int levelStworkow;
	float x;
	float y;

    int zloto;

    cBohater* tabBohaterow[3];
	cZamek* zamek;
	vector < cStworek* > tabStworkow;

    void Dzialaj();
    void DodajBohatera(int ktory);
	void PrzyspieszajBohatera(float dVx, float dVy);

	int wybranyBohater;
	int idWybrane;

    void DodajStworka(int _typStworka);
	bool ZaplacZlotem(int ile);
	void AwansujStworki();

};

