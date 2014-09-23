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

	mnoznikZycia = 15;
	wydobycie = 10;
	dodawanaWieza = 0;
}

void cZamek::DodajWieze(int _typWiezy, int pozycja)
{
	Plansza->DodajAkcje(0x16, _typWiezy, pozycja/100);
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

			if (tabWiez[i].pozycja == wybranaWiez && tabWiez[i].czyAtakuje && Plansza->tabGraczy[Plansza->wybranyGracz]->idWybrane == this->GetId())
			{																					 
				tabWiez[i].x = (-6+3*kolumna)*rozmiarWiezy;
				tabWiez[i].y = 1.04*rozmiar + (wiersz+1.3)*wysokoscWiezy;

				glPushMatrix();
					
					glColor3f(1, 0, 0);
					glLineWidth(3);
					glTranslatef(tabWiez[i].x, tabWiez[i].y, 0);
					glBegin(GL_LINE_LOOP);
						for (int j = 0; j < 133; j++)
						{
							glVertex2f(tabWiez[i].zasieg * sin(6.2832*j/133), tabWiez[i].zasieg * cos(6.2832*j/133));
						}
					glEnd();

				glPopMatrix();
				glColor4f(1, 1, 1, 1);
			}
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
			typWybranejWiezy = tabWiez[i].typWiezy;
			return true;
		}
	}

	if ((px > x - rozmiar) && (px < x + rozmiar) && (py > y) && (py < y + 1.24*rozmiar))
	{
		wybranaWiez = 0;
		Plansza->ramkaOpisu.rodzajMenu = TEKSTURA_MENU_ZAMEK;
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
		if (tabWiez[nrWiezy].czyAtakuje)
		{
			ssOpis	<< "Typ Wiezy:      " << (int) tabWiez[nrWiezy].typWiezy << endl
					<< "Pozycja:      " << (int) tabWiez[nrWiezy].pozycja << endl
					<< "Level:      " << (int) tabWiez[nrWiezy].level  << endl
					<< "Obrazenia:      " << (int) tabWiez[nrWiezy].obrazenia << endl
					<< "Zasieg:      " << (int) tabWiez[nrWiezy].zasieg << endl
					<< "Szybkosc ataku:   " << (int) tabWiez[nrWiezy].szybkoscAtaku << endl;

		}
		else if (tabWiez[nrWiezy].typWiezy == TEKSTURA_WIEZA6)
		{
			ssOpis	<< "Typ Wiezy:      " << (int) tabWiez[nrWiezy].typWiezy << endl
					<< "Pozycja:      " << (int) tabWiez[nrWiezy].pozycja << endl
					<< "Level:      " << (int) tabWiez[nrWiezy].level  << endl
					<< "Wydobycie zlota: " << (int) tabWiez[nrWiezy].obrazenia << endl;
		}
		else
		{
			ssOpis	<< "Typ Wiezy:      " << (int) tabWiez[nrWiezy].typWiezy << endl
					<< "Pozycja:      " << (int) tabWiez[nrWiezy].pozycja << endl
					<< "Level:      " << (int) tabWiez[nrWiezy].level  << endl
					<< "Szybkosc leczenia: " << (int) tabWiez[nrWiezy].obrazenia << endl;
		}


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
		
	}

}


void cZamek::Awansuj()
{
	Plansza->DodajAkcje(0x15);
}

void cZamek::AwansujWieze()
{
	for (int i = 0; i < tabWiez.size(); i++)
	{
		if (tabWiez[i].pozycja == wybranaWiez)
		{
			Plansza->DodajAkcje(0x1D, i);
		}
	}
}

int cZamek::SprzedajWieze()
{

	int maxPozycja = 0;
	int nrDoUsuniecia;
	for (int i = 0; i < tabWiez.size(); i++)
	{
		if (tabWiez[i].pozycja/100 == wybranaWiez/100  &&  maxPozycja < tabWiez[i].pozycja)
			maxPozycja = tabWiez[i].pozycja;

		if (tabWiez[i].pozycja == wybranaWiez)
		{
			nrDoUsuniecia = i;
		}
	}

	if (tabWiez[nrDoUsuniecia].pozycja == maxPozycja)
	{
		Plansza->DodajAkcje(0x1E, nrDoUsuniecia);
		wybranaWiez = 0;
		Plansza->ramkaOpisu.rodzajMenu = TEKSTURA_MENU_ZAMEK;
	}
	return 0;
}