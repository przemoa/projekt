#pragma once
#include "cJednostka.h"
#include "naglowki.h"

class cStworek : public cJednostka
{
public:
	cStworek(void);
	cStworek(float _x, float _z, int _typStworka, int _wlasciciel, int levelStworkow);
	~cStworek(void);


    bool Atakuj();
	void Ruszaj();
    bool SprawdzZycie();

	float kat;

	float yCel;

	float wysokosc;			// wysokosc nad poziomem powierzchni
	int typStworka;			// 
	float predkosc;			// predkosc ruchu stworka

};

