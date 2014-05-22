#pragma once
#include "cBohater.h"
#include "naglowki.h"

class cGracz
{
public:
	cGracz(void);
	~cGracz(void);
	cGracz(float _x, float _y);
	
	float x;
	float y;

	vector < cBohater* > tabBohaterow;

	void Dzialaj();			// wywolywana timerem co 20ms
	void DodajBohatera(float _x, float _y);
	void RuszajBohatera(float dVx, float dVy);
	void Rysuj();

	int wybranyBohater;







};

