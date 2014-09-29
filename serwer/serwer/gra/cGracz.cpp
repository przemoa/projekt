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
    liczbaStworkow = 0;
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
    case LISTA_STWOREK_TROJKAT:
        if(!ZaplacZlotem(80)) return;
        break;
    case LISTA_STWOREK_JAJO:
        if(!ZaplacZlotem(150)) return;
        break;
    }

    cStworek* nowyStworek = new cStworek(x+40*wlasciciel, -0.5, _typStworka, wlasciciel, levelStworkow);
	tabStworkow.push_back(nowyStworek);
    liczbaStworkow++;
    Plansza->DodajDodanie(0x60, ((wlasciciel==1)?0:1), _typStworka);

}

void cGracz::Dzialaj()
{
    if(Plansza->nrTury%100==99) zloto += zamek->wydobycie;

    for (int i  = 0; i < 3; i++)
	{
        if (tabBohaterow[i] == NULL) continue;
        if (tabBohaterow[i]->zywy == false) continue;
		tabBohaterow[i]->Ruszaj();
        tabBohaterow[i]->Atakuj();
	}

    zamek->Atakuj();

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
            liczbaStworkow--;
        }
    }


    if (zamek->poziomZycia < 0)
    {

        Plansza->koniecGry = true;
    }



}


void cGracz::DodajBohatera(int ktory)
{

    if (tabBohaterow[ktory-1]) if (tabBohaterow[ktory-1]->zywy) return;

    if (ktory == 1) if (ZaplacZlotem(400))
    {
        if (tabBohaterow[0] == NULL)
            tabBohaterow[0] = new cBohater1(x+60*wlasciciel, y, wlasciciel);
        else
        {
            tabBohaterow[0]->zywy = true;
            tabBohaterow[0]->poziomZycia = 100;
            tabBohaterow[0]->x = tabBohaterow[0]->xBaz;
            tabBohaterow[0]->y = tabBohaterow[0]->yBaz+60;
            tabBohaterow[0]->poziomZycia = 100;
        }

    }
    else return;

    if (ktory == 2) if (ZaplacZlotem(500))
    {
        if (tabBohaterow[1] == NULL)
            tabBohaterow[1] = new cBohater2(x+60*wlasciciel, y, wlasciciel);
        else
        {
            tabBohaterow[1]->zywy = true;
            tabBohaterow[1]->x = tabBohaterow[1]->xBaz;
            tabBohaterow[1]->y = tabBohaterow[1]->yBaz+60;
            tabBohaterow[1]->poziomZycia = 100;
        }
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














