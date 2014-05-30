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
	




	float x2;			// wspolrzedne mniejszego kola
	float y2;			
	float Vx;
	float Vy;
	float Vkatowa;
	
	float fazaKol;		// kat miedzy kolami w poziomie
	float kat;
	void Przyspieszaj(float dVx, float dVy);
	
	void Ruszaj(float dx);
	void Opadaj();
	void ZmienKat(float dkat);
	void UstawX2();
	void UstawY2();
	void Przesun(float dx, float dy);
};

