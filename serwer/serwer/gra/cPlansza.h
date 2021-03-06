#pragma once
#include "naglowki.h"
#include "cPunktStabilny.h"
#include "cGracz.h"
#include "cElement.h"
#include "cBelka.h"
#include "cTeownik.h"





class cPlansza
{
public:
	cPlansza(void);
	~cPlansza(void);

    void _Dzialaj(int value);
	void WczytajTeren();

	vector < cPunktStabilny* > tabPunktStab;
	vector < cGracz* > tabGraczy;
    vector < cElement* > tabElementow;
	float tabPol[50000];
	int tabTypowPol[50000];
    int nrTury;
    bool koniecGry = false;

	void DodajPunktStabilny(float _x, float _y);


	float TabDoX(int k);
	float TabDoY(int w);
	int XDoTab(float x);
	int YDoTab(float y);
    float Wysokosc(float x, float y);		// wysokosc poziomu mapy


    void DodajDodanie(char pierwszy, char drugi, char trzeci, char czwarty);
    void DodajDodanie(char pierwszy, char drugi, char trzeci);
    void DodajDodanie(char pierwszy, char drugi);
    void DodajDodanie(char pierwszy);
    char buforDodan[1024];
    int bajtyBuforuDodan;


    void UsunElement(float x, float y);
    void DodajElement(int belkaP, char belkaK, char wlascicel);
    float ZnajdzBelke(float x, float y);
    void CzyBelkaWytrzyma();
    void AnimacjaBelek();
};

