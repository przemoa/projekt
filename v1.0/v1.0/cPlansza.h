#pragma once
#include "naglowki.h"
#include "cChmura.h"
#include "cPalma.h"


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
	void OdswiezKamere();
	void PrzesunKamere(float dx, float dy);
	void WczytajTeren();

	void TworzTekstury();
	cChmura* tabChmur[ILOSC_CHMUR];
	cPalma* tabPalm[ILOSC_PALM];


	unsigned char tabPol[400][1500]; // PUSTE = 1, TRAWA = 2, ZIEMIA = 3, TWARDAZIEMIA = 4};


	void RysujPodloze();
	void RysujTlo();
	


	float testowy;
	float testowy2;
	void RysujSzescian();
	
	//int tabPunktow[200][2];
	//int licznikPunktow;

};

