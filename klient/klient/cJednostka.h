#pragma once
#include "naglowki.h"

class cJednostka
{
public:
	float x;
	float y;
	float z;

	float rozmiar;			// promien jednostki
	int wlasciciel;			// 1: gracz 1		-1: gracz 2
	int id;


	float poziomZycia;	// od 0 do 100
	int level;
	int doswiadczenie;		// punkty za pokonanie przeciwnikow potrzebne do wzrostu levelu

	float mnoznikZycia;	// pomnozony przez poziom zycia daje aktualna liczbe HP
	float zasieg;			// zasieg strzalu
	float obrazenia;		// zadawane obrazenia
	int szybkoscAtaku;		// szybkosc z jaka atakuje		0.05*x=ilosc strzlow na sekunde

	sKOLOR kolor;



public:
	cJednostka(void);
	~cJednostka(void);

	static int aktualneId;
	virtual void Rysuj() = 0;
	virtual bool CzyKliknieto(float px, float py) = 0;
	virtual void AktualizujRamke() = 0;
	virtual void RysujPasekZycia() = 0;
	int GetId()	{return id;}
	float GetX() {return x;}
	float GetY() {return y;}
};

