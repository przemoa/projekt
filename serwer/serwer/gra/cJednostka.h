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
    int turDoAtaku;

	float poziomZycia;	// od 0 do 100
	int level;
	int doswiadczenie;		// punkty za pokonanie przeciwnikow potrzebne do wzrostu levelu

	float mnoznikZycia;	// pomnozony przez poziom zycia daje aktualna liczbe HP
	float zasieg;			// zasieg strzalu
	float obrazenia;		// zadawane obrazenia
    int szybkoscAtaku;		// szybkosc z jaka atakuje		0.05*x=ilosc strzlow na sekunde




public:
	cJednostka(void);
	~cJednostka(void);

	static int aktualneId;
    virtual bool Atakuj() = 0;          // zwraca true jezeli jednostka atakuje
    virtual bool SprawdzZycie() = 0;

	int GetId()	{return id;}
	float GetX() {return x;}
	float GetY() {return y;}
};

