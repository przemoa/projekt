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


    zamek = new cZamek(x, y, wlasciciel);
	zloto = 5000;		//500

	idWybrane = 0;
	levelStworkow = 0;

    tabBohaterow[0] = NULL;
    tabBohaterow[1] = NULL;
    tabBohaterow[2] = NULL;
}

void cGracz::DodajStworka(int _typStworka)
{
    switch (_typStworka)
    {
    case LISTA_STWOREK_KULA:
        if(!ZaplacZlotem(30)) return;
        break;
    case LISTA_STWOREK_KWADRAT:
        if(!ZaplacZlotem(35)) return;
        break;
    case LISTA_STWOREK_TRZY:
        if(!ZaplacZlotem(80)) return;
        break;
    case LISTA_STWOREK_CZTERY:
        if(!ZaplacZlotem(220)) return;
        break;
    }

    cStworek* nowyStworek = new cStworek(x+40*wlasciciel, -0.5, _typStworka, wlasciciel, levelStworkow);
	tabStworkow.push_back(nowyStworek);

    Plansza->DodajDodanie(0x60, ((wlasciciel==1)?0:1), _typStworka);

}


void cGracz::Dzialaj()
{
    for (int i  = 0; i < 3; i++)
	{
        if (tabBohaterow[i] == NULL) continue;
		tabBohaterow[i]->Ruszaj();
	}

	for (int i = 0; i < tabStworkow.size(); i++)
	{
        if (!(tabStworkow[i]->Atakuj())) tabStworkow[i]->Ruszaj();
	}





    for (int i  = 0; i < 3; i++)
    {
        if (tabBohaterow[i])
        {
             if (!(tabBohaterow[i]->SprawdzZycie())) tabBohaterow[i]->zywy = false;
        }
    }

    for (int i = 0; i < tabStworkow.size(); i++)
    {
        if (!(tabStworkow[i]->SprawdzZycie()))
        {
            tabStworkow.erase(tabStworkow.begin() + i);
            Plansza->DodajDodanie(0x72, ((wlasciciel==1)?0:1), (unsigned char) (i));
        }
    }



}


void cGracz::DodajBohatera(int ktory)
{

    if (tabBohaterow[ktory-1]) if (tabBohaterow[ktory-1]->zywy) return;

    if (ktory == 1) if (ZaplacZlotem(400))
    {
        if (tabBohaterow[0] == NULL)
            tabBohaterow[0] = new cBohater1(x+60*wlasciciel, y, wlasciciel);
        else tabBohaterow[0]->zywy = true;

    }
    else return;

    if (ktory == 2) if (ZaplacZlotem(500))
    {
        if (tabBohaterow[1] == NULL)
            tabBohaterow[1] = new cBohater2(x+60*wlasciciel, y, wlasciciel);
        else tabBohaterow[1]->zywy = true;
    }
    else return;

    Plansza->DodajDodanie(0x61, ((wlasciciel==1)?0:1), ktory);




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
    if (ZaplacZlotem(400))
        levelStworkow += 1;

    Plansza->DodajDodanie(0x70, ((wlasciciel==1)?0:1));
}














