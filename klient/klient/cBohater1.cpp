#include "cBohater1.h"
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
	y = BOHATER_PROMIEN1 + 60;
	z = 0;

	rozmiar = 2;
	kat = 0;
	mocSilnika = 4;



	masa = 10;


	energia = 0;
	mnoznikZycia = 11.5;
	poziomZycia = 100;
	zasieg = 90;
	obrazenia = 70;
	szybkoscAtaku = 12; 
}

void cBohater1::Rysuj()
{
	if (!zywy) return;

	glPushMatrix();
		glTranslatef(x, y, z);
		RysujPasekZycia();
		glRotatef(kat, 0, 0, 1);
		glColor3f(1,0,0);  //todo
		glCallList(LISTA_BOHATER1);
	glPopMatrix();

}


void cBohater1::RysujPasekZycia()
{
	glPushMatrix();
		glTranslatef(-3*rozmiar, 6*rozmiar, 0);
		glColor3f(0.1,0.1,0.1);
		glBegin(GL_POLYGON);
			glVertex2f(0, -0.4*rozmiar);
			glVertex2f( rozmiar*8, -0.4*rozmiar);
			glVertex2f( rozmiar*8,  0.4*rozmiar);
			glVertex2f(0,  0.4*rozmiar);
		glEnd();

		glColor3f(1-poziomZycia/100, poziomZycia/100, 0.0);
		glBegin(GL_POLYGON);
			glVertex2f(0.2*rozmiar, -0.32*rozmiar);
			glVertex2f( rozmiar*4*1.95*poziomZycia/100, -0.32*rozmiar);
			glVertex2f( rozmiar*4*1.95*poziomZycia/100,  0.32*rozmiar);
			glVertex2f(0.2*rozmiar,  0.32*rozmiar);
		glEnd();
	glPopMatrix();
}


bool cBohater1::CzyKliknieto(float px, float py)
{
	if ((px-x)*(px-x)+(py-y)*(py-y) < ZAKRES_KLIKNIECIE*rozmiar*rozmiar) return true;
	return false;
}
void cBohater1::AktualizujRamke()
{
	Plansza->ramkaOpisu.id = id;
	Plansza->ramkaOpisu.typ = BOHATER1;
	Plansza->ramkaOpisu.ikona = IKONA_BOHATER1;
	Plansza->ramkaOpisu.poziomZycia = poziomZycia;

	stringstream ssNazwa;
	ssNazwa << "BOHATER 1 " << "  (id " << id << ")";
	Plansza->ramkaOpisu.nazwa = ssNazwa.str();

	stringstream ssOpis;
	ssOpis	<< "Poziom zycia:  " << (int) poziomZycia << endl
			<< "Level:    " << (int) level << " (" << doswiadczenie << "/5)" << endl
			<< "Obrazenia:   " << (int) obrazenia << endl
			<< "Zasieg:    " << (int) zasieg << endl
			<< "Szybkosc ataku: " << szybkoscAtaku << endl
			<< "Moc Silnika:    " << (int) mocSilnika << endl
			<< "Energia:   " << energia ;
	Plansza->ramkaOpisu.opis = ssOpis.str();
	Plansza->ramkaOpisu.rodzajMenu = TEKSTURA_MENU_BOHATER;

	if (poziomZycia < 0) Plansza->ramkaOpisu.czyWidoczna = false;
}


