#include "cStworek.h"
#include "cPlansza.h"

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
	kolor.r = 1;
	kolor.g = 0;
	kolor.b = 0;

	kat = 0;

	switch(_typStworka)
	{
	case LISTA_STWOREK_KULA:
		wysokosc = ROZMIAR_STWORKA_KULA;
		predkosc = 50;
		mnoznikZycia = 0.6;
		zasieg = 35;
		obrazenia = 12;
		szybkoscAtaku = 40;
		break;
	case LISTA_STWOREK_KWADRAT:
		wysokosc = 35;
		predkosc = 30;
		mnoznikZycia = 0.4;
		zasieg = 55;
		obrazenia = 15;
		szybkoscAtaku = 15; 
		break;
	case LISTA_STWOREK_TROJKAT:
		wysokosc = 1.5 * ROZMIAR_STWORKA_TROJKAT;
		predkosc = 100;
		mnoznikZycia = 0.8;
		zasieg = 55;
		obrazenia = 15;
		szybkoscAtaku = 65; 
		break;
	case LISTA_STWOREK_JAJO:
		wysokosc = 2 * ROZMIAR_STWORKA_TROJKAT;
		predkosc = 84;
		mnoznikZycia = 0.15;
		zasieg = 18;
		obrazenia = 15;
		szybkoscAtaku = 20; 
		break;
	}

	predkosc += predkosc*levelStworkow/5.0;
	mnoznikZycia += mnoznikZycia*levelStworkow/5.0;
	zasieg += zasieg*levelStworkow/5.0;
	obrazenia += obrazenia*levelStworkow/5.0;
	szybkoscAtaku += szybkoscAtaku*levelStworkow/5.0;

	y = Plansza->tabPol[Plansza->XDoTab(x)] + wysokosc;
	yCel = y;

}

cStworek::~cStworek(void)
{

}

void cStworek::Rysuj()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(kat, 0, 0, 1);
		glColor3f(kolor.r, kolor.g, kolor.b);  //todo
		//glCallList(typStworka);
		glCallList(LISTA_STWOREK_KULA);

		RysujPasekZycia();

	glPopMatrix();

	
}

void cStworek::Ruszaj()
{
	int xTab = Plansza->XDoTab(x);
	float dx = 0;

	if (typStworka == LISTA_STWOREK_KWADRAT)
	{
		dx = wlasciciel * predkosc;
	}
	else if (typStworka == LISTA_STWOREK_KULA)
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

void cStworek::RysujPasekZycia()
{

	glPushMatrix();

		glTranslatef(-rozmiar, rozmiar*1.7, 0);
		glColor3f(0.1,0.1,0.1);
		glBegin(GL_POLYGON);
			glVertex2f(0, -0.1*rozmiar);
			glVertex2f( rozmiar*2, -0.1*rozmiar);
			glVertex2f( rozmiar*2,  0.1*rozmiar);
			glVertex2f(0,  0.1*rozmiar);
		glEnd();
		
		glColor3f(1-poziomZycia/100, poziomZycia/100, 0.0);
		glBegin(GL_POLYGON);
			glVertex2f(0.05*rozmiar, -0.08*rozmiar);
			glVertex2f( rozmiar*1.95*poziomZycia/100, -0.08*rozmiar);
			glVertex2f( rozmiar*1.95*poziomZycia/100,  0.08*rozmiar);
			glVertex2f(0.05*rozmiar,  0.08*rozmiar);
		glEnd();


	glPopMatrix();
}

bool cStworek::CzyKliknieto(float px, float py)
{
	if ((px-x)*(px-x)+(py-y)*(py-y) < ZAKRES_KLIKNIECIE*rozmiar*rozmiar) return true;

	return false;
}
void cStworek::AktualizujRamke()
{
	Plansza->ramkaOpisu.id = id;
	Plansza->ramkaOpisu.typ = STWOREK;
	Plansza->ramkaOpisu.ikona = typStworka;
	Plansza->ramkaOpisu.poziomZycia = poziomZycia;

	stringstream ssNazwa;
	ssNazwa << "STWOREK " << (typStworka - 120);
	Plansza->ramkaOpisu.nazwa = ssNazwa.str();

	sprintf(Plansza->ramkaOpisu.tekstId, "%d", id);

	stringstream ssOpis;
	ssOpis	<< "Poziom zycia:  " << (int) mnoznikZycia * poziomZycia << endl
			<< "Level:    " << (int) level << " (" << doswiadczenie << "/5)" << endl
			<< "Obrazenia:   " << (int) obrazenia<< endl
			<< "Zasieg:    " << (int) zasieg << endl
			<< "Szybkosc ataku: " << szybkoscAtaku << endl
			<< "Predkosc:   " << predkosc ;
	Plansza->ramkaOpisu.opis = ssOpis.str();
	Plansza->ramkaOpisu.rodzajMenu = TEKSTURA_MENU_STWOREK;
}
void cStworek::Atakuj()
{
}
