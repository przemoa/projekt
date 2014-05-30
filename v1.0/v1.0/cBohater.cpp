#include "cBohater.h"
#include "naglowki.h"
#include "cPlansza.h"			// co z tym?


cBohater::cBohater(void)
{
}


cBohater::~cBohater(void)
{
}

cBohater::cBohater(float _x, float _y, int _wlascicel)
{
	wlasciciel = _wlascicel;
	x = _x;
	y = _y;
	y = BOHATER_PROMIEN1 + 60;
	z = 0;
	Vx = 0;
	Vy = 0;
	Vx2 = 0;
	Vy2 = 0;
	Vg = 0;
	Vg2 = 0;
	Vkatowa = 0;
	rozmiar = 2;
	kat = 0;
	mocSilnika = 6;
	fazaKol = atan2(BOHATER_PROMIEN1 - BOHATER_PROMIEN2, BOHATER_POZYCJA_KOLA);
	x2 = x + BOHATER_POZYCJA_KOLA / cos(fazaKol) * cos((kat)*3.1415/180 - fazaKol);
	y2 = y + BOHATER_POZYCJA_KOLA / cos(fazaKol) * sin((kat)*3.1415/180 - fazaKol);
	UstawXs();
	UstawYs();
	katPoprzedni = 0;


}

void cBohater::Rysuj()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		RysujPasekZycia();
		glRotatef(kat, 0, 0, 1);
		glColor3f(1,0,0);  //todo
		glCallList(LISTA_BOHATER);
	glPopMatrix();

}

void cBohater::Ruszaj()
{

	cout << "Vx = " << Vx << endl;
	cout << "Vy = " << Vy << endl;
	cout << "Vg = " << Vg << endl;
	cout << "kat terenu= " << katTerenu << endl;
				cout << sin(kat * 3.1416 / 180 - fazaKol) << endl;
			cout << sin(katTerenu * 3.1416 / 180) << endl;
	int b1, b2;			// 0 - bez zmian, 1 - podnosi siê do góry, -1 - opada w dó³

	Przesun(Vx * KROK_CZASOWY, 0);

	//wyznacznie ktore kolo moze opadac
	int k = Plansza->XDoTab(x);
	if (k < 0)
		k = 0;
	if (y - BOHATER_PROMIEN1 - KROK_BOHATERA > Plansza->tabPol[k])
	{
		b1 = -1;
	}
	else 
	{
		if(y - BOHATER_PROMIEN1 - KROK_BOHATERA == Plansza->tabPol[k])
		{
			b1 = 0;
		}
		else
		{
			b1 = 1;
		}
	}

	int k2 = Plansza->XDoTab(x2);
	if (k2 < 0)
		k2 = 0;
	if (y2 - BOHATER_PROMIEN2 - KROK_BOHATERA > Plansza->tabPol[k2])
	{
		b2 = -1;
	}
	else 
	{
		if(y2 - BOHATER_PROMIEN2 - KROK_BOHATERA == Plansza->tabPol[k2])
		{
			b2 = 0;
		}
		else
		{
			b2 = 1;
		}
	}



	katTerenu = atan((Plansza->tabPol[k2] - Plansza->tabPol[k])/(x2 - x)) * 180 / 3.1416;

	float nVx = Vx;
	float nVx2 = Vx2;

	//jesli tylne kolo jest na ziemi
	if ((b1 == 1) || (b1 == 0))
	{
		y = BOHATER_PROMIEN1 + KROK_BOHATERA + Plansza->tabPol[k];

		if ((nVx > 0) && (katTerenu <= katPoprzedni))
		{
		}

		if ((nVx > 0) && (katTerenu > katPoprzedni))
		{
			Vg = sqrt(Vx * Vx + Vy * Vy);
			Vx = Vg * cos(kat * 3.1416 / 180 - fazaKol);
			Vy = -Vg * sin(kat * 3.1416 / 180 - fazaKol);
			cout << "przeliczono 1.1" << endl;
		}

		if ((nVx < 0) && (katTerenu < katPoprzedni))
		{
			Vg = sqrt(Vx * Vx + Vy * Vy);
			Vx = -Vg * cos(kat * 3.1416 / 180 - fazaKol);
			Vy = Vg * sin(kat * 3.1416 / 180 - fazaKol);
			cout << "przeliczono 1.2" << endl;
		}
		if ((nVx < 0) && (katTerenu >= katPoprzedni))
		{
		}
		Vy += PRZYSPIESZENIE_GRAWITACYJNE * sin (katTerenu * 3.1416 / 180) * sin(katTerenu * 3.1416 / 180) * KROK_CZASOWY;
	}

	if((b2 == 1) || (b2 == 0))
	{
		y2 = BOHATER_PROMIEN2 + KROK_BOHATERA + Plansza->tabPol[k2];

		if ((nVx2 > 0) && (katTerenu <= katPoprzedni))
		{
		}
		if ((nVx2 > 0) && (katTerenu > katPoprzedni))
		{
			Vg2 = sqrt(Vx2 * Vx2 + Vy2 * Vy2);
			Vx2 = Vg2 * cos(katTerenu * 3.1416 / 180);
			Vy2 = -Vg2 * sin(katTerenu * 3.1416 / 180);
			cout << "przeliczono 2.1" << endl;
		}
		if ((nVx2 < 0) && (katTerenu < katPoprzedni))
		{
			Vg2 = sqrt(Vx2 * Vx2 + Vy2 * Vy2);
			Vx2 = -Vg2 * cos(katTerenu * 3.1416 / 180);
			Vy2 = Vg2 * sin(katTerenu * 3.1416 / 180);
			cout << "przeliczono 2.2" << endl;
		}
		if ((nVx2 < 0) && (katTerenu >= katPoprzedni))
		{
		}
		Vy2 += PRZYSPIESZENIE_GRAWITACYJNE * sin (katTerenu * 3.1416 / 180) * sin(katTerenu * 3.1416 / 180) * KROK_CZASOWY;
	}

	if (b1 == -1)
	{
		if (y - BOHATER_PROMIEN1 - KROK_BOHATERA - Vy * KROK_CZASOWY >= Plansza->tabPol[k])
		{
			y -= Vy * KROK_CZASOWY;
			Vy += PRZYSPIESZENIE_GRAWITACYJNE * KROK_CZASOWY;
		}
		else
		{
			y = BOHATER_PROMIEN1 + KROK_BOHATERA + Plansza->tabPol[k];
		}
	}

	if (b2 == -1)
	{
		if (y - BOHATER_PROMIEN2 - KROK_BOHATERA - Vy2 * KROK_CZASOWY >= Plansza->tabPol[k2])
		{
			y2 -= Vy2 * KROK_CZASOWY;
			Vy2 += PRZYSPIESZENIE_GRAWITACYJNE * KROK_CZASOWY;
		}
		else
		{
			y2 = BOHATER_PROMIEN2 + KROK_BOHATERA + Plansza->tabPol[k2];
		}
	}

	//zmiana Vx w wyniku dzialania grawitacji
	if (((b1 == 1) || (b1 == 0) || (b2 == 1) || (b2 == 0)))
	{
		Vx -= PRZYSPIESZENIE_GRAWITACYJNE * sin (katTerenu * 3.1416 / 180) * cos(katTerenu * 3.1416 / 180) * KROK_CZASOWY;
		Vx2 -=PRZYSPIESZENIE_GRAWITACYJNE * sin (katTerenu * 3.1416 / 180) * cos(katTerenu * 3.1416 / 180) * KROK_CZASOWY;
	}

	UstawKat();
	UstawXs();
	UstawYs();
	UstawX();
	UstawX2();
	katPoprzedni = katTerenu;

	if (((b1 == 1) || (b1 == 0)) || ((b2 == 1) || (b2 == 0)) && ((katTerenu >= -3) && (katTerenu <= 3)))
	{
		//Vy = 0;
		//Vy2 = 0;
	}

	cout << "b1 = " << b1 << "   " << "b2 = " << b2 << endl;
}

void cBohater::Opadaj()
{
	Vy += KROK_PRZYSPIESZANIA_BOHATERA;
}

void cBohater::Przyspieszaj(float dVx, float dVy)
{
	int b1;
	int b2;
	int k = Plansza->XDoTab(x);
	if (k < 0)
		k = 0;
	if (y - BOHATER_PROMIEN1 - 5 * KROK_BOHATERA > Plansza->tabPol[k])
	{
		b1 = -1;
	}
	else 
	{
		if(y - BOHATER_PROMIEN1 - 5 * KROK_BOHATERA == Plansza->tabPol[k])
		{
			b1 = 0;
		}
		else
		{
			b1 = 1;
		}
	}

	int k2 = Plansza->XDoTab(x2);
	if (k2 < 0)
		k2 = 0;
	if (y2 - BOHATER_PROMIEN2 - 5 * KROK_BOHATERA > Plansza->tabPol[k2])
	{
		b2 = -1;
	}
	else 
	{
		if(y2 - BOHATER_PROMIEN2 - 5 * KROK_BOHATERA == Plansza->tabPol[k2])
		{
			b2 = 0;
		}
		else
		{
			b2 = 1;
		}
	}

	if ((b1 == 0) || (b1 == 1) || (b2 == 0) || (b2 == 1))
	{
		Vx += dVx * cos(katTerenu * 3.1416 / 180);
		Vx2 += dVx * cos(katTerenu * 3.1416 / 180);
	}
}

void cBohater::ZmienKat(float dkat)
{
	kat += dkat;
	if (kat < -90) kat = 360 - kat;
	if (kat > 270) kat = -(360 - kat);
	UstawX2();
	UstawY2();
}

void cBohater::UstawX()
{
	x = xs - 0.5 * BOHATER_POZYCJA_KOLA / cos(fazaKol) * cos((kat)*3.1415/180 - fazaKol);
	y = ys - 0.5 * BOHATER_POZYCJA_KOLA / cos(fazaKol) * sin((kat)*3.1415/180 - fazaKol);
}

void cBohater::UstawX2()
{
	x2 = xs + 0.5 * BOHATER_POZYCJA_KOLA / cos(fazaKol) * cos((kat)*3.1415/180 - fazaKol);
	y2 = ys + 0.5 * BOHATER_POZYCJA_KOLA / cos(fazaKol) * sin((kat)*3.1415/180 - fazaKol);
}

void cBohater::UstawY2()
{
	y2 = y + BOHATER_POZYCJA_KOLA * sin((+kat)*3.1415/180 - fazaKol);
}

void cBohater::Przesun(float dx, float dy)
{
	x += dx;
	x2 += dx;
	y += dy;
}

void cBohater::UstawXs()
{
	xs = 0.5 * (x + x2);
}

void cBohater::UstawYs()
{
	ys = 0.5 * (y + y2);
}

void cBohater::UstawKat()
{
	kat = (atan((y2 - y)/(x2 - x)) + fazaKol) * 180 / 3.1416;

	if (kat < -80) 
		kat = -80;
	if (kat > 80) 
		kat = 80;

}

void cBohater::RysujPasekZycia()
{
	glPushMatrix();
		glTranslatef(-3*rozmiar, 6*rozmiar, 0);
		poziomZycia  = 50;
		glColor3f(0.1,0.1,0.1);
		glBegin(GL_POLYGON);
			glVertex2f(0, -0.4*rozmiar);
			glVertex2f( rozmiar*8, -0.4*rozmiar);
			glVertex2f( rozmiar*8,  0.4*rozmiar);
			glVertex2f(0,  0.4*rozmiar);
		glEnd();
		
		glColor3f(1-poziomZycia/100, poziomZycia/100, 0.0);
		glBegin(GL_POLYGON);
			glVertex2f(0.2*rozmiar, -0.32*rozmiar);
			glVertex2f( rozmiar*4*1.95*poziomZycia/100, -0.32*rozmiar);
			glVertex2f( rozmiar*4*1.95*poziomZycia/100,  0.32*rozmiar);
			glVertex2f(0.2*rozmiar,  0.32*rozmiar);
		glEnd();
	glPopMatrix();
}


bool cBohater::CzyKliknieto(float px, float py)
{
	return false;
}
void cBohater::AktualizujRamke()
{
}
void cBohater::Atakuj()
{
}
