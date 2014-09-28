#pragma once
#include "celement.h"
class cBelka :
	public cElement
{
public:
	cBelka(void);
	cBelka(float xp, float yp, float xk, float yk);
	~cBelka(void);
	void Rysuj();
};