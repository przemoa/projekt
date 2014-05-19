#pragma once

#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <cmath>
#include "cObiekt.h"
#include "SOIL.h"


using namespace std;

void Dzialaj(int value);


#define ZAKRES_GRY_X 300
#define ZAKRES_GRY_Y 80
#define MNOZNIK_POL 5

#define TIMER_KAMERA_SCROLL 5
#define TIMER_KAMERA_PRZESUN_X 6
#define TIMER_KAMERA_MYSZ_PRZESUN_X 61
#define TIMER_KAMERA_MYSZ_PRZESUN_Y 62
#define TIMER_KAMERA_PRZESUN_Y 7
#define TIMER_ANIMACJI_TLA 8
#define TIMER_CO_DWASEKUNDOWY 9


#define SZYBKOSC_PRZESUWANIA 0.25
#define SZYBKOSC_SCROLLOWANIA 1.3

#define KAMERA_MAX_ZAKRES 500
#define KAMERA_MIN_ZAKRES 5
#define KAMERA_MAX_POLOZENIE_X 300
#define KAMERA_MAX_POLOZENIE_Y 100
#define KAMERA_MIN_POLOZENIE_Y -30
#define KAMERA_PRZESUWANIE_MYSZA 60

#define ILOSC_CHMUR 8
#define SZYBKOSC_CHMUR 120.0

#define ILOSC_PALM 8

#define TEKSTURA_CHMURA1 1
#define TEKSTURA_CHMURA2 2
#define TEKSTURA_PALMA1 3
#define TEKSTURA_TRAWA1 4

struct sKOLOR
{
	float r;
	float g;
	float b;
};