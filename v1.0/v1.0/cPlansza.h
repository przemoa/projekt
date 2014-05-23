#pragma once
#include "naglowki.h"
#include "cChmura.h"
#include "cPalma.h"
#include "cPunktStabilny.h"
#include "cGracz.h"


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

struct sRAMKA
{
	char nazwa[64];
	float zycie;
	char opis[256];
	bool czyWidoczna;
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

	vector < cGracz* > tabGraczy;


	float tabPol[50000];
	int tabTypowPol[50000];


	void DodajPunktStabilny(float _x, float _y);

	void RysujPodloze();
	void RysujTlo();
	void RysujTeren();

	sRAMKA ramkaOpisu;
	void RysujRamkeOpisu();
	void RysujPasekZycia(float _x, float _y, float _rozmiar, float poziomZycia);



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

