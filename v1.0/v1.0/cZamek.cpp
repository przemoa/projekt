#include "cZamek.h"
#include "cPlansza.h"

cZamek::cZamek(void)
{
}


cZamek::~cZamek(void)
{
}



cZamek::cZamek(float _x, float _y)
{
	x = _x;
	y = _y;
	rozmiar = 25;
	rozmiarWiezy = rozmiar/4.2;
	zycie = 100;

	DodajWieze(11, 100);
	DodajWieze(12, 100);
	DodajWieze(13, 300);
	DodajWieze(14, 300);
	DodajWieze(15, 300);
	DodajWieze(13, 100);
	DodajWieze(14, 200);
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

	tabWiez.insert(tabWiez.begin(), nowaWieza);

}

void cZamek::Rysuj()
{	
	glColor4f(1, 1, 1, 1);
	glPushMatrix();
		glTranslatef(x, y, 0);

		float wysokosc = 3*rozmiarWiezy;
		
		for (int i = 0; i < tabWiez.size(); i++)
		{
			int kolumna = tabWiez[i].pozycja/100;
			int wiersz = tabWiez[i].pozycja%100 - 1;

			glBindTexture(GL_TEXTURE_2D, tabWiez[i].typWiezy);
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex2f((-7+3*kolumna)*rozmiarWiezy, 1.04*rozmiar + wiersz*wysokosc);
				glTexCoord2f(1.0f, 0.0f); glVertex2f( (-5+3*kolumna)*rozmiarWiezy, 1.04*rozmiar + wiersz*wysokosc);
				glTexCoord2f(1.0f, 1.0f); glVertex2f( (-5+3*kolumna)*rozmiarWiezy,  1.04*rozmiar + (wiersz+1.6)*wysokosc);
				glTexCoord2f(0.0f, 1.0f); glVertex2f((-7+3*kolumna)*rozmiarWiezy,  1.04*rozmiar + (wiersz+1.6)*wysokosc);
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

	Plansza->RysujPasekZycia(x, y - 6, rozmiar, zycie);


}