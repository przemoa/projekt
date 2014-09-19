#include "cStworek.h"
#include "cPlansza.h"
#include "cGracz.h"
#include "cStworek.h"

cStworek::cStworek(void)
{
}

cStworek::cStworek(float _x, float _z, int _typStworka, int _wlasciciel, int levelStworkow)
{
	x = _x;
	z = _z;
	wlasciciel = _wlasciciel;
	rozmiar = 3;	
	typStworka = _typStworka;


	kat = 0;

	switch(_typStworka)
	{
	case LISTA_STWOREK_KULA:
		wysokosc = ROMIAR_STWORKA_KULA;
        predkosc = 55;
        mnoznikZycia = 2.1;
		zasieg = 35;
		obrazenia = 12;
        szybkoscAtaku = 30;
		break;
	case LISTA_STWOREK_KWADRAT:
		wysokosc = 35;
        predkosc = 35;
        mnoznikZycia = 2.6;
		zasieg = 55;
		obrazenia = 15;
		szybkoscAtaku = 15; 
		break;
    case LISTA_STWOREK_TROJKAT:
        wysokosc = 1.5 * ROZMIAR_STWORKA_TROJKAT;
        predkosc = 100;
        mnoznikZycia = 1.6;
        zasieg = 85;
        obrazenia = 8;
        szybkoscAtaku = 65;
        break;
    case LISTA_STWOREK_JAJO:
        wysokosc = 20;
        predkosc = 70;
        mnoznikZycia = 4;
        zasieg = 50;
        obrazenia = 85;
        szybkoscAtaku = 20;
        break;
	}

    predkosc += predkosc*levelStworkow*1.03+1;
    mnoznikZycia += mnoznikZycia*levelStworkow*1.03+2;
    zasieg += zasieg*levelStworkow*1.03+2;
    obrazenia += obrazenia*levelStworkow*1.03+2;
    szybkoscAtaku += szybkoscAtaku*levelStworkow*1.03+3;

	y = Plansza->tabPol[Plansza->XDoTab(x)] + wysokosc;
	yCel = y;

}

cStworek::~cStworek(void)
{

}

void cStworek::Ruszaj()
{


	int xTab = Plansza->XDoTab(x);
	float dx = 0;

    if (typStworka == LISTA_STWOREK_KWADRAT || typStworka == LISTA_STWOREK_JAJO)
	{
		dx = wlasciciel * predkosc;
	}
    else if (typStworka == LISTA_STWOREK_KULA || typStworka == LISTA_STWOREK_TROJKAT)
	{
		dx = Plansza->tabPol[xTab-30] - Plansza->tabPol[xTab+30];

		dx = wlasciciel*predkosc + 10*dx;				// todo

		switch (wlasciciel)
		{ 
		case 1:
			if (dx < 5) dx = 5;
			if (dx > predkosc*2) dx = predkosc*2;
			break;
		case -1:
			if (dx > -5) dx = -5;
			if (dx < -predkosc*2) dx = -predkosc*2;
			break;
		}
	}

	dx /= 100;
	x += dx;
	yCel = Plansza->tabPol[Plansza->XDoTab(x)]  + wysokosc;
	y += 0.2/wysokosc*abs(yCel-y)*(yCel-y);
	
}

bool cStworek::Atakuj()
{


    int nrKogo = ((wlasciciel == 1) ? 1 : 0); // ktorego gracza z tablicy stowrek ma atakowac
    cGracz* kogo =  Plansza->tabGraczy[nrKogo];

    float odlegloscMin = 99999;
    int nrDoAtakowania = -1;
    for (unsigned int i = 0; i < kogo->tabStworkow.size(); i++)
    {
        float odleglosc = sqrt(pow(x - kogo->tabStworkow[i]->x, 2) + pow(y - kogo->tabStworkow[i]->y, 2));
        if (odleglosc < odlegloscMin)
        {
            odlegloscMin = odleglosc;
            nrDoAtakowania = i;
        }
    }

    if (odlegloscMin < zasieg)          // jezeli w poblizu stworek - atakuj
    {
        if (turDoAtaku > 0)        // ograniczenie czestosci strzelania
        {
            turDoAtaku--;
            return true;
        }
        else
        {
            kogo->tabStworkow[nrDoAtakowania]->poziomZycia -= obrazenia / kogo->tabStworkow[nrDoAtakowania]->mnoznikZycia;
            turDoAtaku = 1000.0/szybkoscAtaku;
            return true;
        }
    }




    for (int i = 0; i < 2; i++)
    {
        if (kogo->tabBohaterow[i] != NULL)
        {
            if (kogo->tabBohaterow[i]->zywy)
            {
                float odleglosc = sqrt(pow(x - kogo->tabBohaterow[i]->x, 2) + pow(y - kogo->tabBohaterow[i]->y, 2));
                if (zasieg > odleglosc)
                {
                    if (turDoAtaku > 0)        // ograniczenie czestosci strzelania
                    {
                        turDoAtaku--;
                        return true;
                    }
                    else
                    {
                        kogo->tabBohaterow[i]->poziomZycia -= obrazenia / kogo->tabBohaterow[i]->mnoznikZycia;
                        turDoAtaku = 1000.0/szybkoscAtaku;
                        return true;
                    }
                }
            }
        }
    }

    float odleglosc = sqrt(pow(x - kogo->zamek->x, 2) + pow(y - kogo->zamek->y, 2));
    if (zasieg > odleglosc)      // todo dodac rozmiar zamku
    {
        if (turDoAtaku > 0)        // ograniczenie czestosci strzelania
        {
            turDoAtaku--;
            return true;
        }
        else
        {
            kogo->zamek->poziomZycia -= obrazenia / kogo->zamek->mnoznikZycia;
            turDoAtaku = 1000.0/szybkoscAtaku;
            return true;
        }

    }




    return false;
}



bool cStworek::SprawdzZycie()
{
    if (poziomZycia < 0) return false;
    else return true;
}
