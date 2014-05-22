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
	Vx = 0;
	Vy = 0;
	Vkatowa = 0;

	kat = 0;
	rozmiar = 2;
	kat = 30;
	fazaKol = atan2(BOHATER_PROMIEN1 - BOHATER_PROMIEN2, BOHATER_POZYCJA_KOLA);
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


void cBohater::Ruszaj(float dx)			// realizacja prêdkoœci
{
	int k = Plansza->XDoTab(x);
	bool b1;
	if (y - BOHATER_PROMIEN1 - KROK_BOHATERA > Plansza->tabPol[k]) 
		b1 = true;	// czy wolno spadac kolu 1
	else 
		b1 = false;

	k = Plansza->XDoTab(x2);
	bool b2;
	if (y2 - BOHATER_PROMIEN2 - KROK_BOHATERA > Plansza->tabPol[k]) 
		b2 = true;// czy wolno spadac kolu 2
	else 
		b2 = false;


	if (!b1 && !b2) 
		return;
	if (b1 && b2) 
	{
		Przesun(0, -KROK_BOHATERA);
		UstawX2();
		UstawY2();
		return;
	}
	else if (b1 && (!(b2))) 
		{
			Przesun(0, -KROK_BOHATERA);
			float nowyKat = asin(cos(fazaKol) * (y2 - y) / BOHATER_POZYCJA_KOLA) + fazaKol;
			x = x2 - BOHATER_POZYCJA_KOLA / cos(fazaKol) * cos(nowyKat - fazaKol);
			ZmienKat(nowyKat * 180 / 3.1416 - kat);
		}
	else if (b2 && (!(b1))) 
		{
			y2 -= KROK_BOHATERA;
			float nowyKat = asin(cos(fazaKol) * (y2 - y) / BOHATER_POZYCJA_KOLA) - fazaKol;
			ZmienKat(nowyKat * 180 / 3.1416 - kat);
		}
}


void cBohater::Opadaj()
{
	Vy += KROK_PRZYSPIESZANIA_BOHATERA;
}

void cBohater::Przyspieszaj(float dVx, float dVy)
{
	Vx += dVx;
	Vy += dVy;
}

void cBohater::ZmienKat(float dkat)
{
	kat += dkat;
	if (kat < -90) kat = 360 - kat;
	if (kat > 270) kat = 360 - kat;
	UstawX2();
	UstawY2();
}

void cBohater::UstawX2()
{
	x2 = x + BOHATER_POZYCJA_KOLA * cos((+kat)*3.1415/180 - fazaKol);
}

void cBohater::UstawY2()
{
	y2 = y + BOHATER_POZYCJA_KOLA * sin((+kat)*3.1415/180 - fazaKol);
}

void cBohater::Przesun(float dx, float dy)
{
	x += dx;
	y += dy;
}
