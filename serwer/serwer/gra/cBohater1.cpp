﻿#include "cBohater1.h"
#include "naglowki.h"
#include "cPlansza.h"

cBohater1::cBohater1(void)
{
}


cBohater1::~cBohater1(void)
{
}

cBohater1::cBohater1(float _x, float _y, int _wlascicel)
{
	wlasciciel = _wlascicel;
	xBaz = x = _x;
	yBaz = y = _y;
    y = yBaz + 30;
	z = 0;
	Vx = 0;
	Vy = 0;
	Vx2 = 0;
	Vy2 = 0;
	Vg = 0;
	Vg2 = 0;
	Vkatowa = 0;
	rozmiar = 2;
	kat = 0;
    mocSilnika = 5;
	fazaKol = atan2(BOHATER_PROMIEN1 - BOHATER_PROMIEN2, BOHATER_POZYCJA_KOLA);
	x2 = x + BOHATER_POZYCJA_KOLA / cos(fazaKol) * cos((kat)*3.1415/180 - fazaKol);
	y2 = y + BOHATER_POZYCJA_KOLA / cos(fazaKol) * sin((kat)*3.1415/180 - fazaKol);
	UstawXs();
	UstawYs();
	katPoprzedni = 0;
    masa = 100;

    energia = 0;
    mnoznikZycia = 13.5;
    poziomZycia = 100;
    zasieg = 90;
    obrazenia = 70;
    szybkoscAtaku = 14;
}



void cBohater1::Ruszaj()
{
    Vx*= 0.99;      //testowe!!!


    int b1, b2;			// 0 - bez zmian, 1 - podnosi się do góry, -1 - opada w dół

    Przesun(Vx * KROK_CZASOWY, 0);

    //wyznaczenie ktore kolo moze opadac
    int k = Plansza->XDoTab(x);
    if (k < 0)
        k = 0;
    float poziomTerenu1;
    if(Plansza->ZnajdzBelke(x, y) > Plansza->tabPol[k])
        poziomTerenu1 = Plansza->ZnajdzBelke(x, y);
    else
        poziomTerenu1 = Plansza->tabPol[k];


    if (y - BOHATER_PROMIEN1 - KROK_BOHATERA > poziomTerenu1)
    {
        b1 = -1;
    }
    else
    {
        if(y - BOHATER_PROMIEN1 - KROK_BOHATERA == poziomTerenu1)
        {
            b1 = 0;
        }
        else
        {
            b1 = 1;
        }
    }

    int k2 = Plansza->XDoTab(x2);
    if (k2 < 0)
        k2 = 0;
    float poziomTerenu2;
    if(Plansza->ZnajdzBelke(x2, y2) > Plansza->tabPol[k2])
        poziomTerenu2 = Plansza->ZnajdzBelke(x2, y2);
    else
        poziomTerenu2 = Plansza->tabPol[k2];
    if (y2 - BOHATER_PROMIEN2 - KROK_BOHATERA > poziomTerenu2)
    {
        b2 = -1;
    }
    else
    {
        if(y2 - BOHATER_PROMIEN2 - KROK_BOHATERA == poziomTerenu2)
        {
            b2 = 0;
        }
        else
        {
            b2 = 1;
        }
    }


    katTerenu = atan((poziomTerenu2 - poziomTerenu1)/(x2 - x)) * 180 / 3.1416;

    float nVx = Vx;
    float nVx2 = Vx2;

    //jesli tylne kolo jest na ziemi
    if ((b1 == 1) || (b1 == 0))
    {
        y = BOHATER_PROMIEN1 + KROK_BOHATERA + poziomTerenu1;

        if ((nVx > 0) && (katTerenu <= katPoprzedni))
        {
        }

        if ((nVx > 0) && (katTerenu > katPoprzedni))
        {
            Vg = sqrt(Vx * Vx + Vy * Vy);
            Vx = Vg * cos(kat * 3.1416 / 180 - fazaKol);
            Vy = -Vg * sin(kat * 3.1416 / 180 - fazaKol);
        }

        if ((nVx < 0) && (katTerenu < katPoprzedni))
        {
            Vg = sqrt(Vx * Vx + Vy * Vy);
            Vx = -Vg * cos(kat * 3.1416 / 180 - fazaKol);
            Vy = Vg * sin(kat * 3.1416 / 180 - fazaKol);
        }
        if ((nVx < 0) && (katTerenu >= katPoprzedni))
        {
        }
        Vy += PRZYSPIESZENIE_GRAWITACYJNE * sin (katTerenu * 3.1416 / 180) * sin(katTerenu * 3.1416 / 180) * KROK_CZASOWY;
    }

    if((b2 == 1) || (b2 == 0))
    {
        y2 = BOHATER_PROMIEN2 + KROK_BOHATERA + poziomTerenu2;

        if ((nVx2 > 0) && (katTerenu <= katPoprzedni))
        {
        }
        if ((nVx2 > 0) && (katTerenu > katPoprzedni))
        {
            Vg2 = sqrt(Vx2 * Vx2 + Vy2 * Vy2);
            Vx2 = Vg2 * cos(katTerenu * 3.1416 / 180);
            Vy2 = -Vg2 * sin(katTerenu * 3.1416 / 180);
        }
        if ((nVx2 < 0) && (katTerenu < katPoprzedni))
        {
            Vg2 = sqrt(Vx2 * Vx2 + Vy2 * Vy2);
            Vx2 = -Vg2 * cos(katTerenu * 3.1416 / 180);
            Vy2 = Vg2 * sin(katTerenu * 3.1416 / 180);
        }
        if ((nVx2 < 0) && (katTerenu >= katPoprzedni))
        {
        }
        Vy2 += PRZYSPIESZENIE_GRAWITACYJNE * sin (katTerenu * 3.1416 / 180) * sin(katTerenu * 3.1416 / 180) * KROK_CZASOWY;
    }

    if (b1 == -1)
    {
        if (y - BOHATER_PROMIEN1 - KROK_BOHATERA - Vy * KROK_CZASOWY >= poziomTerenu1)
        {
            y -= Vy * KROK_CZASOWY;
            Vy += PRZYSPIESZENIE_GRAWITACYJNE * KROK_CZASOWY;
        }
        else
        {
            y = BOHATER_PROMIEN1 + KROK_BOHATERA + poziomTerenu1;
        }
    }

    if (b2 == -1)
    {
        if (y - BOHATER_PROMIEN2 - KROK_BOHATERA - Vy2 * KROK_CZASOWY >= poziomTerenu2)
        {
            y2 -= Vy2 * KROK_CZASOWY;
            Vy2 += PRZYSPIESZENIE_GRAWITACYJNE * KROK_CZASOWY;
        }
        else
        {
            y2 = BOHATER_PROMIEN2 + KROK_BOHATERA + poziomTerenu2;
        }
    }

    //zmiana Vx w wyniku dzialania grawitacji
    if (((b1 == 1) || (b1 == 0) || (b2 == 1) || (b2 == 0)))
    {
        Vx -= PRZYSPIESZENIE_GRAWITACYJNE * sin (katTerenu * 3.1416 / 180) * cos(katTerenu * 3.1416 / 180) * KROK_CZASOWY;
        Vx2 -=PRZYSPIESZENIE_GRAWITACYJNE * sin (katTerenu * 3.1416 / 180) * cos(katTerenu * 3.1416 / 180) * KROK_CZASOWY;
    }

    UstawKat();
    UstawXs();
    UstawYs();
    UstawX();
    UstawX2();
    katPoprzedni = katTerenu;
    if ((katTerenu <= 1) && (katTerenu >= -1) && (b1 != -1) && (b2 != -1))
    {
        Vy = 0;
        Vy2 = 0;
    }

    if (((b1 == 1) || (b1 == 0)) || ((b2 == 1) || (b2 == 0)) && ((katTerenu >= -3) && (katTerenu <= 3)))
    {
        //Vy = 0;
        //Vy2 = 0;
    }


    if (x < -920)
    {
        Teleportuj();
        y = yBaz+5;
    }
    if (x > 920)
    {
        x = 915;
        y = yBaz + 3;
        Vx = 0;
        Vy = 0;
        Vx2 = 0;
        Vy2 = 0;
        Vg = 0;
        Vg2 = 0;
        Vkatowa = 0;
        kat = 0;
        fazaKol = atan2(BOHATER_PROMIEN1 - BOHATER_PROMIEN2, BOHATER_POZYCJA_KOLA);
        x2 = x + BOHATER_POZYCJA_KOLA / cos(fazaKol) * cos((kat)*3.1415/180 - fazaKol);
        y2 = y + BOHATER_POZYCJA_KOLA / cos(fazaKol) * sin((kat)*3.1415/180 - fazaKol);
        UstawXs();
        UstawYs();
        katPoprzedni = 0;
    }

    energia = (Vx*Vx) / 25.0;
}


void cBohater1::Przyspieszaj(float dVx, float dVy)
{
    dVx *= sqrt(mocSilnika) / 125.0 + 0.2;

    int b1;
    int b2;
    int k = Plansza->XDoTab(x);
    if (k < 0)
        k = 0;
    float poziomTerenu1;
    if(Plansza->ZnajdzBelke(x, y) > Plansza->tabPol[k])
        poziomTerenu1 = Plansza->ZnajdzBelke(x, y);
    else
        poziomTerenu1 = Plansza->tabPol[k];
    if (y - BOHATER_PROMIEN1 - 5 * KROK_BOHATERA > poziomTerenu1)
    {
        b1 = -1;
    }
    else
    {
        if(y - BOHATER_PROMIEN1 - 5 * KROK_BOHATERA == poziomTerenu1)
        {
            b1 = 0;
        }
        else
        {
            b1 = 1;
        }
    }

    int k2 = Plansza->XDoTab(x2);
    if (k2 < 0)
        k2 = 0;
    float poziomTerenu2;
    if(Plansza->ZnajdzBelke(x2, y2) > Plansza->tabPol[k2])
        poziomTerenu2 = Plansza->ZnajdzBelke(x2, y2);
    else
        poziomTerenu2 = Plansza->tabPol[k2];
    if (y2 - BOHATER_PROMIEN2 - 5 * KROK_BOHATERA > poziomTerenu2)
    {
        b2 = -1;
    }
    else
    {
        if(y2 - BOHATER_PROMIEN2 - 5 * KROK_BOHATERA == poziomTerenu2)
        {
            b2 = 0;
        }
        else
        {
            b2 = 1;
        }
    }

    if ((b1 == 0) || (b1 == 1) || (b2 == 0) || (b2 == 1))
    {
        Vx += 10 * dVx * cos(katTerenu * 3.1416 / 180);
        Vx2 += 10 * dVx * cos(katTerenu * 3.1416 / 180);
    }
}

void cBohater1::ZmienKat(float dkat)
{
    kat += dkat;
    if (kat < -90) kat = 360 - kat;
    if (kat > 270) kat = -(360 - kat);
    UstawX2();
    //UstawY2();
}

void cBohater1::UstawX()
{
    x = xs - 0.5 * BOHATER_POZYCJA_KOLA / cos(fazaKol) * cos((kat)*3.1415/180 - fazaKol);
    y = ys - 0.5 * BOHATER_POZYCJA_KOLA / cos(fazaKol) * sin((kat)*3.1415/180 - fazaKol);
}

void cBohater1::UstawX2()
{
    x2 = xs + 0.5 * BOHATER_POZYCJA_KOLA / cos(fazaKol) * cos((kat)*3.1415/180 - fazaKol);
    y2 = ys + 0.5 * BOHATER_POZYCJA_KOLA / cos(fazaKol) * sin((kat)*3.1415/180 - fazaKol);
}

void cBohater1::UstawY2()
{
    y2 = y + BOHATER_POZYCJA_KOLA * sin((+kat)*3.1415/180 - fazaKol);
}

void cBohater1::Przesun(float dx, float dy)
{
    x += dx;
    x2 += dx;
    y += dy;
    y2 += dy;
}

void cBohater1::UstawXs()
{
    xs = 0.5 * (x + x2);
}

void cBohater1::UstawYs()
{
    ys = 0.5 * (y + y2);
}

void cBohater1::UstawKat()
{
    kat = (atan((y2 - y)/(x2 - x)) + fazaKol) * 180 / 3.1416;

    if (kat < -80)
        kat = -80;
    if (kat > 80)
        kat = 80;
    ys = 0.5 * (y + y2);
    y = ys;
    y2 = ys;
}





bool cBohater1::Atakuj()
{
    int nrKogo = ((wlasciciel == 1) ? 1 : 0); // ktorego gracza z tablicy stowrek ma atakowac
    cGracz* kogo =  Plansza->tabGraczy[nrKogo];



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
                        if (kogo->tabBohaterow[i]->poziomZycia < 0) this->doswiadczenie++;
                        if (doswiadczenie > 5)
                        {
                            doswiadczenie = 0;
                            this->Awansuj();
                        }
                        turDoAtaku = 1000.0/szybkoscAtaku;
                        return true;
                    }
                }
            }
        }
    }




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
            if (kogo->tabStworkow[nrDoAtakowania]->poziomZycia < 0) this->doswiadczenie++;
            if (doswiadczenie > 5)
            {
                doswiadczenie = 0;
                this->Awansuj();
            }

            turDoAtaku = 1000.0/szybkoscAtaku;
            return true;
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

void cBohater1::Awansuj()
{
    mnoznikZycia += 0.45;
	poziomZycia = 100;
	zasieg += 10;
    obrazenia += 3;
    szybkoscAtaku += 2;
    level++;
}
void cBohater1::ZwiekszMoc()
{

    mocSilnika = mocSilnika * 1.02 + 2;
}

void cBohater1::Teleportuj()
{
	x = xBaz;
    y = yBaz + 30;

    z = 0;
    Vx = 0;
    Vy = 0;
    Vx2 = 0;
    Vy2 = 0;
    Vg = 0;
    Vg2 = 0;
    Vkatowa = 0;
    kat = 0;
    fazaKol = atan2(BOHATER_PROMIEN1 - BOHATER_PROMIEN2, BOHATER_POZYCJA_KOLA);
    x2 = x + BOHATER_POZYCJA_KOLA / cos(fazaKol) * cos((kat)*3.1415/180 - fazaKol);
    y2 = y + BOHATER_POZYCJA_KOLA / cos(fazaKol) * sin((kat)*3.1415/180 - fazaKol);
    UstawXs();
    UstawYs();
    katPoprzedni = 0;
}

bool cBohater1::SprawdzZycie()
{
    if (poziomZycia < 0) return false;
    else return true;
}
