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
	mocSilnika = 6;


	UstawXs();
	UstawYs();

	masa = 10;


	energia = 0;
	mnoznikZycia = 11.5;
	poziomZycia = 100;
	zasieg = 70;
	obrazenia = 70;
	szybkoscAtaku = 12; 
}

void cBohater1::Rysuj()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		RysujPasekZycia();
		glRotatef(kat, 0, 0, 1);
		glColor3f(1,0,0);  //todo
		glCallList(LISTA_BOHATER1);
	glPopMatrix();

}

void cBohater1::Opadaj()
{
	//Vy += KROK_CZASOWY * PRZYSPIESZENIE_GRAWITACYJNE;
	//Vy2 += KROK_CZASOWY * PRZYSPIESZENIE_GRAWITACYJNE;
}

void cBohater1::Przyspieszaj(float dVx, float dVy)
{

}


void cBohater1::UstawX()
{

}

void cBohater1::UstawX2()
{

}

void cBohater1::UstawY2()
{

}

void cBohater1::Przesun(float dx, float dy)
{

}

void cBohater1::UstawXs()
{

}

void cBohater1::UstawYs()
{

}

void cBohater1::UstawKat()
{

}

void cBohater1::RysujPasekZycia()
{
	glPushMatrix();
		glTranslatef(-3*rozmiar, 6*rozmiar, 0);
		poziomZycia  = 50;
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
			<< "Rozmiar:      " << (int) rozmiar << endl
			<< "Obrazenia:   " << (int) obrazenia << endl
			<< "Zasieg:    " << (int) zasieg << endl
			<< "Moc Silnika:    " << (int) mocSilnika << endl
			<< "Vx:   " << 0 ;
	Plansza->ramkaOpisu.opis = ssOpis.str();
	Plansza->ramkaOpisu.rodzajMenu = 0;
}


