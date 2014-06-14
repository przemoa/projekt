#pragma once
#include "naglowki.h"
#include "cJednostka.h"


struct sWIEZA 
{
	int typWiezy;			// TEKSTURA_WIEZA1 TEKSTURA_WIEZA2 itd jak tekstury
	int pozycja;			// 100*kolumna + wiersz, liczac od lewej dolnej strony
	float obrazenia;
	float zasieg;
	int szybkoscAtaku;

	int level;
	
};
	//	TEKSTURA_WIEZA1	: luk, srednioszybka, male obrazenia, sredni zasieg
	//	TEKSTURA_WIEZA2	: kamien, malas szybkosc, srednie obrazenia, maly zasieg
	//	TEKSTURA_WIEZA3	: pocisk, srednia szybkosc, srednie obrazenia, sredni zasieg
	//	TEKSTURA_WIEZA4	: laser, malas szybkosc, duze obrazenia, duzy zasieg
	//	TEKSTURA_WIEZA5	: ogien, mala szybkosc, duze obrazenia, maly zasieg


class cZamek : public cJednostka
{
public:
	cZamek(void);
	cZamek(float _x, float _y, int _wlascicel);
	~cZamek(void);

	void Rysuj();
	bool CzyKliknieto(float px, float py);
	void AktualizujRamke();
	void RysujPasekZycia();
	void Atakuj();
	float rozmiarWiezy;
	float wysokoscWiezy;

	float wydobycie;		// pozyskiwane zloto na sekunde
	int wybranaWiez;

	//x;	 srodek zamq
	//y;	 spod zamq

	vector < sWIEZA > tabWiez;

	void DodajWieze(int _typWiezy, int pozycja);			// pozycja = 100, 200, lub 300

};

