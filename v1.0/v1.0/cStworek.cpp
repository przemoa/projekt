#include "cStworek.h"
#include "cPlansza.h"

cStworek::cStworek(void)
{
}

cStworek::cStworek(float _x, float _z, int _typStworka, int _wlasciciel)
{
	x = _x;
	z = _z;
	wlasciciel = _wlasciciel;
	rozmiar = 3;	
	typStworka = _typStworka;
	poziomZycia = 100;
	kolor.r = 1;
	kolor.g = 0;
	kolor.b = 0;

	kat = 0;

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

	y = Plansza->tabPol[Plansza->XDoTab(x)] + wysokosc;
	yCel = y;

}

cStworek::~cStworek(void)
{

}

void cStworek::Rysuj()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(kat, 0, 0, 1);
		glColor3f(kolor.r, kolor.g, kolor.b);  //todo
		//glCallList(typStworka);
		glCallList(LISTA_STWOREK_KULA);

		RysujPasekZycia();

	glPopMatrix();

	
}

void cStworek::Ruszaj()
{
	int xTab = Plansza->XDoTab(x);
	float dx = 0;

	if (typStworka == LISTA_STWOREK_KWADRAT)
	{
		dx = wlasciciel * predkosc;
	}
	else
	{
		dx = Plansza->tabPol[xTab-30] - Plansza->tabPol[xTab+30];

		dx = predkosc + 10*dx;				// todo
		dx *= wlasciciel;

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

void cStworek::RysujPasekZycia()
{

	glPushMatrix();

		glTranslatef(-rozmiar, rozmiar*1.7, 0);
		glColor3f(0.1,0.1,0.1);
		glBegin(GL_POLYGON);
			glVertex2f(0, -0.1*rozmiar);
			glVertex2f( rozmiar*2, -0.1*rozmiar);
			glVertex2f( rozmiar*2,  0.1*rozmiar);
			glVertex2f(0,  0.1*rozmiar);
		glEnd();
		
		glColor3f(1-poziomZycia/100, poziomZycia/100, 0.0);
		glBegin(GL_POLYGON);
			glVertex2f(0.05*rozmiar, -0.08*rozmiar);
			glVertex2f( rozmiar*1.95*poziomZycia/100, -0.08*rozmiar);
			glVertex2f( rozmiar*1.95*poziomZycia/100,  0.08*rozmiar);
			glVertex2f(0.05*rozmiar,  0.08*rozmiar);
		glEnd();


	glPopMatrix();
}

bool cStworek::CzyKliknieto(float px, float py)
{
	if ((px-x)*(px-x)+(py-y)*(py-y) < ZAKRES_KLIKNIECIE*rozmiar*rozmiar) return true;

	return false;
}
void cStworek::AktualizujRamke()
{
}
void cStworek::Atakuj()
{
}
