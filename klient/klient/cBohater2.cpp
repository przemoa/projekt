#include "cBohater2.h"
#include "naglowki.h"
#include "cPlansza.h"	

cBohater2::cBohater2(void)
{
}


cBohater2::~cBohater2(void)
{
}

cBohater2::cBohater2(float _x, float _y, int _wlascicel)
{
	wlasciciel = _wlascicel;
	xBaz = x = _x;
	yBaz = y = _y;
	z = 0;
	Vy = 0;
	yCel = y;
	VyCel = Vy;
	odbity = false;


	mocSilnika = 5;
	energia = 0;
	kierunek = 1;
	rozmiar = 2;

	mnoznikZycia = 5.5;
	poziomZycia = 100;
	zasieg = 120;
	obrazenia = 25;
	szybkoscAtaku = 15; 
}


void cBohater2::Rysuj()
{
	if (!zywy) return;
	glPushMatrix();
		glTranslatef(x, y, z);
		RysujPasekZycia();
		glCallList(LISTA_BOHATER2);
	glPopMatrix();
}




void cBohater2::RysujPasekZycia()
{
	glPushMatrix();
		glTranslatef(-4*rozmiar, 8*rozmiar, 0);
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


bool cBohater2::CzyKliknieto(float px, float py)
{
	//if ((px-x)*(px-x)+(py-y)*(py-y) < ZAKRES_KLIKNIECIE*rozmiar*rozmiar) return true;
	if (abs(x-px) < BOHATER2_ZAKRES_KLIKNIECIE*BOHATER2_ROZMIAR &&
		abs(y+2.5*BOHATER2_ROZMIAR-py) < BOHATER2_ZAKRES_KLIKNIECIE*2.5*BOHATER2_ROZMIAR) return true;

	return false;
}
void cBohater2::AktualizujRamke()
{



	Plansza->ramkaOpisu.id = id;
	Plansza->ramkaOpisu.typ = BOHATER2;
	Plansza->ramkaOpisu.ikona = IKONA_BOHATER2;
	Plansza->ramkaOpisu.poziomZycia = poziomZycia;

	stringstream ssNazwa;
	ssNazwa << "BOHATER 2";
	Plansza->ramkaOpisu.nazwa = ssNazwa.str();

	sprintf(Plansza->ramkaOpisu.tekstId, "%d", id);

	stringstream ssOpis;
	ssOpis	<< "Poziom zycia:  " << (int) (mnoznikZycia*poziomZycia) << endl
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

