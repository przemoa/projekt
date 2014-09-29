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

    QFile plik ("1.bin");
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

float cPlansza::Wysokosc(float x, float y)
{
	float xWTab = ((x + 1000) / 0.4 * 10);
	

	float wynik = tabPol[(int) xWTab]; + ((tabPol[((int) xWTab) + 1] - tabPol[(int) xWTab]) * (xWTab - (int) xWTab));

    float poziomBelki = Plansza->ZnajdzBelke(x, y);
    if (poziomBelki > wynik) wynik = poziomBelki;

	return wynik;



}





void cPlansza::DodajElement(int belkaP, char belkaK, char wlascicel)
{
    float x1 = Plansza->tabPunktStab[belkaP]->x;
    float x2 = Plansza->tabPunktStab[belkaK]->x;
    float y1 = Plansza->tabPunktStab[belkaP]->y;
    float y2 = Plansza->tabPunktStab[belkaK]->y;

    float xp, yp, y;
    bool czyRysowac = true;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (tabGraczy[i]->tabBohaterow[j] == NULL) continue;
            if (tabGraczy[i]->tabBohaterow[j]->zywy == false) continue;

            xp = tabGraczy[i]->tabBohaterow[j]->GetX();
            yp = tabGraczy[i]->tabBohaterow[j]->GetY();
            y = (y2 - y1) / (x2 - x1) * (xp - x1) + y1;
            if ((yp < y) && ((xp >= x1) && (xp <= x2) || (xp <= x1) && (xp >= x2)))
            {
                czyRysowac = false;
                break;
            }
        }
    }

    if(czyRysowac == true)
    {
        if (tabGraczy[wlascicel]->ZaplacZlotem(200))
        {
            cBelka *nowa = new cBelka(x1, y1, x2, y2, 15, false);
            tabElementow.push_back(nowa);
            Plansza->DodajDodanie(0x65, belkaP, belkaK);
        }

    }
}

void cPlansza::UsunElement(float x, float y)
{

}





void cPlansza::CzyBelkaWytrzyma()
{
    float momentGnacy = 0;
    float obciazenie = 0;
    float cosAlfa;
    float a, b;
    for (int i = 0; i < tabElementow.size(); i++)
    {
        cosAlfa = (tabElementow[i]->y_konca - tabElementow[i]->y_poczatku) / sqrt((pow(tabElementow[i]->y_konca - tabElementow[i]->y_poczatku, 2) + pow(tabElementow[i]->x_konca - tabElementow[i]->x_poczatku, 2)));
        a = (tabElementow[i]->y_konca - tabElementow[i]->y_poczatku) / (tabElementow[i]->x_konca - tabElementow[i]->x_poczatku);
        b = tabElementow[i]->y_poczatku - a * tabElementow[i]->x_poczatku;

        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (tabGraczy[j]->tabBohaterow[k] == NULL) continue;
                if (tabGraczy[j]->tabBohaterow[k]->zywy == false) continue;
                if ((((tabGraczy[j]->tabBohaterow[k]->GetX() > tabElementow[i]->x_poczatku) && (tabGraczy[j]->tabBohaterow[k]->GetX() < tabElementow[i]->x_konca)) || ((tabGraczy[j]->tabBohaterow[k]->GetX() < tabElementow[i]->x_poczatku) && (tabGraczy[j]->tabBohaterow[k]->GetX() > tabElementow[i]->x_konca))) && ((tabGraczy[j]->tabBohaterow[k]->GetY() < a * tabGraczy[j]->tabBohaterow[k]->GetX() + b + 2 * tabElementow[i]->grubosc / cosAlfa) && (tabGraczy[j]->tabBohaterow[k]->GetY() > a * tabGraczy[j]->tabBohaterow[k]->GetX() + b - 2 * tabElementow[i]->grubosc / cosAlfa)))
                {
                    obciazenie += tabGraczy[j]->tabBohaterow[k]->masa;
                }
            }
        }
        if (obciazenie > tabElementow[i]->wytrzymalosc)
        {
            cout << "belka zlamana" << endl;
            float xp = tabElementow[i]->x_poczatku;
            float xk = tabElementow[i]->x_konca;
            float yp = tabElementow[i]->y_poczatku;
            float yk = tabElementow[i]->y_konca;
            float xs = 0.5 * (xp + xk);
            float ys = 0.5 * (yp + yk);
            float dlugosc = sqrt((pow(tabElementow[i]->x_konca - tabElementow[i]->x_poczatku, 2)) + (pow(tabElementow[i]->y_konca - tabElementow[i]->y_poczatku, 2)));


            DodajDodanie(0x66, (char) i);

            tabElementow.erase(i + tabElementow.begin());
            cBelka *nowa = new cBelka(xp, yp, xs, ys, 100, true);
            cBelka *nowa2 = new cBelka(xk, yk, xs, ys, 100, true);


            tabElementow.push_back(nowa);
            tabElementow.push_back(nowa2);
            break;
        }
        obciazenie = 0;
    }
}

float cPlansza::ZnajdzBelke(float x, float y)
{

    float poziom_max = -1000;
    float poziom = -1000;
    for (int i = 0; i < tabElementow.size(); i++)
    {
        if(((x >= tabElementow[i]->x_poczatku) && (x <= tabElementow[i]->x_konca)) || ((x >= tabElementow[i]->x_konca) && (x <= tabElementow[i]->x_poczatku)))
        {
            poziom = (tabElementow[i]->y_konca - tabElementow[i]->y_poczatku) / (tabElementow[i]->x_konca - tabElementow[i]->x_poczatku) * x + tabElementow[i]->y_poczatku - (tabElementow[i]->y_konca - tabElementow[i]->y_poczatku) / (tabElementow[i]->x_konca - tabElementow[i]->x_poczatku) * tabElementow[i]->x_poczatku;
            poziom += tabElementow[i]->grubosc / 2 * abs(cos(atan2(tabElementow[i]->y_konca - tabElementow[i]->y_poczatku, tabElementow[i]->x_konca - tabElementow[i]->x_poczatku)));
            if((y - poziom >= -6) && (poziom > poziom_max))
            {
                poziom_max = poziom;
            }
        }
    }
    return poziom_max;

}

void cPlansza::AnimacjaBelek()
{

}

