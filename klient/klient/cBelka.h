#pragma once
#include "celement.h"
class cBelka :
	public cElement
{
public:
	bool animuj;

	cBelka(void);
	cBelka(float xp, float yp, float xk, float yk, bool _animuj);
	~cBelka(void);
	void Rysuj();
};