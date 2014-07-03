#include "cBohater.h"
#include "naglowki.h"
#include "cPlansza.h"			// co z tym?  // se jest


cBohater::cBohater(void)
{
	zywy = true;
	energia = 0;
}


cBohater::~cBohater(void)
{
}

void cBohater::Awansuj()
{
	Plansza->DodajAkcje(0x0B, (char) (Plansza->tabGraczy[0]->wybranyBohater));
	
}
void cBohater::ZwiekszMoc()
{
	Plansza->DodajAkcje(0x0C, (char) (Plansza->tabGraczy[0]->wybranyBohater));
}
void cBohater::Teleportuj()
{
	Plansza->DodajAkcje(0x0D, (char) (Plansza->tabGraczy[0]->wybranyBohater));
}


