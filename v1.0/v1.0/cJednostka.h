#pragma once
#include "naglowki.h"

class cJednostka
{
protected:
	float x;
	float y;
	float z;

	float poziomZycia;	// od 0 do 100
	float mnoznikZycia;	// pomnozony przez poziom zycia daje aktualna liczbe HP
	float rozmiar;			// promien jednostki

	int wlasciciel;			// 1: gracz 1		-1: gracz 2
	sKOLOR kolor;

	int id;
	int level;
	int doswiadczenie;		// punkty za pokonanie przeciwnikow potrzebne do wzrostu levelu

public:
	cJednostka(void);
	~cJednostka(void);

	static int aktualneId;
	virtual void Rysuj() = 0;
	virtual bool CzyKliknieto(float px, float py) = 0;
	virtual void AktualizujRamke() = 0;
	virtual void RysujPasekZycia() = 0;
	virtual void Atakuj() = 0;
	int GetId()	{return id;}
	float GetX() {return x;}
	float GetY() {return y;}
};

