#pragma once
#include "cbohater.h"
class cBohater1 :
	public cBohater
{
public:
	cBohater1(void);
	cBohater1(float _x, float _y, int _wlascicel);
	~cBohater1(void);

	void Rysuj();
	bool CzyKliknieto(float px, float py);
	void AktualizujRamke();
	void RysujPasekZycia();
	void Przyspieszaj(float dVx, float dVy);



	void Opadaj();
	void UstawX2();
	void UstawY2();
	void Przesun(float dx, float dy);
	void UstawX();
	void UstawXs();
	void UstawYs();
	void UstawKat();
};

