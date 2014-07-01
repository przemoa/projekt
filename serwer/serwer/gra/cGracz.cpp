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

	x = _x;
	y = _y;
	wlasciciel = _wlascicel;


	zamek = new cZamek(_x, 62 + ((wlasciciel==-1) ? 40 : 0), wlasciciel);
	zloto = 5000;		//500

	idWybrane = 0;
	levelStworkow = 0;


}

void cGracz::DodajStworka(float _x, int _typStworka)
{
	cStworek* nowyStworek = new cStworek(_x+40*wlasciciel, -0.5, _typStworka, wlasciciel, levelStworkow);
	tabStworkow.push_back(nowyStworek);
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


void cGracz::DodajBohatera(float _x, float _y, int ktory)
{
	
	cBohater * nowyBohater;

	if (ktory == 1) nowyBohater = new cBohater1(_x+60*wlasciciel, _y, wlasciciel);
	if (ktory == 2) nowyBohater = new cBohater2(_x+60*wlasciciel, _y, wlasciciel);

	tabBohaterow.push_back(nowyBohater);


}

void cGracz::PrzyspieszajBohatera(float dVx, float dVy)
{
	if (wybranyBohater < 0) return;
	tabBohaterow[wybranyBohater]->Przyspieszaj(dVx, dVy);
}


bool cGracz::ZaplacZlotem(int ile)
{
	if (zloto >= ile)
	{
		zloto -= ile;
		return true;
	}
	else return false;
}

void cGracz::AwansujStworki()
{
	levelStworkow += 1;
}














