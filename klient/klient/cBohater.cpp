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
	Plansza->DodajAkcje(0x0B, (char) (Plansza->tabGraczy[Plansza->wybranyGracz]->wybranyBohater));
	
}
void cBohater::ZwiekszMoc()
{
	char drugiBajt = Plansza->tabGraczy[Plansza->wybranyGracz]->wybranyBohater;
	Plansza->DodajAkcje(0x0C, drugiBajt);
}
void cBohater::Teleportuj()
{
	Plansza->DodajAkcje(0x0D, (char) (Plansza->tabGraczy[Plansza->wybranyGracz]->wybranyBohater));
}


