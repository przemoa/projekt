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
	void Awansuj();
	void ZwiekszMoc();
	void Teleportuj();

	float x2;			// wspolrzedne mniejszego kola
	float y2;
	float xs;
	float ys;
	float Vx;
	float Vy;
	float Vx2;
	float Vy2;
	float Vkatowa;
	float katTerenu;
	float Vg;
	float Vg2;
	float katPoprzedni;
	float fazaKol;		// kat miedzy kolami w poziomie

	float kat;

	void Opadaj();
	void ZmienKat(float dkat);
	void UstawX2();
	void UstawY2();
	void Przesun(float dx, float dy);
	void UstawX();
	void UstawXs();
	void UstawYs();
	void UstawKat();
};

