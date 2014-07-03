#include "cZamek.h"
#include "cPlansza.h"

cZamek::cZamek(void)
{
}


cZamek::~cZamek(void)
{
}



cZamek::cZamek(float _x, float _y, int _wlasciciel)
{
	x = _x;
	y = _y;
	rozmiar = 25;
	rozmiarWiezy = rozmiar/4.2;
	wysokoscWiezy = 3*rozmiarWiezy;

	poziomZycia = 100;

	wlasciciel = _wlasciciel;

//	DodajWieze(11, 100);
//	DodajWieze(12, 100);
//	DodajWieze(13, 300);
//	DodajWieze(14, 300);
//	DodajWieze(15, 300);
//	DodajWieze(17, 100);
//	DodajWieze(16, 200);


	mnoznikZycia = 15;
	wydobycie = 10;

}

void cZamek::DodajWieze(int _typWiezy, int pozycja)
{

	sWIEZA nowaWieza;
	for (int i = 0; i < tabWiez.size(); i++)
	{
		if (pozycja/100 == tabWiez[i].pozycja/100)
		{
			if (pozycja < tabWiez[i].pozycja) pozycja = tabWiez[i].pozycja;
		}
	}
	pozycja++;

	nowaWieza.pozycja = pozycja;
	nowaWieza.typWiezy = _typWiezy;
	nowaWieza.level = 1;
	nowaWieza.czyAtakuje = true;
	nowaWieza.x = x + (pozycja/100 -2) * rozmiarWiezy * 3;
	nowaWieza.y = y + 1.2*rozmiar + (pozycja%100) * wysokoscWiezy;

	switch (_typWiezy)
	{
	case TEKSTURA_WIEZA1:		// luk, srednioszybka, male obrazenia, sredni zasieg
		nowaWieza.obrazenia = 15;
		nowaWieza.zasieg = 150;
		nowaWieza.szybkoscAtaku = 35;
		break;
	case TEKSTURA_WIEZA2:		// kamien, malas szybkosc, srednie obrazenia, maly zasieg
		nowaWieza.obrazenia = 25;
		nowaWieza.zasieg = 100;
		nowaWieza.szybkoscAtaku = 20;
		break;
	case TEKSTURA_WIEZA3:		// pocisk, srednia szybkosc, srednie obrazenia, sredni zasieg
		nowaWieza.obrazenia = 35;
		nowaWieza.zasieg = 250;
		nowaWieza.szybkoscAtaku = 35;
		break;
	case TEKSTURA_WIEZA4:		// laser, malas szybkosc, duze obrazenia, duzy zasieg
		nowaWieza.obrazenia = 95;
		nowaWieza.zasieg = 350;
		nowaWieza.szybkoscAtaku = 10;
		break;
	case TEKSTURA_WIEZA5:		// ogien, mala szybkosc, duze obrazenia, maly zasieg
		nowaWieza.obrazenia = 40;
		nowaWieza.zasieg = 80;
		nowaWieza.szybkoscAtaku = 20;
		break;
	case TEKSTURA_WIEZA6:		// produkuje zloto
		nowaWieza.obrazenia = 5;
		nowaWieza.czyAtakuje = false;
		break;
	case TEKSTURA_WIEZA7:		// leczy zamek
		nowaWieza.obrazenia = 10;
		nowaWieza.czyAtakuje = false;
		break;
	}

	tabWiez.insert(tabWiez.begin(), nowaWieza);

}


void cZamek::Atakuj()
{
}

void cZamek::Awansuj()
{
	rozmiar += 1;
	rozmiarWiezy = rozmiar/4.2;
	wysokoscWiezy = 3*rozmiarWiezy;

	poziomZycia += 10;
	if (poziomZycia > 100) poziomZycia = 100;

	mnoznikZycia += 1;
	wydobycie += 1;

	for (int i = 0; i < tabWiez.size(); i++)
	{
		tabWiez[i].x = x + (tabWiez[i].pozycja/100 -2) * rozmiarWiezy * 3;
		tabWiez[i].y = y + 1.2*rozmiar + (tabWiez[i].pozycja%100) * wysokoscWiezy;
	}
}

void cZamek::AwansujWieze(int i)
{

    switch (tabWiez[i].typWiezy)
    {
    case TEKSTURA_WIEZA1:		// luk, srednioszybka, male obrazenia, sredni zasieg
        tabWiez[i].obrazenia += 4;
        tabWiez[i].zasieg += 20;
        tabWiez[i].szybkoscAtaku += 6;
        break;
    case TEKSTURA_WIEZA2:		// kamien, malas szybkosc, srednie obrazenia, maly zasieg
        tabWiez[i].obrazenia += 6;
        tabWiez[i].zasieg += 12;
        tabWiez[i].szybkoscAtaku += 4;
        break;
    case TEKSTURA_WIEZA3:		// pocisk, srednia szybkosc, srednie obrazenia, sredni zasieg
        tabWiez[i].obrazenia += 6;
        tabWiez[i].zasieg += 25;
        tabWiez[i].szybkoscAtaku += 6;
        break;
    case TEKSTURA_WIEZA4:		// laser, malas szybkosc, duze obrazenia, duzy zasieg
        tabWiez[i].obrazenia += 15;
        tabWiez[i].zasieg += 35;
        tabWiez[i].szybkoscAtaku += 2;
        break;
    case TEKSTURA_WIEZA5:		// ogien, mala szybkosc, duze obrazenia, maly zasieg
        tabWiez[i].obrazenia += 6;
        tabWiez[i].zasieg += 10;
        tabWiez[i].szybkoscAtaku += 5;
        break;
    case TEKSTURA_WIEZA6:		// produkuje zloto
        tabWiez[i].obrazenia += 2;
        break;
    case TEKSTURA_WIEZA7:		// leczy zamek
        tabWiez[i].obrazenia += 2;
        break;
    }
}

void cZamek::SprzedajWieze(int i)
{
    tabWiez.erase(tabWiez.begin() + i);
}
