#include "cPlansza.h"
#include "naglowki.h"
#include "qfile.h"


cPlansza::cPlansza(void)
{

    nrTury = 0;


	// wczytaj plansze
	for (int k = 0; k < 50000; k+=10)
	{
		tabPol[k] = -7777;
		tabTypowPol[k] = -7777;
	}
	WczytajTeren();
    bajtyBuforuDodan = 0;

}

cPlansza::~cPlansza(void)
{

}



void cPlansza::DodajDodanie(char pierwszy, char drugi , char trzeci, char czwarty)
{

    buforDodan[bajtyBuforuDodan] = pierwszy;
    bajtyBuforuDodan++;


        buforDodan[bajtyBuforuDodan] = drugi;
        bajtyBuforuDodan++;



        buforDodan[bajtyBuforuDodan] = trzeci;
        bajtyBuforuDodan++;



        buforDodan[bajtyBuforuDodan] = czwarty;
        bajtyBuforuDodan++;

}

void cPlansza::DodajDodanie(char pierwszy, char drugi , char trzeci)
{

    buforDodan[bajtyBuforuDodan] = pierwszy;
    bajtyBuforuDodan++;


        buforDodan[bajtyBuforuDodan] = drugi;
        bajtyBuforuDodan++;



        buforDodan[bajtyBuforuDodan] = trzeci;
        bajtyBuforuDodan++;


}

void cPlansza::DodajDodanie(char pierwszy, char drugi)
{

    buforDodan[bajtyBuforuDodan] = pierwszy;
    bajtyBuforuDodan++;


        buforDodan[bajtyBuforuDodan] = drugi;
        bajtyBuforuDodan++;

}

void cPlansza::DodajDodanie(char pierwszy)
{

    buforDodan[bajtyBuforuDodan] = pierwszy;
    bajtyBuforuDodan++;

}



void cPlansza::_Dzialaj(int value)
{

    for (int i = 0; i < tabGraczy.size(); i++)
    {
        tabGraczy[i]->Dzialaj();
    }
}




void cPlansza::WczytajTeren()
{

    QFile plik ("C:\\1.bin");
    plik.open(QIODevice::ReadOnly);
    QByteArray tablicaPikseli = plik.readAll();
    plik.close();

	for (int k = 0; k < 5000; k++)				// przepisz z wektra do tabeli pól i wykonaje pola specjalne
	{
		for (int w = 849; w >= 0; w--)
		{
			unsigned char pole = tablicaPikseli[w*5000 + k];

			if (pole == POLE_TLO) continue;
            if (pole == 8)
            {

                int a = 99;
                int b = a;
                a = b;
            }

			switch (pole)
            {
			case POLE_GRACZ:
				{
					int kierunek = 1 - 2*tabGraczy.size();
					cGracz* nowyGracz = new cGracz(TabDoX(k*10), TabDoY(w), kierunek);
					tabGraczy.push_back(nowyGracz);
				}
				pole = POLE_TLO;
				break;

			case POLE_PALMA:
				pole = POLE_TLO;
				break;

			case POLE_PUNKT_STABILNY: 
				DodajPunktStabilny(TabDoX(k*10), TabDoY(w));
				pole = POLE_TLO;
			}
			if (pole == POLE_TLO) continue;

			if (tabPol[k*10] == -7777)
			{
				float wynik = TabDoY(w) + 0.65;
				tabPol[k*10] = wynik;
				tabTypowPol[k*10] = pole;
			}
		}
	}


	for (int k = 0; k < 50000; k++)
	{
		if (k%10 == 0) continue;
		int ktory = k % 10;
		tabPol[k] = tabPol[k - ktory] + ktory / 10.0 * (tabPol[k - ktory+10] - tabPol[k - ktory]);
	}

}

void cPlansza::DodajPunktStabilny(float _x, float _y)
{
	cPunktStabilny* nowyPunkt = new cPunktStabilny(_x, _y, 0);
	tabPunktStab.push_back(nowyPunkt);
}



float cPlansza::TabDoX(int k)
{
	return (-1000 + 0.4*k / 10);
}

float cPlansza::TabDoY(int w)
{
	return (0.4*w - 170);
}

int cPlansza::XDoTab(float x)
{
	return ((x + 1000) / 0.4 * 10) + 0.5;
}

int cPlansza::YDoTab(float y)
{
	return ((y+170) / 0.4) + 0.5;
}

float cPlansza::Wysokosc(float x)
{
	float xWTab = ((x + 1000) / 0.4 * 10);
	

	float wynik = tabPol[(int) xWTab]; + ((tabPol[((int) xWTab) + 1] - tabPol[(int) xWTab]) * (xWTab - (int) xWTab));
	return wynik;

}




