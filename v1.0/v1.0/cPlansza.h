#pragma once
#include "naglowki.h"
#include "cChmura.h"
#include "cPalma.h"
#include "cPunktStabilny.h"
#include "cBohater.h"


struct sROZMIAROKNA
{
	int x;			// szerokosc
	int y;			// wysokosc
	float proporcja;
};

struct sKAMERA
{
	float zakres;			// aktualny zakres patrzenia kamery
	float zakresCel;		// zakres ktory ma byc osiagniety

	float x;
	float xCel;

	float y;
	float yCel;

	int przesuwajx;			// czy przesuwac kamere z powodu bycia myszy na krawedzi
	int przesuwajy;
};


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
	void WczytajTeren();
	
	void UtworzListy();

	void TworzTekstury();
	cChmura* tabChmur[ILOSC_CHMUR];
	vector < cPalma* > tabPalm;
	vector < cPunktStabilny* > tabPunktStab;
	vector < cBohater* > tabBohaterow;
	int wybranyBohater;


	float tabPol[5000];

	void DodajPunktStabilny(float _x, float _y);

	void RysujPodloze();
	void RysujTlo();
	void RysujTeren();


	float testowy;
	float testowy2;
	void RysujSzescian();
	
	//int tabPunktow[200][2];
	//int licznikPunktow;

	float TabDoX(int k);
	float TabDoY(int w);
	int XDoTab(float x);
	int YDoTab(float y);
};

