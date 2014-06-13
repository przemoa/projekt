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
	DodajBohatera(_x + _wlascicel*50, 122);

	x = _x;
	y = _y;
	wlasciciel = _wlascicel;

	kolor.r = 1;
	kolor.g = 0;
	kolor.b = 0;

	zamek = new cZamek(_x, 62 + ((wlasciciel==-1) ? 40 : 0), wlasciciel);
	zloto = 500;
	idWybrane = 0;
	


}

void cGracz::DodajStworka(float _x, int _typStworka)
{
	cStworek* nowyStworek = new cStworek(_x, -0.5, _typStworka, wlasciciel);
	tabStworkow.push_back(nowyStworek);
}

void cGracz::AktualizujRamke()
{

	for (int i  = 0; i < tabBohaterow.size(); i++)
	{
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

void cGracz::Dzialaj()
{
	for (int i  = 0; i < tabBohaterow.size(); i++)
	{
		tabBohaterow[i]->Ruszaj();
	}

	for (int i = 0; i < tabStworkow.size(); i++)
	{
		tabStworkow[i]->Ruszaj();
	}
}

void cGracz::FocusujKamere() 
{
	// sprawdzenie czy to aktualnie wybrana jednostka i ustawienie focusa kamery

	for (int i  = 0; i < tabBohaterow.size(); i++)
	{
		if (tabBohaterow[i]->GetId() == idWybrane)			
		{
			float odlegloscX = -tabBohaterow[i]->GetX()+Plansza->kamera.xCel;
			float odlegloscY = tabBohaterow[i]->GetY()-Plansza->kamera.yCel + Plansza->kamera.zakres/3.0;

			if (abs(odlegloscX) > Plansza->kamera.zakres)
				Plansza->PrzesunKamere(odlegloscX, 0);
			if (abs(odlegloscY) > Plansza->kamera.zakres / 2.0)
				Plansza->PrzesunKamere(0, odlegloscY);

		}
	}

	for (int i = 0; i < tabStworkow.size(); i++)
	{

		if (tabStworkow[i]->GetId() == idWybrane)			
		{
			Plansza->PrzesunKamere(-tabStworkow[i]->GetX()+Plansza->kamera.xCel, tabStworkow[i]->GetY()-Plansza->kamera.yCel + Plansza->kamera.zakres/3.0 );
		}
	}


}

void cGracz::DodajBohatera(float _x, float _y)
{
	//if (wybranyBohater == -1) wybranyBohater = 0;
	cBohater * nowyBohater = new cBohater2(_x+10, _y, wlasciciel);
	tabBohaterow.push_back(nowyBohater);

	//nowyBohater = new cBohater(_x, _y, wlascicel);
	//tabBohaterow.push_back(nowyBohater);
}

void cGracz::PrzyspieszajBohatera(float dVx, float dVy)
{
	if (wybranyBohater < 0) return;
	tabBohaterow[wybranyBohater]->Przyspieszaj(dVx, dVy);
}

void cGracz::Rysuj()
{
	for (int i = 0; i < tabBohaterow.size(); i++)
	{
		tabBohaterow[i]->Rysuj();
	}

	zamek->Rysuj();

	for (int i = 0; i < tabStworkow.size(); i++)
	{
		tabStworkow[i]->Rysuj();
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
	for (int i = 0; i < tabBohaterow.size(); i++)
	{
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
















