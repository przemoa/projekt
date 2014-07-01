#include "cStworek.h"
#include "cPlansza.h"

cStworek::cStworek(void)
{
}

cStworek::cStworek(float _x, float _z, int _typStworka, int _wlasciciel, int levelStworkow)
{
	x = _x;
	z = _z;
	wlasciciel = _wlasciciel;
	rozmiar = 3;	
	typStworka = _typStworka;


	kat = 0;

	switch(_typStworka)
	{
	case LISTA_STWOREK_KULA:
		wysokosc = ROMIAR_STWORKA_KULA;
		predkosc = 50;
		mnoznikZycia = 0.6;
		zasieg = 35;
		obrazenia = 12;
		szybkoscAtaku = 40;
		break;
	case LISTA_STWOREK_KWADRAT:
		wysokosc = 35;
		predkosc = 30;
		mnoznikZycia = 0.4;
		zasieg = 55;
		obrazenia = 15;
		szybkoscAtaku = 15; 
		break;
	}

	predkosc += predkosc*levelStworkow/5.0;
	mnoznikZycia += mnoznikZycia*levelStworkow/5.0;
	zasieg += zasieg*levelStworkow/5.0;
	obrazenia += obrazenia*levelStworkow/5.0;
	szybkoscAtaku += szybkoscAtaku*levelStworkow/5.0;

	y = Plansza->tabPol[Plansza->XDoTab(x)] + wysokosc;
	yCel = y;

}

cStworek::~cStworek(void)
{

}

void cStworek::Ruszaj()
{
	int xTab = Plansza->XDoTab(x);
	float dx = 0;

	if (typStworka == LISTA_STWOREK_KWADRAT)
	{
		dx = wlasciciel * predkosc;
	}
	else if (typStworka == LISTA_STWOREK_KULA)
	{
		dx = Plansza->tabPol[xTab-30] - Plansza->tabPol[xTab+30];

		dx = wlasciciel*predkosc + 10*dx;				// todo

		switch (wlasciciel)
		{ 
		case 1:
			if (dx < 5) dx = 5;
			if (dx > predkosc*2) dx = predkosc*2;
			break;
		case -1:
			if (dx > -5) dx = -5;
			if (dx < -predkosc*2) dx = -predkosc*2;
			break;
		}
	}

	dx /= 100;
	x += dx;
	yCel = Plansza->tabPol[Plansza->XDoTab(x)]  + wysokosc;
	y += 0.2/wysokosc*abs(yCel-y)*(yCel-y);
	
}

void cStworek::Atakuj()
{
}
