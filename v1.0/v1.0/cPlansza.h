#pragma once
#include "naglowki.h"
#include "cChmura.h"
#include "cPalma.h"
#include "cPunktStabilny.h"
#include "cGracz.h"



class cPlansza
{
public:
	cPlansza(void);
	~cPlansza(void);

	sROZMIAROKNA rozmiarOkna;
	sKAMERA kamera;
	void _Przerysuj();
	void _ZmianaRozmiaruOkna(int width, int height);
	void _Dzialaj(int value);
	void _Idle();
	void _Klawiatura(unsigned char key, int x, int y);
	void _MyszKlawisz(int button, int state, int x, int y);
	void _MyszRuch(int x,int y);
	void _KlawiszeSpecjalne(int key, int x, int y);
	void OdswiezKamere();
	void PrzesunKamere(float dx, float dy);
	void AktualizujRamke();
	void FocusujKamere();
	void WczytajTeren();
	
	void UtworzListy();
	void TworzTekstury();

	cChmura* tabChmur[ILOSC_CHMUR];
	vector < cPalma* > tabPalm;
	vector < cPunktStabilny* > tabPunktStab;
	vector < cGracz* > tabGraczy;
	bool wybranyGracz;
	bool czyFocusowac;		// czy ustawiac focus na wybrana jednostke

	float tabPol[50000];
	int tabTypowPol[50000];


	void DodajPunktStabilny(float _x, float _y);

	void RysujPodloze();
	void RysujTloNiebo();
	void RysujTeren();

	sRAMKAOPISU ramkaOpisu;
	void RysujRamkeOpisu();

	void DrawString(int x, int y, const unsigned char * string, float skala);


	float testowy;
	float testowy2;
	void RysujSzescian();
	


	float TabDoX(int k);
	float TabDoY(int w);
	int XDoTab(float x);
	int YDoTab(float y);
	float Wysokosc(float x);		// wysokosc poziomu mapy
};

