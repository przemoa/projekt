#include "cPlansza.h"
#include "naglowki.h"



cPlansza::cPlansza(void)
{
	moznaBudowac = true;
	testowy = 0;
	testowy2 = 0;
	//licznikPunktow = 0;

	rozmiarOkna.x = 1000;
	rozmiarOkna.y = 600;
	rozmiarOkna.proporcja = (float) rozmiarOkna.x / rozmiarOkna.y;

	kamera.x = 900;
	kamera.xCel = -900;
	kamera.y = 110;
	kamera.yCel = 110;
	kamera.zakres = 200;
	kamera.zakresCel = 55;
	kamera.przesuwajx = 0;
	kamera.przesuwajy = 0;

	glutTimerFunc(20, Dzialaj, TIMER_KAMERA_PRZESUN_X);
	glutTimerFunc(20, Dzialaj, TIMER_KAMERA_PRZESUN_Y);
	glutTimerFunc(20, Dzialaj, TIMER_KAMERA_SCROLL);
	glutTimerFunc(500, Dzialaj, TIMER_500);
	glutTimerFunc(100, Dzialaj, TIMER_100);

	ramkaOpisu.czyWidoczna = false;
	wybranyGracz = 0;
	czyFocusowac = 1;

	TworzTekstury();
	UtworzListy();

	for (int i = 0; i < ILOSC_CHMUR; i++)
	{

		tabChmur[i] = new cChmura(((rand()%2) ? TEKSTURA_CHMURA1 : TEKSTURA_CHMURA2), 
									-1600 + (3200.0 / ILOSC_CHMUR) * i + rand()%50, 140+rand()%50,
									14+rand()%8, rand()%2*180-7+rand()%14, 15+rand()%25);
	}

	// wczytaj plansze
	for (int k = 0; k < 50000; k+=10)
	{
		tabPol[k] = -7777;
		tabTypowPol[k] = -7777;
	}
	WczytajTeren();

	mysz.x = 1;
	mysz.y = 2;

	etapGry = LACZENIE;
	bajtyOdebrane = -1;
	bajtyDoWyslania = 1;
	daneDoWyslania[0] = 0x01;
	PolaczZSerwerem();

	wcisnieteA = 0;
	wcisnieteD = 0;
}

cPlansza::~cPlansza(void)
{

}

void cPlansza::_Dzialaj(int value)
{
	// Plynne przewijanie kamery
	if (value == TIMER_KAMERA_SCROLL)
	{
		if (abs(kamera.zakres - kamera.zakresCel) > kamera.zakresCel / 150)
		{
			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_SCROLL);
			kamera.zakres += (kamera.zakresCel - kamera.zakres) / 35.0;
			OdswiezKamere();
		}
		else
		{
			kamera.zakres = kamera.zakresCel;
		}
	}

	if (value == TIMER_KAMERA_PRZESUN_X)
	{
		if (abs(kamera.x - kamera.xCel) > kamera.zakres/350.0)
		{
			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_PRZESUN_X);
			kamera.x += (kamera.xCel - kamera.x) / 35.0;
			OdswiezKamere();
		}
		else
		{
			kamera.x = kamera.xCel;
			OdswiezKamere();
		}
	}

	if (value == TIMER_KAMERA_PRZESUN_Y)
	{
		if (abs(kamera.y - kamera.yCel) > kamera.zakres/350.0)
		{
			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_PRZESUN_Y);
			kamera.y += (kamera.yCel - kamera.y) / 35.0;
			OdswiezKamere();
		}
		else
		{
			kamera.y = kamera.yCel;
			OdswiezKamere();
		}
	}		

	if (value == TIMER_KAMERA_MYSZ_PRZESUN_X)
	{
		if (kamera.przesuwajx)
		{
			PrzesunKamere(-kamera.przesuwajx * 0.01 * kamera.zakres, 0);
			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_MYSZ_PRZESUN_X);
		}
	}

	if (value == TIMER_KAMERA_MYSZ_PRZESUN_Y)
	{
		if (kamera.przesuwajy)
		{
			PrzesunKamere(0, -kamera.przesuwajy * 0.01 * kamera.zakres);
			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_MYSZ_PRZESUN_Y);
		}
	}


	if (value == TIMER_ANIMACJI_TLA)
	{
		for (int i = 0; i < ILOSC_CHMUR; i++)
		{
			tabChmur[i]->Ruszaj();
		}

		for (int i = 0; i < tabPunktStab.size(); i++)
		{
			tabPunktStab[i]->ObracajSie();
		}

		glutTimerFunc(20, Dzialaj, TIMER_ANIMACJI_TLA);
	}

	if (value == TIMER_CO_DWASEKUNDOWY)
	{
		moznaBudowac = true;
		for (int i = 0; i < ILOSC_CHMUR; i++)
		{
			tabChmur[i]->SprawdzZasieg();
		}
		glutTimerFunc(2000, Dzialaj, TIMER_CO_DWASEKUNDOWY);
	}

	if (value == TIMER_BUDOWA_STWORKA)
	{
		moznaBudowac = true;
		glutTimerFunc(5000, Dzialaj, TIMER_BUDOWA_STWORKA);
	}


	if (value == TIMER_20)
	{
		for (int i = 0; i < tabGraczy.size(); i++)
		{
			
		}
		glutTimerFunc(20, Dzialaj, TIMER_20);
	}

	if (value == TIMER_500)
	{
		TekstPomocy();
		AktualizujRamke();
		glutTimerFunc(500, Dzialaj, TIMER_500);
		
	}

	if (value == TIMER_100)
	{
		FocusujKamere();
		glutTimerFunc(100, Dzialaj, TIMER_100);
	}







	if (value == TIMER_2)
	{

		if (etapGry == LACZENIE)
		{
			if(PolaczZSerwerem())
			{
				etapGry == OCZEKIWANIE_NA_WARUNKI;
				glutTimerFunc(2, Dzialaj, TIMER_2);
			}
			else
			{
				glutTimerFunc(4000, Dzialaj, TIMER_2);
			}
			return;
		}
			
		if (etapGry == UTRACONO_POLACZENIE) return;


		glutTimerFunc(2, Dzialaj, TIMER_2);
		OdbierzDane();

		if (etapGry == OCZEKIWANIE_NA_WARUNKI)
		{
			CzekajNaRozpoczenie();
		}

		if (etapGry == OCZEKIWANIE_NA_ROZPOCZECIE)
		{
			if (bajtyOdebrane > 0) etapGry = GRA;
			else return;
		}

		if (etapGry == GRA && (bajtyOdebrane > 0))
		{
			PrzetworzDane();
			tabGraczy[0]->PrzyspieszajBohatera(0,0);
			//DodajAkcjeDoWyslania();
			//DodajWiadomoscDoWyslania();
			WyslijDane();
			bajtyDoWyslania = 1;
			daneDoWyslania[0] = 0x01;
		}
	}





}

void cPlansza::_Idle(void)
{
    glutPostRedisplay();
}

void cPlansza::_Klawiatura(unsigned char key, int x, int y)
{
	float przesu = SZYBKOSC_PRZESUWANIA * kamera.zakres;

	switch(key)
	{
		// obsluga kamery
	case 'w':
		break;

	case 's':
		PrzesunKamere(0, -przesu);
		break;

	case 'a':
		wcisnieteA = 1;
		break;

	case 'd':
		wcisnieteD = 1;
		break;
	case '-':
		kamera.zakresCel *= SZYBKOSC_SCROLLOWANIA;
		if (kamera.zakresCel > KAMERA_MAX_ZAKRES) kamera.zakresCel = KAMERA_MAX_ZAKRES;
		glutTimerFunc(20, Dzialaj, TIMER_KAMERA_SCROLL);
		break;
	case '+':
		kamera.zakresCel /= SZYBKOSC_SCROLLOWANIA;
		if (kamera.zakresCel < KAMERA_MIN_ZAKRES) kamera.zakresCel = KAMERA_MIN_ZAKRES;
		glutTimerFunc(20, Dzialaj, TIMER_KAMERA_SCROLL);
		break;

	case 'o':
		tabGraczy[wybranyGracz]->DodajStworka(-900+1800*wybranyGracz, LISTA_STWOREK_KULA);
		break;
	case 'p':
		tabGraczy[wybranyGracz]->DodajStworka(-900+1800*wybranyGracz, LISTA_STWOREK_KWADRAT);
		break;
	case 'x':
		wybranyGracz = !wybranyGracz;
		break;
	case 'c':
		tabGraczy[wybranyGracz];
		break;
	case 'q':
		int a = 32;

		int b = a;
		break;


	}

}

void cPlansza::_KlawiszPusc(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'a':
		wcisnieteA = 0;
		break;

	case 'd':
		wcisnieteD = 0;
		break;
	}
}

void cPlansza::_ZmianaRozmiaruOkna(int width, int height)
{
	rozmiarOkna.x = width;
	rozmiarOkna.y = height;
	rozmiarOkna.proporcja = (float) rozmiarOkna.x / rozmiarOkna.y;

	glViewport(0, 0, width, height);

	OdswiezKamere();
}

void cPlansza::_MyszKlawisz(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{		
			testowy = ((float) x / rozmiarOkna.x * 2 * kamera.zakres - kamera.zakres) * rozmiarOkna.proporcja + kamera.x;
			testowy2 = - ((float) y / rozmiarOkna.y * 2 * kamera.zakres - kamera.zakres) + kamera.y;

			//tabPunktow[licznikPunktow][0] = testowy;
			//tabPunktow[licznikPunktow++][1] = testowy2;

			cout << "(" << testowy << " ; " << testowy2 << ") " << endl;
		}
	}

	if (button == GLUT_RIGHT_BUTTON)
	{
		if (!etapGry==GRA) return;

		if (state == GLUT_DOWN)
		{		
			float px = ((float) x / rozmiarOkna.x * 2 * kamera.zakres - kamera.zakres) * rozmiarOkna.proporcja + kamera.x;
			float py = - ((float) y / rozmiarOkna.y * 2 * kamera.zakres - kamera.zakres) + kamera.y;

			if (ramkaOpisu.czyWidoczna && KliknieteMenu(x, y) && ramkaOpisu.rodzajMenu)
			{
				int menu = KliknieteMenu(x, y);
				WykonajAkcje(menu);
			}
			else
			{
				czyFocusowac = 1;
				ramkaOpisu.czyWidoczna = tabGraczy[wybranyGracz]->WybierzJednostke(px, py);
			}

			for (auto iter = tabPunktStab.begin(); iter < tabPunktStab.end(); iter++)
			{
				if((px <= (*iter)->GetX() + ROZMIAR_PUNKTUSTABILNEGO) && (px >= (*iter)->GetX() - ROZMIAR_PUNKTUSTABILNEGO) && (py <= (*iter)->GetY() + ROZMIAR_PUNKTUSTABILNEGO) && (py >= (*iter)->GetY() - ROZMIAR_PUNKTUSTABILNEGO))
				{

				}
			}
		}
	}

	// pokretlo myszy
	if (button == 3 || button == 4)			
	{

		if (button == 3)				// przyblizanie
		{
			kamera.zakresCel /= SZYBKOSC_SCROLLOWANIA;
			float wspx = (x - rozmiarOkna.x / 2.0) * kamera.zakres / 1200;
			float wspy = (y - rozmiarOkna.y / 2.0) * kamera.zakres / 1200;
			PrzesunKamere(-wspx, -wspy);
			if (kamera.zakresCel < KAMERA_MIN_ZAKRES) kamera.zakresCel = KAMERA_MIN_ZAKRES;
		}
		

		if (button == 4)				// oddalanie
		{
			kamera.zakresCel *= SZYBKOSC_SCROLLOWANIA;
			if (kamera.zakresCel > KAMERA_MAX_ZAKRES) kamera.zakresCel = KAMERA_MAX_ZAKRES;
		}
		

		

		glutTimerFunc(20, Dzialaj, TIMER_KAMERA_PRZESUN_X);
		glutTimerFunc(20, Dzialaj, TIMER_KAMERA_SCROLL);
	}
}

void cPlansza::WykonajAkcje(int menu)
{
	float zloto = tabGraczy[wybranyGracz]->zloto;
	cGracz* gracz = tabGraczy[wybranyGracz];

	int cenyWiez[8] = {300, 200, 450, 1200, 250, 800, 600, 0}; 

	switch (ramkaOpisu.rodzajMenu)
	{
		case TEKSTURA_MENU_ZAMEK:
			if (menu == 1)
				if (gracz->ZaplacZlotem(500))
					gracz->zamek->Awansuj();
			if (menu == 2) 
				ramkaOpisu.rodzajMenu = TEKSTURA_MENU_BUDOWA_WIEZY;
			if (menu == 3)
				ramkaOpisu.rodzajMenu = TEKSTURA_MENU_BUDOWA_BOHATERA;
			if (menu == 4)
				ramkaOpisu.rodzajMenu = TEKSTURA_MENU_BUDOWA_STWORKA;
			break;
		case TEKSTURA_MENU_BOHATER:
			if (menu == 1)
				if (gracz->ZaplacZlotem(30))
					gracz->tabBohaterow[gracz->wybranyBohater]->Teleportuj();
	
			if (menu == 2)
				if (gracz->ZaplacZlotem(200))
					gracz->tabBohaterow[gracz->wybranyBohater]->Awansuj();

			if (menu == 3) if (gracz->ZaplacZlotem(150))
					gracz->tabBohaterow[gracz->wybranyBohater]->ZwiekszMoc();
			break;
		case TEKSTURA_MENU_WIEZA:
			if (menu == 1)
				if (gracz->ZaplacZlotem((int) (cenyWiez[tabGraczy[wybranyGracz]->zamek->typWybranejWiezy-11]/2.0)))
					gracz->zamek->AwansujWieze();
			if (menu == 2)
				gracz->ZaplacZlotem(gracz->zamek->SprzedajWieze());
			break;

		case TEKSTURA_MENU_STWOREK:
			if (menu == 1) 
				if (gracz->ZaplacZlotem(400))
					gracz->AwansujStworki();
			break;

		case TEKSTURA_MENU_BUDOWA_BOHATERA:
				if (menu > 2) break;
				if (gracz->ZaplacZlotem((menu == 1 ? 400 : (menu == 2 ? 500 : (menu == 3 ? 900 : 3000)))))
					gracz->DodajBohatera(gracz->x, gracz->y+100, menu);
			break;

		case TEKSTURA_MENU_BUDOWA_STWORKA:
			if (gracz->ZaplacZlotem((menu == 1 ? 30 : (menu == 2 ? 35 : (menu == 3 ? 80 : 220)))))
			{
				if (moznaBudowac)
					gracz->DodajStworka(gracz->x, menu+LISTA_STWOREK_KULA-1);
				moznaBudowac = false;
			}
			break;
			
		case TEKSTURA_MENU_BUDOWA_WIEZY:
			if (menu > 7) break;
			if (gracz->ZaplacZlotem(cenyWiez[menu-1]))
			{
				gracz->ZaplacZlotem(-cenyWiez[menu-1]);
				gracz->zamek->dodawanaWieza = menu;
				ramkaOpisu.rodzajMenu = TEKSTURA_WYBOR_MIEJSCA;
			}
			break;

		case TEKSTURA_WYBOR_MIEJSCA:
			if (menu > 3) break;
			if (gracz->ZaplacZlotem(cenyWiez[gracz->zamek->dodawanaWieza-1]))
			{
				gracz->zamek->DodajWieze(gracz->zamek->dodawanaWieza + 10, menu*100);
				ramkaOpisu.rodzajMenu = TEKSTURA_MENU_ZAMEK;
			}
			break;			


		}
}

void cPlansza::TekstPomocy()
{
	int menu = KliknieteMenu(mysz.x, mysz.y);
	if (ramkaOpisu.czyWidoczna && menu && ramkaOpisu.rodzajMenu)
	{
		
		int cenyWiez[8] = {300, 200, 450, 1200, 250, 800, 600, 0}; 

		switch (ramkaOpisu.rodzajMenu)
		{
		case TEKSTURA_MENU_ZAMEK:
			if (menu == 1) sprintf(ramkaOpisu.tekstPomocy, "Ulepsz Zamek (800$)");
			if (menu == 2) sprintf(ramkaOpisu.tekstPomocy, "Zbuduj Wieze");
			if (menu == 3) sprintf(ramkaOpisu.tekstPomocy, "Zbuduj Bohatera");
			if (menu == 4) sprintf(ramkaOpisu.tekstPomocy, "Zbuduj Stworka");
			break;
		case TEKSTURA_MENU_BOHATER:
			if (menu == 1) sprintf(ramkaOpisu.tekstPomocy, "Teleportuj do zamku (30$)");
			if (menu == 2) sprintf(ramkaOpisu.tekstPomocy, "Awansuj o jeden poziom (200$)");
			if (menu == 3) sprintf(ramkaOpisu.tekstPomocy, "Zwieksz moc silnika (150$)");
			if (menu == 4) sprintf(ramkaOpisu.tekstPomocy, "");
			break;
		case TEKSTURA_MENU_WIEZA:
			if (menu == 1) sprintf(ramkaOpisu.tekstPomocy, "Awansuj o jeden poziom (%d$)", (int) (cenyWiez[tabGraczy[wybranyGracz]->zamek->typWybranejWiezy-11]/2.0));
			if (menu == 2) sprintf(ramkaOpisu.tekstPomocy, "Sprzedaj (zrot czesci $)");
			if (menu == 3) sprintf(ramkaOpisu.tekstPomocy, "");
			if (menu == 4) sprintf(ramkaOpisu.tekstPomocy, "");
			break;

		case TEKSTURA_MENU_STWOREK:
			if (menu == 1) sprintf(ramkaOpisu.tekstPomocy, "Ulepsz parametry (400$)");
			if (menu == 2) sprintf(ramkaOpisu.tekstPomocy, "");
			if (menu == 3) sprintf(ramkaOpisu.tekstPomocy, "");
			if (menu == 4) sprintf(ramkaOpisu.tekstPomocy, "");
			break;

		case TEKSTURA_MENU_BUDOWA_BOHATERA:
			if (menu == 1) sprintf(ramkaOpisu.tekstPomocy, "Boahter 1 (400$)");
			if (menu == 2) sprintf(ramkaOpisu.tekstPomocy, "Bohater 2 (500$)");
			if (menu == 3) sprintf(ramkaOpisu.tekstPomocy, "");
			if (menu == 4) sprintf(ramkaOpisu.tekstPomocy, "");
			break;

		case TEKSTURA_MENU_BUDOWA_STWORKA:
			if (menu == 1) sprintf(ramkaOpisu.tekstPomocy, "Stworek 1 (30$)");
			if (menu == 2) sprintf(ramkaOpisu.tekstPomocy, "Stworek 2 (35$)");
			if (menu == 3) sprintf(ramkaOpisu.tekstPomocy, "");
			if (menu == 4) sprintf(ramkaOpisu.tekstPomocy, "");
			break;
		case TEKSTURA_MENU_BUDOWA_WIEZY:
			if (menu == 1) sprintf(ramkaOpisu.tekstPomocy, "Wieza lucznicza (%d$)", cenyWiez[menu-1]);
			if (menu == 2) sprintf(ramkaOpisu.tekstPomocy, "Wieza kamienna (%d$)", cenyWiez[menu-1]);
			if (menu == 3) sprintf(ramkaOpisu.tekstPomocy, "Wieza strzelecka (%d$)", cenyWiez[menu-1]);
			if (menu == 4) sprintf(ramkaOpisu.tekstPomocy, "Wieza laser-zaglady (%d$)", cenyWiez[menu-1]);
			if (menu == 5) sprintf(ramkaOpisu.tekstPomocy, "Wieza ogniomiotna (%d$)", cenyWiez[menu-1]);
			if (menu == 6) sprintf(ramkaOpisu.tekstPomocy, "Wieza wydobywajaca zloto (%d$)", cenyWiez[menu-1]);
			if (menu == 7) sprintf(ramkaOpisu.tekstPomocy, "Wieza uzdrowiciela (%d$)", cenyWiez[menu-1]);
			break;

		case TEKSTURA_WYBOR_MIEJSCA:
			if (menu == 1) sprintf(ramkaOpisu.tekstPomocy, "Wybuduj po lewej");
			if (menu == 2) sprintf(ramkaOpisu.tekstPomocy, "Wybuduj po srodku");
			if (menu == 3) sprintf(ramkaOpisu.tekstPomocy, "Wybuduj po prawej");
			break;			
		}
	}
	else ramkaOpisu.tekstPomocy[0] = 0;
}

int cPlansza::KliknieteMenu(int px, int py)
{
	int wynik = 0;
	float lx = 75 * (px / (float) rozmiarOkna.x) * rozmiarOkna.proporcja;
	float ly = 75 - 75 * py / (float) rozmiarOkna.y;
	
	if (abs(lx-27.5) < 2.5 && abs(ly-5.5)<2.5) wynik=3;
	if (abs(lx-27.5) < 2.5 && abs(ly-11.5)<2.5) wynik=1;

	if (abs(lx-33.5) < 2.5 && abs(ly-5.5)<2.5) wynik=4;
	if (abs(lx-33.5) < 2.5 && abs(ly-11.5)<2.5) wynik=2;

	if (abs(lx-39.5) < 2.5 && abs(ly-5.5)<2.5) wynik=7;
	if (abs(lx-39.5) < 2.5 && abs(ly-11.5)<2.5) wynik=5;

	if (abs(lx-45.5) < 2.5 && abs(ly-5.5)<2.5) wynik=8;
	if (abs(lx-45.5) < 2.5 && abs(ly-11.5)<2.5) wynik=6;

	return wynik;
}

void cPlansza::_MyszRuch(int x,int y)
{
	mysz.x = x;
	mysz.y = y;

	if (kamera.przesuwajx == 0)
	{
		if (x < KAMERA_PRZESUWANIE_MYSZA)
		{
			kamera.przesuwajx = -1;
			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_MYSZ_PRZESUN_X);
		}
		if (x > rozmiarOkna.x - KAMERA_PRZESUWANIE_MYSZA)
		{
			kamera.przesuwajx = +1;
			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_MYSZ_PRZESUN_X);
		}
	}
	else
	{
		if (x > KAMERA_PRZESUWANIE_MYSZA && x < rozmiarOkna.x - KAMERA_PRZESUWANIE_MYSZA) kamera.przesuwajx = 0;
	}


	if (kamera.przesuwajy == 0)
	{
		if (y < KAMERA_PRZESUWANIE_MYSZA)
		{
			kamera.przesuwajy = -1;
			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_MYSZ_PRZESUN_Y);
		}
		if (y > rozmiarOkna.y - KAMERA_PRZESUWANIE_MYSZA)
		{
			kamera.przesuwajy = +1;
			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_MYSZ_PRZESUN_Y);
		}
	}
	else
	{
		if (y > KAMERA_PRZESUWANIE_MYSZA && y < rozmiarOkna.y - KAMERA_PRZESUWANIE_MYSZA) kamera.przesuwajy = 0;
	}


}

void cPlansza::OdswiezKamere()
{
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glFrustum( -kamera.zakres*rozmiarOkna.proporcja, kamera.zakres*rozmiarOkna.proporcja, -kamera.zakres, kamera.zakres, 10.0, 40);
	gluLookAt(0, 0, 5.0001, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-5);
	glTranslatef(-kamera.x, -kamera.y, 0);
}

void cPlansza::PrzesunKamere(float dx, float dy)
{
	if (dy)
	{
		kamera.yCel += dy;
		if (kamera.yCel > KAMERA_MAX_POLOZENIE_Y) kamera.yCel = KAMERA_MAX_POLOZENIE_Y;
		if (kamera.yCel < KAMERA_MIN_POLOZENIE_Y) kamera.yCel = KAMERA_MIN_POLOZENIE_Y;
		glutTimerFunc(20, Dzialaj, TIMER_KAMERA_PRZESUN_Y);
	}

	if (dx)
	{
		kamera.xCel -= dx;
		if (kamera.xCel < -KAMERA_MAX_POLOZENIE_X) kamera.xCel = -KAMERA_MAX_POLOZENIE_X;
		if (kamera.xCel > KAMERA_MAX_POLOZENIE_X) kamera.xCel = KAMERA_MAX_POLOZENIE_X;
		glutTimerFunc(20, Dzialaj, TIMER_KAMERA_PRZESUN_X);
	}
}

void cPlansza::AktualizujRamke()
{
	tabGraczy[wybranyGracz]->AktualizujRamke();
}

void cPlansza::FocusujKamere()
{
	if (czyFocusowac) tabGraczy[wybranyGracz]->FocusujKamere();
}

void cPlansza::WczytajTeren()
{
	FILE* odczytTerenu = fopen("tx\\1.bin", "r");
	BYTE* tablicaPikseli = new BYTE[5000*850];
	fread(tablicaPikseli, 1, 5000*850, odczytTerenu);
	fclose(odczytTerenu);

	{		// palmy krañcowe
		cPalma* nowaPalma = new cPalma(TEKSTURA_PALMA1, 35, 0, -1125, 61, -0.4);
		tabPalm.push_back(nowaPalma);
		nowaPalma = new cPalma(TEKSTURA_PALMA1, 25, 0, -1175, 61, -0.4);
		tabPalm.push_back(nowaPalma);

		nowaPalma = new cPalma(TEKSTURA_PALMA1, 35, 0, 1125, 61, -0.4);
		tabPalm.push_back(nowaPalma);
		nowaPalma = new cPalma(TEKSTURA_PALMA1, 25, 0, 1175, 61, -0.4);
		tabPalm.push_back(nowaPalma);
	}

	for (int k = 0; k < 5000; k++)				// przepisz z wektra do tabeli pól i wykonaje pola specjalne
	{
		if (k == 464)
		{
			int a = k;
		}
		for (int w = 849; w >= 0; w--)
		{
			unsigned char pole = tablicaPikseli[w*5000 + k];

			if (pole == POLE_TLO) continue;

			switch (pole)
			{
			case POLE_GRACZ:
				{
					int kierunek = 1 - 2*tabGraczy.size();
					cGracz* nowyGracz = new cGracz(TabDoX(k*10), TabDoY(w), kierunek);
					tabGraczy.push_back(nowyGracz);
				}
				pole = POLE_TLO;
				break;

			case POLE_PALMA:
				sKOLOR kolor;
				kolor.b = 0.9;
				kolor.r = 1;
				kolor.g = 1;
				{cPalma* nowaPalma = new cPalma(TEKSTURA_PALMA1, 15+rand()%9, -5+rand()%10, TabDoX(k*10), TabDoY(w), -0.4);
				tabPalm.push_back(nowaPalma);}
				pole = POLE_TLO;
				break;

			case POLE_PUNKT_STABILNY: 
				cPunktStabilny* nowyPunkt = new cPunktStabilny(TabDoX(k*10), TabDoY(w), 0);
				tabPunktStab.push_back(nowyPunkt);
				pole = POLE_TLO;
			}
			if (pole == POLE_TLO) continue;

			if (tabPol[k*10] == -7777)
			{
				float wynik = TabDoY(w) + 0.65;
				tabPol[k*10] = wynik;
				tabTypowPol[k*10] = pole;
			}
		}
	}
	delete [] tablicaPikseli;

	for (int k = 0; k < 50000; k++)
	{
		if (k%10 == 0) continue;
		int ktory = k % 10;
		tabPol[k] = tabPol[k - ktory] + ktory / 10.0 * (tabPol[k - ktory+10] - tabPol[k - ktory]);
	}

}

void cPlansza::DodajPunktStabilny(float _x, float _y)
{
	//cPunktStabilny* nowyPunkt = new cPunktStabilny(_x, _y, 0);
	//tabPunktStab.push_back(nowyPunkt);
}

void cPlansza::UtworzListy()
{
	// punkt stabilny
	glGenLists(LISTA_PUNKT_STABILNY);
	glNewList(LISTA_PUNKT_STABILNY, GL_COMPILE);

		glBegin(GL_POLYGON);
		glColor4f(0,0,0,1);
		for (int i = 0; i < 33; i++)
		{
			glVertex2f(ROZMIAR_PUNKTUSTABILNEGO * sin(6.2832*i/33), ROZMIAR_PUNKTUSTABILNEGO * cos(6.2832*i/33));
		}
		glEnd();

		glBegin(GL_POLYGON);
		glColor4f(0.38,0.25,0,1);
		for (int i = 0; i < 33; i++)
		{
			glVertex2f(0.8 * ROZMIAR_PUNKTUSTABILNEGO * sin(6.2832*i/33), 0.8 * ROZMIAR_PUNKTUSTABILNEGO * cos(6.2832*i/33));
		}
		glEnd();

		glBegin(GL_POLYGON);
		glColor4f(0.63,0.13,0,1);
		for (int i = 0; i < 33; i++)
		{
			glVertex2f(0.45 * ROZMIAR_PUNKTUSTABILNEGO * sin(6.2832*i/33), 0.45 * ROZMIAR_PUNKTUSTABILNEGO * cos(6.2832*i/33));
		}
		glEnd();

		glColor4f(0,0,0,1);
		glBegin(GL_POLYGON);
			glVertex2f(-0.1 * ROZMIAR_PUNKTUSTABILNEGO, -0.8 * ROZMIAR_PUNKTUSTABILNEGO);
			glVertex2f(0.1 * ROZMIAR_PUNKTUSTABILNEGO, -0.8 * ROZMIAR_PUNKTUSTABILNEGO);
			glVertex2f(0.1 * ROZMIAR_PUNKTUSTABILNEGO, 0.8 * ROZMIAR_PUNKTUSTABILNEGO);
			glVertex2f(-0.1 * ROZMIAR_PUNKTUSTABILNEGO, 0.8 * ROZMIAR_PUNKTUSTABILNEGO);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex2f(-0.8 * ROZMIAR_PUNKTUSTABILNEGO, -0.1 * ROZMIAR_PUNKTUSTABILNEGO);
			glVertex2f(0.8 * ROZMIAR_PUNKTUSTABILNEGO, -0.1 * ROZMIAR_PUNKTUSTABILNEGO);
			glVertex2f(0.8 * ROZMIAR_PUNKTUSTABILNEGO, 0.1 * ROZMIAR_PUNKTUSTABILNEGO);
			glVertex2f(-0.8 * ROZMIAR_PUNKTUSTABILNEGO, 0.1 * ROZMIAR_PUNKTUSTABILNEGO);
		glEnd();
	glEndList();


	
	// bohater LISTA_BOHATER2
	
	glGenLists(LISTA_BOHATER2);
	glNewList(LISTA_BOHATER2, GL_COMPILE);
	
	float maxZ = -1;

		glPushMatrix();			// tylne kolo
			glTranslatef(0, BOHATER2_ROZMIAR,  maxZ);	
			glBegin(GL_POLYGON);
				glColor4f(0,0,0, 0.7);
				for (int i = 0; i < 33; i++)	glVertex2f(BOHATER2_ROZMIAR * sin(6.2832*i/33), BOHATER2_ROZMIAR * cos(6.2832*i/33));
			glEnd();
			glColor4f(1,1,0, 0.7);
			glBegin(GL_POLYGON);
				for (int i = 0; i < 33; i++)	glVertex2f(0.55 * BOHATER2_ROZMIAR * sin(6.2832*i/33), 0.55 * BOHATER2_ROZMIAR * cos(6.2832*i/33));
			glEnd();
		glPopMatrix();



				
			glColor4f(0.6, 0.05, 0.3, 0.8);			// dolny prostokat
			glBegin(GL_POLYGON);
				glVertex3f(-0.8*BOHATER2_ROZMIAR, 0.8*BOHATER2_ROZMIAR, 0);
				glVertex3f(+0.8*BOHATER2_ROZMIAR, 0.8*BOHATER2_ROZMIAR, 0);
				glVertex3f(+0.8*BOHATER2_ROZMIAR, 0.8*BOHATER2_ROZMIAR, maxZ);
				glVertex3f(-0.8*BOHATER2_ROZMIAR, 0.8*BOHATER2_ROZMIAR, maxZ);
			glEnd();

			glColor4f(0.6, 0.05, 0.3, 0.8);
			glBegin(GL_POLYGON);
				glVertex3f(+0.8*BOHATER2_ROZMIAR, 0.8*BOHATER2_ROZMIAR, maxZ/2);
				glVertex3f(+0.8*BOHATER2_ROZMIAR, 5*BOHATER2_ROZMIAR, maxZ/2);
				glVertex3f(+0.5*BOHATER2_ROZMIAR, 5*BOHATER2_ROZMIAR, maxZ/2);
				glVertex3f(+0.5*BOHATER2_ROZMIAR, 0.8*BOHATER2_ROZMIAR, maxZ/2);
			glEnd();

			glColor4f(0.6, 0.05, 0.3, 0.9);
			glBegin(GL_POLYGON);
				glVertex3f(+0.8*BOHATER2_ROZMIAR, 0.8*BOHATER2_ROZMIAR, maxZ/1.5);
				glVertex3f(+0.8*BOHATER2_ROZMIAR, 5*BOHATER2_ROZMIAR, maxZ/1.5);
				glVertex3f(+0.8*BOHATER2_ROZMIAR, 5*BOHATER2_ROZMIAR, maxZ/2.7);
				glVertex3f(+0.8*BOHATER2_ROZMIAR, 0.8*BOHATER2_ROZMIAR, maxZ/2.7);
			glEnd();

			glColor4f(0.6, 0.9, 0.3, 0.9);
			glBegin(GL_POLYGON);
				glVertex3f(+0.4*BOHATER2_ROZMIAR, 5*BOHATER2_ROZMIAR, maxZ*0.2);
				glVertex3f(+0.9*BOHATER2_ROZMIAR, 5*BOHATER2_ROZMIAR, maxZ*0.2);
				glVertex3f(+0.9*BOHATER2_ROZMIAR, 5*BOHATER2_ROZMIAR, maxZ*0.8);
				glVertex3f(+0.4*BOHATER2_ROZMIAR, 5*BOHATER2_ROZMIAR, maxZ*0.8);
			glEnd();

			glColor4f(0.6, 0.9, 0.3, 0.9);
			glBegin(GL_POLYGON);
				glVertex3f(+0.65*BOHATER2_ROZMIAR, 4.9*BOHATER2_ROZMIAR, maxZ*0.2);
				glVertex3f(+0.65*BOHATER2_ROZMIAR, 5.2*BOHATER2_ROZMIAR, maxZ*0.2);
				glVertex3f(+0.65*BOHATER2_ROZMIAR, 5.2*BOHATER2_ROZMIAR, maxZ*0.8);
				glVertex3f(+0.65*BOHATER2_ROZMIAR, 4.9*BOHATER2_ROZMIAR, maxZ*0.8);
			glEnd();



		glPushMatrix();				// przednie kolo
			glTranslatef(0, BOHATER2_ROZMIAR,  0);	
			glBegin(GL_POLYGON);
				glColor4f(0,0,0,1);
				for (int i = 0; i < 33; i++)	glVertex2f(BOHATER2_ROZMIAR * sin(6.2832*i/33), BOHATER2_ROZMIAR * cos(6.2832*i/33));
			glEnd();
			glColor4f(1,1,0,1);
			glBegin(GL_POLYGON);
				for (int i = 0; i < 33; i++)	glVertex2f(0.55 * BOHATER2_ROZMIAR * sin(6.2832*i/33), 0.55 * BOHATER2_ROZMIAR * cos(6.2832*i/33));
			glEnd();
		glPopMatrix();

	glEndList();


	// bohater

	glGenLists(LISTA_BOHATER1);
	glNewList(LISTA_BOHATER1, GL_COMPILE);

		glBegin(GL_POLYGON);
			glVertex2f(	0	,	0	);
			glVertex2f(	-1.444444444	,	0	);
			glVertex2f(	-2.444444444	,	-0.444444444	);
			glVertex2f(	-2.444444444	,	0.222222222	);
			glVertex2f(	-1.777777778	,	1	);
			glVertex2f(	-1	,	1.222222222	);
			glVertex2f(	-0.555555556	,	1.555555556	);
			glVertex2f(	-0.333333333	,	5.333333333	);
			glVertex2f(	1.222222222	,	5.555555556	);
			glVertex2f(	3	,	5.444444444	);
			glVertex2f(	3.777777778	,	4.222222222	);
			glVertex2f(	3.888888889	,	2	);
			glVertex2f(	6.111111111	,	2.555555556	);
			glVertex2f(	8	,	2.555555556	);
			glVertex2f(	8.444444444	,	2.111111111	);
			glVertex2f(	8.888888889	,	1.666666667	);
			glVertex2f(	9.222222222	,	0.666666667	);
			glVertex2f(	9.444444444	,	0.444444444	);
			glVertex2f(	9.444444444	,	0	);
		glEnd();



		//glColor4f(0,0,0,0.3);

		glBegin(GL_LINES);
			glVertex2f(	0	,	0	);		glVertex3f(	0	,	0	,	-1.5	);
			glVertex2f(	-1.444444444	,	0	);		glVertex3f(	-1.444444444	,	0	,	-1.5	);
			glVertex2f(	-2.444444444	,	-0.444444444	);		glVertex3f(	-2.444444444	,	-0.444444444	,	-1.5	);
			glVertex2f(	-2.444444444	,	0.222222222	);		glVertex3f(	-2.444444444	,	0.222222222	,	-1.5	);
			glVertex2f(	-1.777777778	,	1	);		glVertex3f(	-1.777777778	,	1	,	-1.5	);
			glVertex2f(	-1	,	1.222222222	);		glVertex3f(	-1	,	1.222222222	,	-1.5	);
			glVertex2f(	-0.555555556	,	1.555555556	);		glVertex3f(	-0.555555556	,	1.555555556	,	-1.5	);
			glVertex2f(	-0.333333333	,	5.333333333	);		glVertex3f(	-0.333333333	,	5.333333333	,	-1.5	);
			glVertex2f(	1.222222222	,	5.555555556	);		glVertex3f(	1.222222222	,	5.555555556	,	-1.5	);
			glVertex2f(	3	,	5.444444444	);		glVertex3f(	3	,	5.444444444	,	-1.5	);
			glVertex2f(	3.777777778	,	4.222222222	);		glVertex3f(	3.777777778	,	4.222222222	,	-1.5	);
			glVertex2f(	3.888888889	,	2	);		glVertex3f(	3.888888889	,	2	,	-1.5	);
			glVertex2f(	6.111111111	,	2.555555556	);		glVertex3f(	6.111111111	,	2.555555556	,	-1.5	);
			glVertex2f(	8	,	2.555555556	);		glVertex3f(	8	,	2.555555556	,	-1.5	);
			glVertex2f(	8.444444444	,	2.111111111	);		glVertex3f(	8.444444444	,	2.111111111	,	-1.5	);
			glVertex2f(	8.888888889	,	1.666666667	);		glVertex3f(	8.888888889	,	1.666666667	,	-1.5	);
			glVertex2f(	9.222222222	,	0.666666667	);		glVertex3f(	9.222222222	,	0.666666667	,	-1.5	);
			glVertex2f(	9.444444444	,	0.444444444	);		glVertex3f(	9.444444444	,	0.444444444	,	-1.5	);
			glVertex2f(	9.444444444	,	0	);		glVertex3f(	9.444444444	,	0	,	-1.5	);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(	0	,	0	,	-1.5	);
			glVertex3f(	-1.444444444	,	0	,	-1.5	);
			glVertex3f(	-2.444444444	,	-0.444444444	,	-1.5	);
			glVertex3f(	-2.444444444	,	0.222222222	,	-1.5	);
			glVertex3f(	-1.777777778	,	1	,	-1.5	);
			glVertex3f(	-1	,	1.222222222	,	-1.5	);
			glVertex3f(	-0.555555556	,	1.555555556	,	-1.5	);
			glVertex3f(	-0.333333333	,	5.333333333	,	-1.5	);
			glVertex3f(	1.222222222	,	5.555555556	,	-1.5	);
			glVertex3f(	3	,	5.444444444	,	-1.5	);
			glVertex3f(	3.777777778	,	4.222222222	,	-1.5	);
			glVertex3f(	3.888888889	,	2	,	-1.5	);
			glVertex3f(	6.111111111	,	2.555555556	,	-1.5	);
			glVertex3f(	8	,	2.555555556	,	-1.5	);
			glVertex3f(	8.444444444	,	2.111111111	,	-1.5	);
			glVertex3f(	8.888888889	,	1.666666667	,	-1.5	);
			glVertex3f(	9.222222222	,	0.666666667	,	-1.5	);
			glVertex3f(	9.444444444	,	0.444444444	,	-1.5	);
			glVertex3f(	9.444444444	,	0	,	-1.5	);
		glEnd();




		glBegin(GL_POLYGON);
			glColor4f(0,0,0,1);
			for (int i = 0; i < 33; i++)
			{
				glVertex2f(BOHATER_PROMIEN1 * sin(6.2832*i/33), BOHATER_PROMIEN1 * cos(6.2832*i/33));
			}		
		glEnd();

		glColor4f(1,1,0,1);
		glBegin(GL_POLYGON);
			for (int i = 0; i < 33; i++)
			{
				glVertex2f(0.55 * BOHATER_PROMIEN1 * sin(6.2832*i/33), 0.55 * BOHATER_PROMIEN1 * cos(6.2832*i/33));
			}		
		glEnd();

		glTranslatef(BOHATER_POZYCJA_KOLA, BOHATER_PROMIEN2 - BOHATER_PROMIEN1, 0);

		glBegin(GL_POLYGON);
			glColor4f(0,0,0,1);
			for (int i = 0; i < 33; i++)
			{
				glVertex2f(BOHATER_PROMIEN2 * sin(6.2832*i/33), BOHATER_PROMIEN2 * cos(6.2832*i/33));
			}		
		glEnd();

		glBegin(GL_POLYGON);
			glColor4f(1,1,0,1);
			for (int i = 0; i < 33; i++)
			{
				glVertex2f(0.55 * BOHATER_PROMIEN2 * sin(6.2832*i/33), 0.55 * BOHATER_PROMIEN2 * cos(6.2832*i/33));
			}		
		glEnd();
	glEndList();




	// STWOREK KULA
	glGenLists(LISTA_STWOREK_KULA);
	glNewList(LISTA_STWOREK_KULA, GL_COMPILE);
	glBegin(GL_POLYGON);
		for (int i = 0; i < 33; i++)
		{
			glVertex2f(ROMIAR_STWORKA_KULA * sin(6.2832*i/33), ROMIAR_STWORKA_KULA * cos(6.2832*i/33));
		}
		glEnd();
	glEndList();
	


}

void cPlansza::TworzTekstury()
{
	SOIL_load_OGL_texture("tx\\chmura1.png", SOIL_LOAD_AUTO, TEKSTURA_CHMURA1, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\chmura2.png", SOIL_LOAD_AUTO, TEKSTURA_CHMURA2, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\palma3.png", SOIL_LOAD_AUTO, TEKSTURA_PALMA1, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\1tlo.png", SOIL_LOAD_AUTO, TEKSTURA_MAPA_TERENU, SOIL_FLAG_INVERT_Y);

//	SOIL_load_OGL_texture("tx\\Przemek.png", SOIL_LOAD_AUTO, 77, SOIL_FLAG_INVERT_Y);

	SOIL_load_OGL_texture("tx\\zlota_moneta.png", SOIL_LOAD_AUTO, TEKSTURA_MONETA, SOIL_FLAG_INVERT_Y);


	SOIL_load_OGL_texture("tx\\zamek1.png", SOIL_LOAD_AUTO, TEKSTURA_ZAMEK, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\wieza1.png", SOIL_LOAD_AUTO, TEKSTURA_WIEZA1, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\wieza2.png", SOIL_LOAD_AUTO, TEKSTURA_WIEZA2, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\wieza3.png", SOIL_LOAD_AUTO, TEKSTURA_WIEZA3, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\wieza4.png", SOIL_LOAD_AUTO, TEKSTURA_WIEZA4, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\wieza5.png", SOIL_LOAD_AUTO, TEKSTURA_WIEZA5, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\wieza6.png", SOIL_LOAD_AUTO, TEKSTURA_WIEZA6, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\wieza7.png", SOIL_LOAD_AUTO, TEKSTURA_WIEZA7, SOIL_FLAG_INVERT_Y);

	SOIL_load_OGL_texture("tx\\ikona_zamek1.png", SOIL_LOAD_AUTO, IKONA_ZAMEK, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\ikona_wieza1.png", SOIL_LOAD_AUTO, IKONA_WIEZA1, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\ikona_wieza2.png", SOIL_LOAD_AUTO, IKONA_WIEZA2, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\ikona_wieza3.png", SOIL_LOAD_AUTO, IKONA_WIEZA3, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\ikona_wieza4.png", SOIL_LOAD_AUTO, IKONA_WIEZA4, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\ikona_wieza5.png", SOIL_LOAD_AUTO, IKONA_WIEZA5, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\ikona_wieza6.png", SOIL_LOAD_AUTO, IKONA_WIEZA6, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\ikona_wieza7.png", SOIL_LOAD_AUTO, IKONA_WIEZA7, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\ikona_bohater1.png", SOIL_LOAD_AUTO, IKONA_BOHATER1, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\ikona_bohater2.png", SOIL_LOAD_AUTO, IKONA_BOHATER2, SOIL_FLAG_INVERT_Y);
	
	SOIL_load_OGL_texture("tx\\ikona_stworek1.png", SOIL_LOAD_AUTO, IKONA_STWOREK1, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\ikona_stworek2.png", SOIL_LOAD_AUTO, IKONA_STWOREK2, SOIL_FLAG_INVERT_Y);



	SOIL_load_OGL_texture("tx\\menu_zamek.png", SOIL_LOAD_AUTO, TEKSTURA_MENU_ZAMEK, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\menu_wieza.png", SOIL_LOAD_AUTO, TEKSTURA_MENU_WIEZA, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\menu_bohater.png", SOIL_LOAD_AUTO, TEKSTURA_MENU_BOHATER, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\menu_stworek.png", SOIL_LOAD_AUTO, TEKSTURA_MENU_STWOREK, SOIL_FLAG_INVERT_Y);

	SOIL_load_OGL_texture("tx\\menu_budowa_bohatera.png", SOIL_LOAD_AUTO, TEKSTURA_MENU_BUDOWA_BOHATERA, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\menu_budowa_wiezy.png", SOIL_LOAD_AUTO, TEKSTURA_MENU_BUDOWA_WIEZY, SOIL_FLAG_INVERT_Y);

	SOIL_load_OGL_texture("tx\\menu_budowa_stworka.png", SOIL_LOAD_AUTO, TEKSTURA_MENU_BUDOWA_STWORKA, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\menu_wybor_miejsca.png", SOIL_LOAD_AUTO, TEKSTURA_WYBOR_MIEJSCA, SOIL_FLAG_INVERT_Y);

}

void cPlansza::_KlawiszeSpecjalne(int key, int x, int y)
{
	float przesu = SZYBKOSC_PRZESUWANIA * kamera.zakres;

	switch(key)
	{
	case GLUT_KEY_UP:
		PrzesunKamere(0, przesu);
		czyFocusowac = 0;
		break;	
	case GLUT_KEY_DOWN:
		PrzesunKamere(0, -przesu);
		czyFocusowac = 0;
		break;
	case GLUT_KEY_LEFT:
		PrzesunKamere(przesu, 0);
		czyFocusowac = 0;
		break;
	case GLUT_KEY_RIGHT:
		PrzesunKamere(-przesu, 0);
		czyFocusowac = 0;
		break;
	}
}

float cPlansza::TabDoX(int k)
{
	return (-1000 + 0.4*k / 10);
}

float cPlansza::TabDoY(int w)
{
	return (0.4*w - 170);
}

int cPlansza::XDoTab(float x)
{
	return ((x + 1000) / 0.4 * 10) + 0.5;
}

int cPlansza::YDoTab(float y)
{
	return ((y+170) / 0.4) + 0.5;
}

float cPlansza::Wysokosc(float x)
{
	float xWTab = ((x + 1000) / 0.4 * 10);
	
	//float y1 = tabPol[(int) xWTab];
	//float y2 = tabPol[((int) xWTab) + 1];
	//float x2 = (int) xWTab;
	//float wynik = y1 + (y2 - y1) * (xWTab - x2);
	float wynik = tabPol[(int) xWTab]; + ((tabPol[((int) xWTab) + 1] - tabPol[(int) xWTab]) * (xWTab - (int) xWTab));
	return wynik;
}

void cPlansza::DodajElement(float x1, float x2, float y1, float y2)
{
	cBelka *nowa = new cBelka(x1, y1, x2, y2, 1);
	tabElementow.push_back(nowa);
}




