#pragma once
#include "naglowki.h"
class cElement
{
protected:
	float wytrzymalosc;
	float grubosc;
	float dlugosc;
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
};

