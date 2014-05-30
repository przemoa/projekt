#pragma once
#include "naglowki.h"

class cJednostka
{
protected:
	float x;
	float y;
	float z;

	float poziomZycia;
	float rozmiar;			// promien jednostki

	int wlasciciel;			// 1: gracz 1		-1: gracz 2
	sKOLOR kolor;
	int id;

public:
	cJednostka(void);
	~cJednostka(void);

	static int aktualneId;
	virtual void Rysuj() = 0;
	virtual bool CzyKliknieto(float px, float py) = 0;
	virtual void AktualizujRamke() = 0;
	virtual void RysujPasekZycia() = 0;
	virtual void Atakuj() = 0;
	int GetId();
};

