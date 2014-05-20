#include "cPlansza.h"
#include "naglowki.h"



cPlansza::cPlansza(void)
{
	
	testowy = 0;
	testowy2 = 0;
	//licznikPunktow = 0;

	rozmiarOkna.x = 800;
	rozmiarOkna.y = 600;
	rozmiarOkna.proporcja = (float) rozmiarOkna.x / rozmiarOkna.y;

	kamera.x = 0;
	kamera.xCel = -190;
	kamera.y = 0;
	kamera.yCel = -44;
	kamera.zakres = 300;
	kamera.zakresCel = 75;
	kamera.przesuwajx = 0;
	kamera.przesuwajy = 0;
	glutTimerFunc(20, Dzialaj, TIMER_KAMERA_PRZESUN_X);
	glutTimerFunc(20, Dzialaj, TIMER_KAMERA_PRZESUN_Y);
	glutTimerFunc(20, Dzialaj, TIMER_KAMERA_SCROLL);

	wybranyBohater = 0;


	TworzTekstury();
	UtworzListy();

	for (int i = 0; i < ILOSC_CHMUR; i++)
	{
		sKOLOR kolor;
		kolor.b = 0.9;
		kolor.r = 1 - i/20.0;
		kolor.g = 1;
		tabChmur[i] = new cChmura(((rand()%2) ? TEKSTURA_CHMURA1 : TEKSTURA_CHMURA2), -400+100*i+rand()%30, -30+rand()%10, -12, kolor, 5+rand()%7, rand()%2*180-5+rand()%10, 10+rand()%15);
	}

	// wczytaj plansze
	for (int w = 0; w < 400; w++)
	{
		for (int k = 0; k < 1500; k++)
		{
			tabPol[w][k] = 0xFF;
		}
	}
	WczytajTeren();

}

cPlansza::~cPlansza(void)
{

}

void cPlansza::RysujSzescian()
{
	glEnable(GL_DEPTH_TEST);
	float rozm = 10;
	glBegin(GL_LINE_LOOP);
			glVertex3f(rozm, rozm, 0);
			glVertex3f(-rozm, rozm, 0);
			glVertex3f(-rozm, -rozm, 0);
			glVertex3f(rozm, -rozm, 0);
		glEnd();

		glColor3f(1, 0, 0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(rozm, rozm, -5);
			glVertex3f(-rozm, rozm, -5);
			glVertex3f(-rozm, -rozm, -5);
			glVertex3f(rozm, -rozm, -5);
		glEnd();


		glColor3f(0, 1, 0);
		glBegin(GL_LINES);
		glVertex3f(rozm, rozm, 0);
			glVertex3f(rozm, rozm, -5);

			glVertex3f(-rozm, rozm, 0);
			glVertex3f(-rozm, rozm, -5);

			glVertex3f(-rozm, -rozm, 0);
			glVertex3f(-rozm, -rozm, -5);

			glVertex3f(rozm, -rozm, 0);
			glVertex3f(rozm, -rozm, -5);
		glEnd();
	glDisable(GL_DEPTH_TEST);
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
		//for (int i = 0; i < tabBohaterow.size(); i++)
		{
			tabBohaterow[0]->Opadaj();
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
		tabBohaterow[wybranyBohater]->Ruszaj(-KROK_BOHATERA*10);
		break;

	case 'd':
		tabBohaterow[wybranyBohater]->Ruszaj(KROK_BOHATERA*10);
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
	FILE* odczytTerenu = fopen("tx\\1.bmp", "r");
	BYTE tablicaPikseli[1500*400];
	fread(tablicaPikseli, 1, 1500*400, odczytTerenu);
	fclose(odczytTerenu);

	for (int w = 0; w < 400; w++)				// przepisz z wektra do tabeli pól i wykonaje pola specjalne
	{
		for (int k = 0; k < 1500; k++)
		{
			unsigned char pole = tablicaPikseli[(399-w)*1500 + k];
			switch (pole)
			{
			case POLE_GRACZ:
				{
					cBohater* nowyBohater = new cBohater(TabDoX(k), TabDoY(w));
					tabBohaterow.push_back(nowyBohater);
				}
				pole = POLE_TLO;
				break;

			case POLE_PALMA:
				sKOLOR kolor;
				kolor.b = 0.9;
				kolor.r = 1;
				kolor.g = 1;
				{cPalma* nowaPalma = new cPalma(TEKSTURA_PALMA1, 5+rand()%4, -5+rand()%10, TabDoX(k), TabDoY(w), -0.1);
				tabPalm.push_back(nowaPalma);}
				pole = POLE_TLO;
				break;

			case POLE_PUNKT_STABILNY: 
				DodajPunktStabilny(TabDoX(k), TabDoY(w));
				pole = tabPol[w][k-1];
				
				break;
			case POLE_SKRZYNKA_Z_NAGRODA_1:

				pole = POLE_TLO;
				break;
			case POLE_SKRZYNKA_Z_NAGRODA_2:

				pole = POLE_TLO;
				break;
			}

			tabPol[w][k] = pole;
		}
	}


	for (int k = 0; k < 1500; k++)
	{
		int ileObsiac = 20;

		for (int w = 0; w < 400; w++)
		{
			if (!ileObsiac) break;
			if (tabPol[w][k] == POLE_ZIEMIA)
			{
				tabPol[w][k] = POLE_TRAWA;
				ileObsiac--;
			}
		}
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

}


void cPlansza::TworzTekstury()
{
	SOIL_load_OGL_texture("tx\\chmura1.png", SOIL_LOAD_AUTO, TEKSTURA_CHMURA1, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\chmura2.png", SOIL_LOAD_AUTO, TEKSTURA_CHMURA2, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\palma1.png", SOIL_LOAD_AUTO, TEKSTURA_PALMA1, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\trawa2.png", SOIL_LOAD_AUTO, TEKSTURA_TRAWA1, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("tx\\trawa2.png", SOIL_LOAD_AUTO, TEKSTURA_BOHATER, SOIL_FLAG_INVERT_Y);

	SOIL_load_OGL_texture("tx\\Przemek.png", SOIL_LOAD_AUTO, 77, SOIL_FLAG_INVERT_Y);
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
	return (-300 + 0.4*k);
}

float cPlansza::TabDoY(int w)
{
	return (-w*0.4);
}

int cPlansza::XDoTab(float x)
{
	return ((x + 300) / 0.4);
}

int cPlansza::YDoTab(float y)
{
	return (-y / 0.4);
}