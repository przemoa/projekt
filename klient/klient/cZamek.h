#pragma once
#include "naglowki.h"
#include "cJednostka.h"


struct sWIEZA 
{
	bool czyAtakuje;		// czy wieza walczaca (1-5) czy nie (6-7)
	int typWiezy;			// TEKSTURA_WIEZA1 TEKSTURA_WIEZA2 itd jak tekstury
	int pozycja;			// 100*kolumna + wiersz, liczac od lewej dolnej strony
	float obrazenia;		// obrazenia wiezy lub parametr dla wiezy 6 i 7
	float zasieg;
	int szybkoscAtaku;
	int level;

	float x;
	float y;
	
};
	//	TEKSTURA_WIEZA1	: luk, srednioszybka, male obrazenia, sredni zasieg
	//	TEKSTURA_WIEZA2	: kamien, malas szybkosc, srednie obrazenia, maly zasieg
	//	TEKSTURA_WIEZA3	: pocisk, srednia szybkosc, srednie obrazenia, sredni zasieg
	//	TEKSTURA_WIEZA4	: laser, malas szybkosc, duze obrazenia, duzy zasieg
	//	TEKSTURA_WIEZA5	: ogien, mala szybkosc, duze obrazenia, maly zasieg
	// TEKSTURA_WIEZA6 : wydobywajaca zloto
	// TEKSTURA_WIEZA7 : lecznicza

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

	int wydobycie;		// pozyskiwane zloto na sekunde
	int wybranaWiez;
	int typWybranejWiezy;

	void Awansuj();

	int dodawanaWieza;

	void AwansujWieze();
	int SprzedajWieze();
	//x;	 srodek zamq
	//y;	 spod zamq

	vector < sWIEZA > tabWiez;

	void DodajWieze(int _typWiezy, int pozycja);			// pozycja = 100, 200, lub 300

};

