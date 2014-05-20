#pragma once
#include "naglowki.h"


class cIstota
{
protected:
	float x;
	float y;
	float z;
	float kat;

public:
	cIstota(void);
	~cIstota(void);
	virtual void cRysuj() = 0;
	virtual bool CzyKliknieto(float px, float py) = 0;
};

