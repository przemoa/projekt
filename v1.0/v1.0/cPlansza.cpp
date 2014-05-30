#include "cPlansza.h"
#include "naglowki.h"



cPlansza::cPlansza(void)
{
	
	testowy = 0;
	testowy2 = 0;
	//licznikPunktow = 0;

	rozmiarOkna.x = 1000;
	rozmiarOkna.y = 600;
	rozmiarOkna.proporcja = (float) rozmiarOkna.x / rozmiarOkna.y;

	kamera.x = 950;
	kamera.xCel = -950;
	kamera.y = 110;
	kamera.yCel = 110;
	kamera.zakres = 1200;
	kamera.zakresCel = 55;
	kamera.przesuwajx = 0;
	kamera.przesuwajy = 0;
	glutTimerFunc(20, Dzialaj, TIMER_KAMERA_PRZESUN_X);
	glutTimerFunc(20, Dzialaj, TIMER_KAMERA_PRZESUN_Y);
	glutTimerFunc(20, Dzialaj, TIMER_KAMERA_SCROLL);

	ramkaOpisu.czyWidoczna = false;



	TworzTekstury();
	UtworzListy();

	for (int i = 0; i < ILOSC_CHMUR; i++)
	{
		sKOLOR kolor;
		kolor.b = 0.9;
		kolor.r = 1 - i/20.0;
		kolor.g = 1;
		tabChmur[i] = new cChmura(((rand()%2) ? TEKSTURA_CHMURA1 : TEKSTURA_CHMURA2), 
									-1000 + (2000.0 / ILOSC_CHMUR) * i + rand()%50, 80+rand()%50, -12,
									kolor, 8+rand()%11, rand()%2*180-7+rand()%14, 15+rand()%25);
	}

	// wczytaj plansze
	for (int k = 0; k < 50000; k+=10)
	{
		tabPol[k] = -7777;
		tabTypowPol[k] = -7777;
	}
	WczytajTeren();

}

cPlansza::~cPlansza(void)
{

}

void cPlansza::_Dzialaj(int value)
{
	// Plynne przewijanie kamery
	if (value == TIMER_KAMERA_SCROLL)
	{
		if (abs(kamera.zakres - kamera.zakresCel) > 0.1)
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
		if (abs(kamera.x - kamera.xCel) > 0.05)
		{
			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_PRZESUN_X);
			kamera.x += (kamera.xCel - kamera.x) / 35.0;
			OdswiezKamere();
		}
		else
		{
			kamera.x = kamera.xCel;
		}
	}

	if (value == TIMER_KAMERA_PRZESUN_Y)
	{
		if (abs(kamera.y - kamera.yCel) > 0.05)
		{
			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_PRZESUN_Y);
			kamera.y += (kamera.yCel - kamera.y) / 35.0;
			OdswiezKamere();
		}
		else
		{
			kamera.y = kamera.yCel;
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
		for (int i = 0; i < ILOSC_CHMUR; i++)
		{
			tabChmur[i]->SprawdzZasieg();
		}
		glutTimerFunc(2000, Dzialaj, TIMER_CO_DWASEKUNDOWY);
	}

	if (value == TIMER_20)
	{
		//for (int i = 0; i < tabGraczy.size(); i++)
		{
			tabGraczy[0]->Dzialaj();
		}
		glutTimerFunc(20, Dzialaj, TIMER_20);
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
		tabGraczy[0]->RuszajBohatera(25*-KROK_PRZYSPIESZANIA_BOHATERA, 0);
		break;

	case 'd':
		tabGraczy[0]->RuszajBohatera(25*KROK_PRZYSPIESZANIA_BOHATERA, 0);
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
		tabGraczy[0]->DodajStworka(-900, LISTA_STWOREK_KULA);
		break;
	case 'p':
		tabGraczy[0]->DodajStworka(-900, LISTA_STWOREK_KWADRAT);
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
		if (state == GLUT_DOWN)
		{		
			float px = ((float) x / rozmiarOkna.x * 2 * kamera.zakres - kamera.zakres) * rozmiarOkna.proporcja + kamera.x;
			float py = - ((float) y / rozmiarOkna.y * 2 * kamera.zakres - kamera.zakres) + kamera.y;

			ramkaOpisu.czyWidoczna = tabGraczy[0]->WybierzJednostke(px, py);
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

void cPlansza::_MyszRuch(int x,int y)
{

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

void cPlansza::WczytajTeren()
{
	FILE* odczytTerenu = fopen("tx\\1.bin", "r");
	BYTE* tablicaPikseli = new BYTE[5000*850];
	fread(tablicaPikseli, 1, 5000*850, odczytTerenu);
	fclose(odczytTerenu);

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
				{cPalma* nowaPalma = new cPalma(TEKSTURA_PALMA1, 5+rand()%4, -5+rand()%10, TabDoX(k*10), TabDoY(w), -0.9);
				tabPalm.push_back(nowaPalma);}
				pole = POLE_TLO;
				break;

			case POLE_PUNKT_STABILNY: 
				DodajPunktStabilny(TabDoX(k*10), TabDoY(w));
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
		tabPol[k] = tabPol[k - ktory] + ktory/10*(tabPol[k - ktory] - tabPol[k - ktory + 10]);
	}

}

void cPlansza::DodajPunktStabilny(float _x, float _y)
{
	cPunktStabilny* nowyPunkt = new cPunktStabilny(_x, _y, 0);
	tabPunktStab.push_back(nowyPunkt);
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



	// bohater

	glGenLists(LISTA_BOHATER);
	glNewList(LISTA_BOHATER, GL_COMPILE);

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
	SOIL_load_OGL_texture("tx\\palma1.png", SOIL_LOAD_AUTO, TEKSTURA_PALMA1, SOIL_FLAG_INVERT_Y);
//	SOIL_load_OGL_texture("tx\\trawa2.png", SOIL_LOAD_AUTO, TEKSTURA_TRAWA1, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\1tlo.png", SOIL_LOAD_AUTO, TEKSTURA_MAPA_TERENU, SOIL_FLAG_INVERT_Y);

//	SOIL_load_OGL_texture("tx\\Przemek.png", SOIL_LOAD_AUTO, 77, SOIL_FLAG_INVERT_Y);

	
	SOIL_load_OGL_texture("tx\\zamek1.png", SOIL_LOAD_AUTO, TEKSTURA_ZAMEK, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\wieza1.png", SOIL_LOAD_AUTO, TEKSTURA_WIEZA1, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\wieza2.png", SOIL_LOAD_AUTO, TEKSTURA_WIEZA2, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\wieza3.png", SOIL_LOAD_AUTO, TEKSTURA_WIEZA3, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\wieza4.png", SOIL_LOAD_AUTO, TEKSTURA_WIEZA4, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\wieza5.png", SOIL_LOAD_AUTO, TEKSTURA_WIEZA5, SOIL_FLAG_INVERT_Y);
}

void cPlansza::_KlawiszeSpecjalne(int key, int x, int y)
{
	float przesu = SZYBKOSC_PRZESUWANIA * kamera.zakres;

	switch(key)
	{
	case GLUT_KEY_UP:
		PrzesunKamere(0, przesu);
		break;	
	case GLUT_KEY_DOWN:
		PrzesunKamere(0, -przesu);
		break;
	case GLUT_KEY_LEFT:
		PrzesunKamere(przesu, 0);
		break;
	case GLUT_KEY_RIGHT:
		PrzesunKamere(-przesu, 0);
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




