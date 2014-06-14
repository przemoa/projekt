#include "cZamek.h"
#include "cPlansza.h"

cZamek::cZamek(void)
{
}


cZamek::~cZamek(void)
{
}



cZamek::cZamek(float _x, float _y, int _wlasciciel)
{
	x = _x;
	y = _y;
	rozmiar = 25;
	rozmiarWiezy = rozmiar/4.2;
	wysokoscWiezy = 3*rozmiarWiezy;

	poziomZycia = 100;

	wlasciciel = _wlasciciel;

	DodajWieze(11, 100);
	DodajWieze(12, 100);
	DodajWieze(13, 300);
	DodajWieze(14, 300);
	DodajWieze(15, 300);
	DodajWieze(13, 100);
	DodajWieze(14, 200);


	mnoznikZycia = 15;
	wydobycie = 10;

}

void cZamek::DodajWieze(int _typWiezy, int pozycja)
{

	sWIEZA nowaWieza;
	for (int i = 0; i < tabWiez.size(); i++)
	{
		if (pozycja/100 == tabWiez[i].pozycja/100)
		{
			if (pozycja < tabWiez[i].pozycja) pozycja = tabWiez[i].pozycja;
		}
	}
	pozycja++;

	nowaWieza.pozycja = pozycja;
	nowaWieza.typWiezy = _typWiezy;
	nowaWieza.level = 1;

	switch (_typWiezy)
	{
	case TEKSTURA_WIEZA1:		// luk, srednioszybka, male obrazenia, sredni zasieg
		nowaWieza.obrazenia = 15;
		nowaWieza.zasieg = 150;
		nowaWieza.szybkoscAtaku = 35;
		break;
	case TEKSTURA_WIEZA2:		// kamien, malas szybkosc, srednie obrazenia, maly zasieg
		nowaWieza.obrazenia = 25;
		nowaWieza.zasieg = 100;
		nowaWieza.szybkoscAtaku = 20;
		break;
	case TEKSTURA_WIEZA3:		// pocisk, srednia szybkosc, srednie obrazenia, sredni zasieg
		nowaWieza.obrazenia = 35;
		nowaWieza.zasieg = 250;
		nowaWieza.szybkoscAtaku = 35;
		break;
	case TEKSTURA_WIEZA4:		// laser, malas szybkosc, duze obrazenia, duzy zasieg
		nowaWieza.obrazenia = 95;
		nowaWieza.zasieg = 350;
		nowaWieza.szybkoscAtaku = 10;
		break;
	case TEKSTURA_WIEZA5:		// ogien, mala szybkosc, duze obrazenia, maly zasieg
		nowaWieza.obrazenia = 40;
		nowaWieza.zasieg = 80;
		nowaWieza.szybkoscAtaku = 20;
		break;
	}

	tabWiez.insert(tabWiez.begin(), nowaWieza);

}

void cZamek::Rysuj()
{	
	glColor4f(1, 1, 1, 1);
	glPushMatrix();
		glTranslatef(x, y, 0);

		
		
		for (int i = 0; i < tabWiez.size(); i++)
		{
			int kolumna = tabWiez[i].pozycja/100;
			int wiersz = tabWiez[i].pozycja%100 - 1;

			glBindTexture(GL_TEXTURE_2D, tabWiez[i].typWiezy);
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex2f((-7+3*kolumna)*rozmiarWiezy, 1.04*rozmiar + wiersz*wysokoscWiezy);
				glTexCoord2f(1.0f, 0.0f); glVertex2f( (-5+3*kolumna)*rozmiarWiezy, 1.04*rozmiar + wiersz*wysokoscWiezy);
				glTexCoord2f(1.0f, 1.0f); glVertex2f( (-5+3*kolumna)*rozmiarWiezy,  1.04*rozmiar + (wiersz+1.6)*wysokoscWiezy);
				glTexCoord2f(0.0f, 1.0f); glVertex2f((-7+3*kolumna)*rozmiarWiezy,  1.04*rozmiar + (wiersz+1.6)*wysokoscWiezy);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}


		glBindTexture(GL_TEXTURE_2D, TEKSTURA_ZAMEK);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(-rozmiar, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex2f( rozmiar, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex2f( rozmiar,  1.24*rozmiar);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(-rozmiar,  1.24*rozmiar);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	RysujPasekZycia();
}

void cZamek::RysujPasekZycia()
{
	glPushMatrix();
		glTranslatef(x - rozmiar, y-rozmiar/3, 0);
		glColor3f(0.15, 0.15, 0.15);
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

bool cZamek::CzyKliknieto(float px, float py)
{
	int kolumna = 0;
	int wiersz = 0;
	if (abs(x-3*rozmiarWiezy-px) < rozmiarWiezy) kolumna = 1;
	if (abs(x-px) < rozmiarWiezy) kolumna = 2;
	if (abs(x+3*rozmiarWiezy-px) < rozmiarWiezy) kolumna = 3;
	wiersz = (py-y-1.04*rozmiar)/wysokoscWiezy + 1;
	if (wiersz < 0 || wiersz > 99) wiersz = 0;

	int kliknietaWieza = kolumna * 100 + wiersz;


	for (int i = 0; i < tabWiez.size(); i++)
	{
		if (tabWiez[i].pozycja == kliknietaWieza)
		{
			wybranaWiez = kliknietaWieza;
			return true;
		}
	}

	if ((px > x - rozmiar) && (px < x + rozmiar) && (py > y) && (py < y + 1.24*rozmiar))
	{
		wybranaWiez = 0;
		return true;
	}
	return false;
}

void cZamek::AktualizujRamke()
{
	bool sprawdzWieze = false;
	int nrWiezy = 0;
	for (int i = 0; i < tabWiez.size(); i++)
	{
		if (tabWiez[i].pozycja == wybranaWiez)
		{
			sprawdzWieze = true;
			nrWiezy = i;
		}
	}

	wybranaWiez *= sprawdzWieze;

	if (wybranaWiez)
	{
		Plansza->ramkaOpisu.id = id;
		Plansza->ramkaOpisu.typ = WIEZA;
		Plansza->ramkaOpisu.ikona = tabWiez[nrWiezy].typWiezy + 100;	// nr tekstury + 100 daje nr ikony wiezy
		Plansza->ramkaOpisu.poziomZycia = poziomZycia;

		sprintf(Plansza->ramkaOpisu.tekstId, "%d", id);

		stringstream ssNazwa;
		ssNazwa << "Wieza zamku";
		Plansza->ramkaOpisu.nazwa = ssNazwa.str();

		stringstream ssOpis;
		ssOpis	<< "Typ Wiezy:      " << (int) tabWiez[nrWiezy].typWiezy << endl
				<< "Pozycja:      " << (int) tabWiez[nrWiezy].pozycja << endl
				<< "Level:      " << (int) tabWiez[nrWiezy].level  << endl
				<< "Obrazenia:      " << (int) tabWiez[nrWiezy].obrazenia << endl
				<< "Zasieg:      " << (int) tabWiez[nrWiezy].zasieg << endl
				<< "Szybkosc ataku:   " << (int) tabWiez[nrWiezy].szybkoscAtaku << endl;
				

		Plansza->ramkaOpisu.opis = ssOpis.str();
		Plansza->ramkaOpisu.rodzajMenu = TEKSTURA_MENU_WIEZA;
	}


	else
	{
		Plansza->ramkaOpisu.id = id;
		Plansza->ramkaOpisu.typ = ZAMEK;
		Plansza->ramkaOpisu.ikona = IKONA_ZAMEK;
		Plansza->ramkaOpisu.poziomZycia = poziomZycia;

		stringstream ssNazwa;
		ssNazwa << "ZAMEK";
		Plansza->ramkaOpisu.nazwa = ssNazwa.str();
		
		sprintf(Plansza->ramkaOpisu.tekstId, "%d", id);

		stringstream ssOpis;
		ssOpis	<< "To jest Zamek, strzez go!" << endl
				<< "Poziom zycia:  " << (int) poziomZycia*mnoznikZycia << endl
				<< "Level:    " << (int) level << " (" << doswiadczenie << "/25)" << endl
				<< "Wdobycie zlota: " << (int) wydobycie << endl
				<< "Ilosc wiez: " << tabWiez.size();

		Plansza->ramkaOpisu.opis = ssOpis.str();
		Plansza->ramkaOpisu.rodzajMenu = TEKSTURA_MENU_ZAMEK;
	}

}

void cZamek::Atakuj()
{
}