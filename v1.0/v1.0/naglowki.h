#pragma once

#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <cmath>
#include "cObiekt.h"
#include "SOIL.h"
#include <vector>

using namespace std;

void Dzialaj(int value);

class cPlansza;
extern cPlansza* Plansza;

#define TIMER_KAMERA_SCROLL 5
#define TIMER_KAMERA_PRZESUN_X 6
#define TIMER_KAMERA_MYSZ_PRZESUN_X 61
#define TIMER_KAMERA_MYSZ_PRZESUN_Y 62
#define TIMER_KAMERA_PRZESUN_Y 7
#define TIMER_ANIMACJI_TLA 8
#define TIMER_CO_DWASEKUNDOWY 9
#define TIMER_20 10

#define SZYBKOSC_PRZESUWANIA 0.25
#define SZYBKOSC_SCROLLOWANIA 1.3

#define KAMERA_MAX_ZAKRES 500
#define KAMERA_MIN_ZAKRES 1
#define KAMERA_MAX_POLOZENIE_X 300
#define KAMERA_MAX_POLOZENIE_Y 100
#define KAMERA_MIN_POLOZENIE_Y -200
#define KAMERA_PRZESUWANIE_MYSZA 60

#define ILOSC_CHMUR 11
#define SZYBKOSC_CHMUR 120.0


#define TEKSTURA_CHMURA1 1
#define TEKSTURA_CHMURA2 2
#define TEKSTURA_PALMA1 3
#define TEKSTURA_TRAWA1 4
#define TEKSTURA_BOHATER 5

#define POLE_WODA 0xFC
#define POLE_GRACZ 0xF9
#define POLE_PALMA 0x18
#define POLE_PUNKT_STABILNY 0x67
#define POLE_TLO 0xFF

#define POLE_SKRZYNKA_Z_NAGRODA_1 0x00
#define POLE_SKRZYNKA_Z_NAGRODA_2 0x00

   

#define LISTA_PUNKT_STABILNY 1
#define LISTA_BOHATER 2


#define ROZMIAR_PUNKTUSTABILNEGO 1
#define BOHATER_PROMIEN1 1.5
#define BOHATER_PROMIEN2 1.2
#define BOHATER_POZYCJA_KOLA 6
#define KROK_BOHATERA 0.2
#define KROK_OBROTU_BOHATERA 0.1


struct sKOLOR
{
	float r;
	float g;
	float b;
};