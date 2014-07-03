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
	zasieg = 250;
	obrazenia = 25;
	szybkoscAtaku = 15; 
}




void cBohater2::Ruszaj()
{
	if (abs(x) > 920)
	{

		x = kierunek * (919.9);
		kierunek *= -1;
		energia *= 0.05;
	}


	//cout << energia << endl;
	float poziomZiemi = Plansza->Wysokosc(x);

	yCel += VyCel;
	y += 0.1*(yCel - y);
	Vy += 0.1*(VyCel - Vy);
	

	if (energia != 0)
	{
		float dx = sqrt(energia)*kierunek / 20;				// zmiana x przy aktualnej energii
		float poziomZiemi2 = Plansza->Wysokosc(x+dx);		// poziom ziemi przy przesuniecu o dx

		
		if (y - 0.11 > poziomZiemi && y - 0.11 > poziomZiemi2) x += dx;			// jesli jest w powietrzu i za dx bêdzie w powietrzu to przeun o dx
		else
		{
			float dE = (poziomZiemi - poziomZiemi2) * 50;				// zmiana energii wynikajaca ze zmiany wysokosci
			if (dE > 0) dE *= 0.4;										// jezeli zjezdza z gorki to czesc energii przepada
			float energia2 = energia + dE;								
			
			if (energia2 > 0)											// jezeli pojazd ma wystarczajaca energii na podjechanie pod gore
			{
				x += dx;	
				yCel += poziomZiemi2 - poziomZiemi;
				energia = energia2;
			}
			else { energia = 0; kierunek = 0; }							// jesli nie ma wystarczajaca energii to traci aktualna
		}
	}

	

	if (odbity)
	{
		if (y - 10 > poziomZiemi)										// wysokosc powyzej ktorej musi sie wzbic aby ponownie odbic
			odbity = false;
	}
	else
	{
		if (y < poziomZiemi)						// nastepuje odbicie 
		{
			Vy = - Vy;
			VyCel = -VyCel;
			odbity = true;
		}
	}
	if (y - 0.05 > poziomZiemi)					// gdy jest troche nad ziemia dziala grawitacja
	{
		VyCel -= PRZYSPIESZENIE_GRAWITACYJNE2;
		if (VyCel > 0) VyCel -= 0.12;
	}
	if (odbity == true && Vy < 0 && y + 0.1 < poziomZiemi)				// gdy nie moze sie odbic a spadnie pod ziemie to ma wcrocic na powierzchnie
	{
		VyCel = 0;
		yCel = poziomZiemi;
	}

	if (energia == 0)							// gdy nachylenie duze a sie nie rusza to rozpoczyna sie staczanie
	{
		float poziomZiemi2 = Plansza->Wysokosc(x + 2);
		if (poziomZiemi2 - poziomZiemi > 1)							// w lewo
		{
			kierunek = -1;
			energia = 15;
		}

		poziomZiemi2 = Plansza->Wysokosc(x - 2);
		if (poziomZiemi2 - poziomZiemi > 1)						// i prawo
		{
			kierunek = 1;
			energia = 15;
		}
	}

	if (y + 0.1 < poziomZiemi) y = poziomZiemi;					// gdy znajdzie sie pod ziemia wraca na powierzchnie
	VyCel *= 0.99;											// tlumienie predkosci pionowej
	energia *= 0.998;										// tlumienie enrgii
	energia -= 0.3;
	if (energia < 0) { energia = 0; kierunek = 0; }			
}


void cBohater2::Przyspieszaj(float dVx, float dVy)
{
	float poziomZiemi = Plansza->Wysokosc(x);
	if (y - 4 > poziomZiemi) return;				// jesli wisi w powietrzu to nie mozna przyspieszac


	int zwrot = abs(dVx)/dVx;				// zwrot zadanego przyspieszenia

	if (energia < 5*mocSilnika*abs(dVx))			// gdy energia mala to przyspiesze od razu do pewnej wartosci
	{
		int tabX = Plansza->XDoTab(x);
		if (Plansza->tabPol[tabX + zwrot*60] -Plansza->tabPol[tabX] < 1.2)		// pod warunkiem ze nachylenie nie jest zbyt duze
		{
			energia = 6*mocSilnika*abs(dVx);
		}
		else return;

		if (kierunek == -zwrot)				// zahamuj do 0
		{
			kierunek = 0;
			energia = 0;
		}
		else	kierunek = zwrot;
	}

	else if (kierunek == zwrot)			// przyspieszaj w kierunku ruchu
	{
		energia *= 1.0005;
		energia += mocSilnika*abs(dVx);
	}
	else if (kierunek != zwrot)			// hamuj 
	{
		energia /= 1.05;
		energia -= mocSilnika*4*abs(dVx);
	}

	if (energia < 0) energia = 0;

	
	


}



void cBohater2::Atakuj()
{
}

void cBohater2::Awansuj()
{
	mnoznikZycia += 0.25;
	poziomZycia = 100;
	zasieg += 10;
	obrazenia += 2;
	szybkoscAtaku += 1; 
	level += 1;
}
void cBohater2::ZwiekszMoc()
{
    mocSilnika = mocSilnika *1.06 + 2;
}

void cBohater2::Teleportuj()
{
	x = xBaz;
	yCel = y = yBaz;
	energia = 0;
	kierunek = 0;
	Vy = VyCel = 0;
}
