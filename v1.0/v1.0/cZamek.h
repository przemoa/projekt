#pragma once
#include "naglowki.h"
#include "cJednostka.h"


struct sWIEZA 
{
	int typWiezy;			// TEKSTURA_WIEZA1 TEKSTURA_WIEZA2 itd jak tekstury
	int pozycja;			// 100*kolumna + wiersz, liczac od lewej dolnej strony
	float obrazenia;
	float zasieg;
};


class cZamek : public cJednostka
{
public:
	cZamek(void);
	cZamek(float _x, float _y, int _wlascicel);
	~cZamek(void);

	void Rysuj();
	bool CzyKliknieto(float px, float py);
	void AktualizujRamke(sRAMKAOPISU &ramkaOpisu);
	void RysujPasekZycia();
	void Atakuj();
	float rozmiarWiezy;


	//x;	 srodek zamq
	//y;	 spod zamq

	vector < sWIEZA > tabWiez;

	void DodajWieze(int _typWiezy, int pozycja);			// pozycja = 100, 200, lub 300

};

