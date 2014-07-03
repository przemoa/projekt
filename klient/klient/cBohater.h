#pragma once
#include "cJednostka.h"

class cBohater : public cJednostka
{
public:
	cBohater(void);
	~cBohater(void);

	virtual void Rysuj() = 0;
	virtual bool CzyKliknieto(float px, float py) = 0;
	virtual void AktualizujRamke() = 0;
	virtual void RysujPasekZycia() = 0;

	void Awansuj();
	void ZwiekszMoc();
	void Teleportuj();

	virtual void Przyspieszaj(float dVx, float dVy) = 0;
	int kierunek;			// aktualny kierunek ruchu 1 lub -1
	float mocSilnika;		// moc silnika

	float xBaz;
	float yBaz;
	bool zywy;
	float energia;
};

