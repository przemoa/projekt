#pragma once

class cObiekt
{
protected:
	float x;
	float y;
	float z;

	float kat;


public:
	cObiekt();
	virtual void Rysuj() = 0;
	void Przesun(float dx, float dy, float dz);
	void UstawPozycje(float _x, float _y, float _z);
	void Obroc(float dkat);
	void UstawKat(float _kat);

	float GetX();
	float GetY();
	float GetZ();
	float GetKat();
};