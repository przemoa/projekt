#pragma once
#include "cbohater.h"
class cBohater2 :
	public cBohater
{
public:
	cBohater2(void);
	cBohater2(float _x, float _y, int _wlascicel);
	~cBohater2(void);

	float Vy;
	float VyCel;
	bool odbity;			// czy odbil sie od ziemi
	float yCel;


	void Rysuj();
	bool CzyKliknieto(float px, float py);
	void AktualizujRamke();
	void RysujPasekZycia();




};

