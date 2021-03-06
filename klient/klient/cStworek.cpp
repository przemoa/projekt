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
	kolor.r = (1+wlasciciel)/2;
	kolor.g = 0;
	kolor.b = (-1+wlasciciel)/(-2);
	
	level = levelStworkow;

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

void cStworek::Rysuj()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(kat, 0, 0, 1);
		glColor3f(kolor.r, kolor.g, kolor.b);  //todo
		glCallList(typStworka);

		RysujPasekZycia();

	glPopMatrix();

	
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
			<< "Level:    " << (int) level << endl
			<< "Obrazenia:   " << (int) obrazenia<< endl
			<< "Zasieg:    " << (int) zasieg << endl
			<< "Szybkosc ataku: " << szybkoscAtaku << endl
			<< "Predkosc:   " << predkosc ;
	Plansza->ramkaOpisu.opis = ssOpis.str();
	Plansza->ramkaOpisu.rodzajMenu = TEKSTURA_MENU_STWOREK;
}
