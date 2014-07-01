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
	
	sKOLOR kolor;
	int wlasciciel;		// 1 w prawo (gracz1), -1 w lewo (gracz2)

	int levelStworkow;
	float x;
	float y;

	float zloto;
	char napisZloto[8];

	vector < cBohater* > tabBohaterow;
	cZamek* zamek;
	vector < cStworek* > tabStworkow;

	void DodajBohatera(float _x, float _y, int ktory);
	void PrzyspieszajBohatera(float dVx, float dVy);
	void Rysuj();
	void AktualizujRamke();
	void FocusujKamere();

	int wybranyBohater;
	int idWybrane;

	void DodajStworka(float _x, int _typStworka);
	bool WybierzJednostke(float px, float py);
	bool ZaplacZlotem(int ile);
	void AwansujStworki();

};

