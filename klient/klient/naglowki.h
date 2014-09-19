#pragma once

#include <GL/freeglut.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <cmath>
#include "SOIL.h"
#include <vector>
#include <sstream>


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
#define TIMER_500 11
#define TIMER_100 12
#define TIMER_2 13
#define TIMER_BUDOWA_STWORKA 14

#define SZYBKOSC_PRZESUWANIA 0.25
#define SZYBKOSC_SCROLLOWANIA 1.3

#define KAMERA_MAX_ZAKRES 400
#define KAMERA_MIN_ZAKRES 1
#define KAMERA_MAX_POLOZENIE_X 975
#define KAMERA_MAX_POLOZENIE_Y 200
#define KAMERA_MIN_POLOZENIE_Y -100
#define KAMERA_PRZESUWANIE_MYSZA 60		// 20	

#define ILOSC_CHMUR 16
#define SZYBKOSC_CHMUR 120.0


#define TEKSTURA_CHMURA1 1
#define TEKSTURA_CHMURA2 2
#define TEKSTURA_PALMA1 3
#define TEKSTURA_TRAWA1 4
#define TEKSTURA_BOHATER 5
#define TEKSTURA_MAPA_TERENU 6
#define TEKSTURA_ZAMEK 7
#define TEKSTURA_MONETA 8

#define TEKSTURA_WIEZA1 11
#define TEKSTURA_WIEZA2 12
#define TEKSTURA_WIEZA3 13
#define TEKSTURA_WIEZA4 14
#define TEKSTURA_WIEZA5 15
#define TEKSTURA_WIEZA6 16
#define TEKSTURA_WIEZA7 17


#define TEKSTURA_MENU_ZAMEK 31
#define TEKSTURA_MENU_BOHATER 32
#define TEKSTURA_MENU_WIEZA 33
#define TEKSTURA_MENU_STWOREK 34
#define TEKSTURA_MENU_BUDOWA_STWORKA 35
#define TEKSTURA_MENU_BUDOWA_BOHATERA 37
#define TEKSTURA_MENU_BUDOWA_WIEZY 38
#define TEKSTURA_WYBOR_MIEJSCA 39


#define POLE_WODA 0xFC
#define POLE_GRACZ 0xF9
#define POLE_PALMA 0x18
#define POLE_PUNKT_STABILNY 0x67
#define POLE_TLO 0xFF
#define POLE_ZIEMIA 0x0A
#define POLE_TRAWA 0x71


#define POLE_SKRZYNKA_Z_NAGRODA_1 0x00
#define POLE_SKRZYNKA_Z_NAGRODA_2 0x00

#define ZAKRES_KLIKNIECIE 3.5   

#define LISTA_PUNKT_STABILNY 1
#define LISTA_STWOREK_KULA 124
#define LISTA_STWOREK_KWADRAT 125
#define LISTA_STWOREK_TROJKAT 126
#define LISTA_STWOREK_JAJO 127
#define LISTA_BOHATER1 2
#define LISTA_BOHATER2 3


#define ROZMIAR_PUNKTUSTABILNEGO 2
#define ROMIAR_STWORKA_KULA 3
#define ROZMIAR_STWORKA_KWADRAT 3
#define ROZMIAR_STWORKA_TROJKAT 3
#define ROZMIAR_STWORKA_JAJO 2

// bohater 1
#define BOHATER_PROMIEN1 1.5
#define BOHATER_PROMIEN2 1.2
#define BOHATER_POZYCJA_KOLA 6
#define KROK_BOHATERA 0.2
#define KROK_OBROTU_BOHATERA 0.1
#define KROK_PRZYSPIESZANIA_BOHATERA 0.5
#define KROK_CZASOWY 0.01
#define PRZYSPIESZENIE_GRAWITACYJNE 1000
#define WSP_TARCIA 0.2
#define SILA_OPORU 1

//bohater 2
#define BOHATER2_ROZMIAR 2.5
#define KROK_PRZYSPIESZANIA_BOHATERA2 0.5
#define PRZYSPIESZENIE_GRAWITACYJNE2 0.07
#define BOHATER2_ZAKRES_KLIKNIECIE 1.5




#define IKONA_ZAMEK 101
#define IKONA_WIEZA1 111
#define IKONA_WIEZA2 112
#define IKONA_WIEZA3 113
#define IKONA_WIEZA4 114
#define IKONA_WIEZA5 115
#define IKONA_WIEZA6 116
#define IKONA_WIEZA7 117
#define IKONA_BOHATER1 121
#define IKONA_BOHATER2 122

#define IKONA_STWOREK1 124
#define IKONA_STWOREK2 125
#define IKONA_STWOREK3 126
#define IKONA_STWOREK4 127

struct sKOLOR
{
	float r;
	float g;
	float b;
};

struct sROZMIAROKNA
{
	int x;			// szerokosc
	int y;			// wysokosc
	float proporcja;
};

struct sKAMERA
{
	float zakres;			// aktualny zakres patrzenia kamery
	float zakresCel;		// zakres ktory ma byc osiagniety

	float x;				// aktualne polozenie kamery
	float xCel;				// polozenie do ktorego dazy kamera

	float y;
	float yCel;

	int przesuwajx;			// czy przesuwac kamere z powodu bycia myszy na krawedzi
	int przesuwajy;
};

struct sMYSZ
{
	int x;		// aktualne wspolrzedne myszy
	int y;

};


enum eTYP
{
	ZAMEK = 1, BOHATER1 = 2, BOHATER2 = 3,  STWOREK = 4, WIEZA = 5
};



struct sRAMKAOPISU
{
	eTYP typ;			
	int ikona;		// nr tesktury

	int id;
	char tekstId[5];
	string nazwa;
	float poziomZycia;
	bool czyWidoczna;
	string opis;
	
	int rodzajMenu;		// nr tekstury bedacej menu
	char tekstPomocy[128];

};

enum eETAPGRY
{
	LACZENIE = 0, OCZEKIWANIE_NA_WARUNKI, OCZEKIWANIE_NA_ROZPOCZECIE, GRA, UTRACONO_POLACZENIE, TEST
};







extern bool dodawanieBelki;