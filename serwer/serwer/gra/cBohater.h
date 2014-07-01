#pragma once
#include "cJednostka.h"

class cBohater : public cJednostka
{
public:
	cBohater(void);
	~cBohater(void);


	virtual void Atakuj() = 0;
	virtual void Ruszaj() = 0;
	virtual void Awansuj() = 0;
	virtual void ZwiekszMoc() = 0;
	virtual void Teleportuj() = 0;

	virtual void Przyspieszaj(float dVx, float dVy) = 0;
	int kierunek;			// aktualny kierunek ruchu 1 lub -1
	float mocSilnika;		// moc silnika

	float xBaz;
	float yBaz;

};

