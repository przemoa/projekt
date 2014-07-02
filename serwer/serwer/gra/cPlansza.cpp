#include "cPlansza.h"
#include "naglowki.h"



cPlansza::cPlansza(void)
{




	// wczytaj plansze
	for (int k = 0; k < 50000; k+=10)
	{
		tabPol[k] = -7777;
		tabTypowPol[k] = -7777;
	}
	WczytajTeren();


}

cPlansza::~cPlansza(void)
{

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
	FILE* odczytTerenu = fopen("tx\\1.bin", "r");
    unsigned char* tablicaPikseli = new unsigned char[5000*850];
	fread(tablicaPikseli, 1, 5000*850, odczytTerenu);
	fclose(odczytTerenu);



	for (int k = 0; k < 5000; k++)				// przepisz z wektra do tabeli p�l i wykonaje pola specjalne
	{
		for (int w = 849; w >= 0; w--)
		{
			unsigned char pole = tablicaPikseli[w*5000 + k];

			if (pole == POLE_TLO) continue;

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
	delete [] tablicaPikseli;

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
	
	//float y1 = tabPol[(int) xWTab];
	//float y2 = tabPol[((int) xWTab) + 1];
	//float x2 = (int) xWTab;
	//float wynik = y1 + (y2 - y1) * (xWTab - x2);
	float wynik = tabPol[(int) xWTab]; + ((tabPol[((int) xWTab) + 1] - tabPol[(int) xWTab]) * (xWTab - (int) xWTab));
	return wynik;

}



