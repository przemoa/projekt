#pragma once
#include "naglowki.h"
#include "cChmura.h"

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

	int przesuwaj;			// czy przesuwac kamere z powodu bycia myszy na krawedzi
};


class cPlansza
{
public:
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
	void TworzTekstury();
	cChmura* tabChmur[ILOSC_CHMUR];

	cPlansza(void);
	~cPlansza(void);

	void RysujPodloze();
	void RysujTlo();
	


	float testowy;
	float testowy2;
	void RysujSzescian();
	GLuint tekstury[32];

};

