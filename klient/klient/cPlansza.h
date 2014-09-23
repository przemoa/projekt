#pragma once
#include "naglowki.h"
#include "cChmura.h"
#include "cPalma.h"
#include "cPunktStabilny.h"
#include "cGracz.h"
#include "cElement.h"
#include "cBelka.h"
#include "cTeownik.h"
#include "winsock2.h"
#ifdef WIN32
#pragma comment(lib,"ws2_32")
#endif



class cPlansza
{
public:
	cPlansza(void);
	~cPlansza(void);

	sROZMIAROKNA rozmiarOkna;
	sKAMERA kamera;
	sMYSZ mysz;
	sRAMKAOPISU ramkaOpisu;

	cChmura* tabChmur[ILOSC_CHMUR];
	vector < cPalma* > tabPalm;
	vector < cPunktStabilny* > tabPunktStab;
	vector < cElement* > tabElementow;
	vector < cGracz* > tabGraczy;
	bool wybranyGracz;
	bool czyFocusowac;		// czy ustawiac focus na wybrana jednostke
	bool moznaBudowac;
	eETAPGRY etapGry;
	bool wcisnieteA;
	bool wcisnieteD;
	float tabPol[50000];
	int tabTypowPol[50000];
	
	void _Przerysuj();
	void _ZmianaRozmiaruOkna(int width, int height);
	void _Dzialaj(int value);
	void _Idle();
	void _Klawiatura(unsigned char key, int x, int y);
	void _KlawiszPusc(unsigned char key, int x, int y);
	void _MyszKlawisz(int button, int state, int x, int y);
	void _MyszRuch(int x,int y);
	void _KlawiszeSpecjalne(int key, int x, int y);
	void OdswiezKamere();
	void PrzesunKamere(float dx, float dy);
	void AktualizujRamke();
	void FocusujKamere();
	void WczytajTeren();

	void UtworzListy();
	void TworzTekstury();
	void DodajPunktStabilny(float _x, float _y);
	void RysujPodloze();
	void RysujTloNiebo();
	void RysujTeren();
	void RysujRamkeOpisu();
	void DrawString(float x, float y, const unsigned char * string, float skala);
	int KliknieteMenu(int px, int py);
	void TekstPomocy();
	void WykonajAkcje(int menu);

	float TabDoX(int k);
	float TabDoY(int w);
	int XDoTab(float x);
	int YDoTab(float y);
	float Wysokosc(float x);		// wysokosc poziomu mapy
	void DodajElement(float x1, float x2, float y1, float y2);




	char daneDoWyslania[512];
	int bajtyDoWyslania;
	char daneOdebrane[8192];
	int bajtyOdebrane;
	SOCKET m_socket;//socket
	sockaddr_in clientService; // struktura zwiazana z serwerem - patrz connectToServer
	
	void DodajAkcje(char pierwszy, char drugi=0, char trzeci=0);
	bool PolaczZSerwerem();
	void OdbierzDane();
	void PrzetworzDane();
	void CzekajNaRozpoczenie();
	void WyslijDane();
	void DodajAkcjeDoWyslania();
};

