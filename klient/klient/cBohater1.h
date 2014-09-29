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




	
};

