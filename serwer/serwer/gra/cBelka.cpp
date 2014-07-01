#include "cBelka.h"


cBelka::cBelka(void)
{
}

cBelka::cBelka(float xp, float yp, float xk, float yk, float wytrzymalosc)
{
	x_poczatku = xp;
	x_konca = xk;
	y_poczatku = yp;
	y_konca = yk;
	this->wytrzymalosc = wytrzymalosc;
	kolor_r = 0.6;
	kolor_g = 0.3;
	kolor_b = 0;
	z = 0;
}

cBelka::~cBelka(void)
{
}




