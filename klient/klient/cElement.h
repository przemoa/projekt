#pragma once
#include "naglowki.h"
class cElement
{
public:
	float grubosc;
	float x_poczatku;
	float y_poczatku;
	float x_konca;
	float y_konca;
	float z;
	float kolor_r;
	float kolor_g;
	float kolor_b;
public:
	cElement(void);
	~cElement(void);
	virtual void Rysuj() = 0;
};

