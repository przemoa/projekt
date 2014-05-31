#pragma once
#include "cJednostka.h"

class cBohater : public cJednostka
{
public:
	cBohater(void);
	cBohater(float _x, float _y, int _wlascicel);
	~cBohater(void);

	void Rysuj();
	bool CzyKliknieto(float px, float py);
	void AktualizujRamke();
	void RysujPasekZycia();
	void Atakuj();
	void Ruszaj();
	void ZmienKat(float dkat);

	void Przyspieszaj(float dVx, float dVy);
	
	float kat;
	float energia;
	int kierunek;			// 1 lub -1
	float mocSilnika;
	float Vy;
	float VyCel;
	bool odbity;			// czy odbil sie od ziemi

	float yCel;

};

