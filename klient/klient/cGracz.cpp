#include "cGracz.h"
#include "cBohater2.h"
#include "cBohater1.h"
#include "cPlansza.h"

cGracz::cGracz(void)
{

}

cGracz::~cGracz(void)
{

}

cGracz::cGracz(float _x, float _y, int _wlascicel)
{
	wybranyBohater = -1;

	if (_wlascicel == 1)
	{
		x = _x;
		y = 62;
	}
	if (_wlascicel == -1)
	{
		x = _x + 200;
		y = 57;
	}


	wlasciciel = _wlascicel;

	kolor.r = 1;
	kolor.g = 0;
	kolor.b = 0;

	zamek = new cZamek(x, y, wlasciciel);
	zloto = 0;		//0
	sprintf(napisZloto, "x %d", (int) zloto);

	idWybrane = 0;
	levelStworkow = 0;

	tabBohaterow[0] = NULL;
	tabBohaterow[1] = NULL;
	tabBohaterow[2] = NULL;


}

void cGracz::DodajStworka(float _x, int _typStworka)
{
	Plansza->DodajAkcje(0x07, _typStworka); 
}

void cGracz::AktualizujRamke()
{

	sprintf(napisZloto, "x %d", (int) zloto);
	for (int i  = 0; i < 3; i++)
	{
		if (tabBohaterow[i] == NULL) continue;
		if (tabBohaterow[i]->GetId() == idWybrane)
			tabBohaterow[i]->AktualizujRamke();
	}

	for (int i = 0; i < tabStworkow.size(); i++)
	{
		if (tabStworkow[i]->GetId() == idWybrane)
			tabStworkow[i]->AktualizujRamke();
	}

	if (zamek->GetId() == idWybrane)
		zamek->AktualizujRamke();
}

void cGracz::FocusujKamere() 
{
	// sprawdzenie czy to aktualnie wybrana jednostka i ustawienie focusa kamery

	for (int i  = 0; i < 3; i++)
	{
		if (tabBohaterow[i] == NULL) continue;
		if (tabBohaterow[i]->GetId() == idWybrane)			
		{
			float odlegloscX = -tabBohaterow[i]->GetX()+Plansza->kamera.xCel;
			float odlegloscY = tabBohaterow[i]->GetY()-Plansza->kamera.yCel + Plansza->kamera.zakres/3.0;

			if (abs(odlegloscX) > Plansza->kamera.zakres)
				Plansza->PrzesunKamere(1.3*odlegloscX, 0);
			if (abs(odlegloscY) > Plansza->kamera.zakres / 2.0)
				Plansza->PrzesunKamere(0, odlegloscY);

		}
	}

	for (int i = 0; i < tabStworkow.size(); i++)
	{

		if (tabStworkow[i]->GetId() == idWybrane)			
		{
			float odlegloscX = -tabStworkow[i]->GetX()+Plansza->kamera.xCel;
			float odlegloscY = tabStworkow[i]->GetY()-Plansza->kamera.yCel + Plansza->kamera.zakres/3.0;

			if (abs(odlegloscX) > Plansza->kamera.zakres)
				Plansza->PrzesunKamere(1.3*odlegloscX, 0);
			if (abs(odlegloscY) > Plansza->kamera.zakres / 2.0)
				Plansza->PrzesunKamere(0, odlegloscY);
		}
	}
}

void cGracz::DodajBohatera(float _x, float _y, int ktory)
{
	Plansza->DodajAkcje(0x04, ktory);
}

void cGracz::PrzyspieszajBohatera(float dVx, float dVy)
{
	if (wybranyBohater < 0) return;

	if (Plansza->wcisnieteA) Plansza->DodajAkcje(0x20, wybranyBohater);
	else if (Plansza->wcisnieteD) Plansza->DodajAkcje(0x21, wybranyBohater);

}

void cGracz::Rysuj()
{
	for (int i = 0; i < 3; i++)
	{
		if (tabBohaterow[i] == NULL) continue;
		tabBohaterow[i]->Rysuj();

		if (tabBohaterow[i]->GetId() == idWybrane)
		{
			glPushMatrix();

				glColor3f(1, 0, 0);
				glLineWidth(3);
				glTranslatef(tabBohaterow[i]->x, tabBohaterow[i]->y, 0);
				glBegin(GL_LINE_LOOP);
					for (int j = 0; j < 133; j++)
					{
						glVertex2f(tabBohaterow[i]->zasieg * sin(6.2832*j/133), tabBohaterow[i]->zasieg * cos(6.2832*j/133));
					}
				glEnd();

			glPopMatrix();
		}

	}

	zamek->Rysuj();

	for (int i = 0; i < tabStworkow.size(); i++)
	{
		tabStworkow[i]->Rysuj();
		if (tabStworkow[i]->GetId() == idWybrane)
		{
			glPushMatrix();

				glColor3f(1, 0, 0);
				glLineWidth(3);
				glTranslatef(tabStworkow[i]->x, tabStworkow[i]->y, 0);
				glBegin(GL_LINE_LOOP);
					for (int j = 0; j < 133; j++)
					{
						glVertex2f(tabStworkow[i]->zasieg * sin(6.2832*j/133), tabStworkow[i]->zasieg * cos(6.2832*j/133));
					}
				glEnd();

			glPopMatrix();
		}
	}
}


bool cGracz::WybierzJednostke(float px, float py)
{
	idWybrane = 0;


	if (zamek->CzyKliknieto(px, py))
	{
		idWybrane = zamek->GetId();
		zamek->AktualizujRamke();
	}

	for (int i = 0; i < tabStworkow.size(); i++)
	{
		if (tabStworkow[i]->CzyKliknieto(px, py))
		{
			idWybrane = tabStworkow[i]->GetId();
			tabStworkow[i]->AktualizujRamke();

		}
	}

	wybranyBohater = -1;
	for (int i = 0; i < 3; i++)
	{
		if (tabBohaterow[i] == NULL) continue;
		if (tabBohaterow[i]->CzyKliknieto(px, py))
		{
			idWybrane = tabBohaterow[i]->GetId();
			tabBohaterow[i]->AktualizujRamke();
			wybranyBohater = i;
		}
	}

	if (idWybrane == 0) return false;
	else return true;
}

bool cGracz::ZaplacZlotem(int ile)
{
	if (zloto >= ile)
	{
		return true;
	}
	else return false;
}

void cGracz::AwansujStworki()
{
	Plansza->DodajAkcje(0x14);
}














