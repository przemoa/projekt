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
	z = 0;
	kat = 0;
	Vy = 0;
	yCel = y;
	VyCel = Vy;
	odbity = false;
	mocSilnika = 10;
	energia = 0;
	kierunek = 1;
}

void cBohater::Rysuj()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		RysujPasekZycia();
		glRotatef(kat, 0, 0, 1);
		glColor4f(1,0,0, 1);  //todo
		glCallList(LISTA_BOHATER_A1);
	glPopMatrix();

}

void cBohater::Ruszaj()
{
	cout << energia << endl;
	float poziomZiemi = Plansza->Wysokosc(x);

	yCel += VyCel;
	y += 0.15*(yCel - y);
	Vy += 0.15*(VyCel - Vy);
	

	if (energia != 0)
	{
		float dx = sqrt(energia)*kierunek / 20;
		float poziomZiemi2 = Plansza->Wysokosc(x+dx);
		
		if (y - 0.11 > poziomZiemi && y - 0.11 > poziomZiemi2) x += dx;
		else
		{
			float dE = (poziomZiemi - poziomZiemi2) * 20;
			float energia2 = energia + dE;
			
			if (energia2 > 0)
			{
				x += dx;	
				yCel += poziomZiemi2 - poziomZiemi;
				energia = energia2;
			}
			else { energia = 0; kierunek = 0; }
		}
	}

	

	if (odbity)
	{
		if (y - 6 > poziomZiemi)
			odbity = false;
	}
	else
	{
		if (y < poziomZiemi)
		{
			Vy = - Vy;
			VyCel = -VyCel;
			odbity = true;
		}
	}
	if (y - 0.05 > poziomZiemi)
	{
		VyCel -= PRZYSPIESZENIE_GRAWITACYJNE;
		if (VyCel > 0) VyCel -= 0.12;
	}
	if (odbity == true && Vy < 0 && y - 0.2 < poziomZiemi)
	{
		VyCel = 0;
		yCel = poziomZiemi;
	}

	if (energia == 0)
	{
		float poziomZiemi2 = Plansza->Wysokosc(x + 2);
		if (poziomZiemi2 - poziomZiemi > 1)
		{
			kierunek = -1;
			energia = 15;
		}

		poziomZiemi2 = Plansza->Wysokosc(x - 2);
		if (poziomZiemi2 - poziomZiemi > 1)
		{
			kierunek = 1;
			energia = 15;
		}
	}

	if (y + 0.1 < poziomZiemi) y = poziomZiemi;
	VyCel *= 0.99;
	energia *= 0.998;
	energia -= 0.3;
	if (energia < 0) { energia = 0; kierunek = 0; }
}


void cBohater::Przyspieszaj(float dVx, float dVy)
{
	int zwrot = abs(dVx)/dVx;

	if (energia < 5*mocSilnika*abs(dVx))
	{
		int tabX = Plansza->XDoTab(x);
		if (Plansza->tabPol[tabX + zwrot*60] -Plansza->tabPol[tabX] < 1.2)
		{
			energia = 6*mocSilnika*abs(dVx);
		}
		else return;

		if (kierunek == -zwrot)
		{
			kierunek = 0;
			energia = 0;
		}
		else
			kierunek = zwrot;
	}
	else if (kierunek == zwrot) energia += mocSilnika*abs(dVx);
	else if (kierunek != zwrot) energia -= mocSilnika*3*abs(dVx);

	if (energia < 0) energia = 0;

}

void cBohater::ZmienKat(float dkat)
{
	kat += dkat;
	if (kat < -90) kat = 360 - kat;
	if (kat > 270) kat = -(360 - kat);
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
