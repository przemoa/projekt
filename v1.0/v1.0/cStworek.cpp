#include "cStworek.h"
#include "cPlansza.h"

cStworek::cStworek(void)
{
}

cStworek::cStworek(float _x, float _z, int _typStworka, int _kierunek)
{
	x = _x;
	z = _z;
	kierunek = _kierunek;
	romiar = 3;	
	typStworka = _typStworka;
	poziomZycia = 100;
	kolor.r = 1;
	kolor.g = 0;
	kolor.b = 0;
	y = Plansza->tabPol[Plansza->XDoTab(x)];

	switch(_typStworka)
	{
	case LISTA_STWOREK_KULA:
		wysokosc = ROMIAR_STWORKA_KULA;
		predkosc = 50;
		break;
	case LISTA_STWOREK_KWADRAT:
		wysokosc = 35;
		predkosc = 30;
		break;
	}

}


cStworek::~cStworek(void)
{

}


void cStworek::Rysuj()
{
	glPushMatrix();
		glTranslatef(x, y + wysokosc, z);
		glRotatef(kat, 0, 0, 1);
		glColor3f(kolor.r, kolor.g, kolor.b);  //todo
		//glCallList(typStworka);
		glCallList(LISTA_STWOREK_KULA);
	glPopMatrix();
}

bool cStworek::CzyKliknieto(float px, float py)
{
	return false;
}

void cStworek::Ruszaj()
{
	int xTab = Plansza->XDoTab(x);
	if (typStworka == LISTA_STWOREK_KWADRAT)
	{
		x += kierunek * predkosc / 100;
		y = Plansza->tabPol[Plansza->XDoTab(x)];
	}
	else
	{
		float dx = Plansza->tabPol[xTab-30] - Plansza->tabPol[xTab+30];
		dx = predkosc + 10*dx;				// todo
		dx *= kierunek;

		switch (kierunek)
		{ 
		case 1:
			if (dx < 0) dx = 5;
			break;
		case -1:
			if (dx > 0) dx = -5;
			break;
		}
		dx /= 100;
		x += dx;
		y = Plansza->tabPol[Plansza->XDoTab(x)];
	}

	
}
