#include "cBohater.h"
#include "naglowki.h"
#include "cPlansza.h"			// co z tym?


cBohater::cBohater(void)
{
}


cBohater::~cBohater(void)
{
}

cBohater::cBohater(float _x, float _y)
{
	x = _x;
	y = _y;
	z = 0;
	kat = 0;
	rozmiar = 2;
	kat = 30;
	fazaKol = atan2(BOHATER_PROMIEN1-BOHATER_PROMIEN2, BOHATER_POZYCJA_KOLA);

	cBohater::UstawX2(); 
	cBohater::UstawY2();

}

void cBohater::Rysuj()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(kat, 0, 0, 1);
		glColor3f(1,0,0);  //todo
		glCallList(LISTA_BOHATER);
	glPopMatrix();

}

bool cBohater::CzyKliknieto(float px, float py)
{
	return false;
}


void cBohater::Ruszaj(float dx)
{
	x += dx;
}

void cBohater::Opadaj()
{
	int w1 = Plansza->YDoTab(y-1*KROK_BOHATERA - BOHATER_PROMIEN1);
	int k1 = Plansza->XDoTab(x);
	bool b1 = (Plansza->tabPol[w1][k1] == POLE_TLO);		// czy wolno spadac kolu 1
	


	int w2 = Plansza->YDoTab()   -1*KROK_BOHATERA - BOHATER_PROMIEN2);
	int k2 = Plansza->XDoTab(x + BOHATER_POZYCJA_KOLA * cos((+kat)*3.1415/180) - fazaKol);
	bool b2 = (Plansza->tabPol[w2][k2] == POLE_TLO);

	if (!b1 && !b2) return;
	if (b1 && b2) y -= 1*KROK_BOHATERA;
	else if (b1) ZmienKat(20*KROK_OBROTU_BOHATERA);
	else if (b2) ZmienKat(-20*KROK_OBROTU_BOHATERA);

	
}

void cBohater::ZmienKat(float dkat)
{
	kat += dkat;
	if (kat < -90) kat = 360 - kat;
	if (kat > 270) kat = 360 - kat;
	cBohater::UstawX2();
	cBohater::UstawY2();
}

void cBohater::UstawX2()
{
	x2 = x + BOHATER_POZYCJA_KOLA * cos((+kat)*3.1415/180 - fazaKol);
}

void cBohater::UstawY2()
{
	y2 = y + BOHATER_POZYCJA_KOLA * sin((+kat)*3.1415/180 - fazaKol);
}
