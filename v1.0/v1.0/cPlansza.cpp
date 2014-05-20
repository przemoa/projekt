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
	kamera.xCel = 0;
	kamera.y = 0;
	kamera.yCel = 0;
	kamera.zakres = 50;
	kamera.zakresCel = 50;
	kamera.przesuwajx = 0;
	kamera.przesuwajy = 0;



	TworzTekstury();
	UtworzListy();

	for (int i = 0; i < ILOSC_CHMUR; i++)
	{
		sKOLOR kolor;
		kolor.b = 0.9;
		kolor.r = 1 - i/20.0;
		kolor.g = 1;
		tabChmur[i] = new cChmura(((rand()%2) ? TEKSTURA_CHMURA1 : TEKSTURA_CHMURA2), -400+100*i+rand()%30, 30+rand()%20, -12, kolor, 5+rand()%7, rand()%2*180-5+rand()%10, 10+rand()%15);
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
		PrzesunKamere(0, przesu);
		break;

	case 's':
		PrzesunKamere(0, -przesu);
		break;

	case 'a':
		PrzesunKamere(przesu, 0);
		break;

	case 'd':
		PrzesunKamere(-przesu, 0);
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
			float wspx = (x - rozmiarOkna.x / 2.0) / 30;
			float wspy = (y - rozmiarOkna.y / 2.0) / 30;
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
			case 0xD5:				 //- gracze

				pole = 0xFF;
				break;
			case 0xE8:				//- palma
				sKOLOR kolor;
				kolor.b = 0.9;
				kolor.r = 1;
				kolor.g = 1;
				{cPalma* nowaPalma = new cPalma(TEKSTURA_PALMA1, 5+rand()%4, -5+rand()%10, -300 + 0.4*k,-w*0.4, -0.1);
				tabPalm.push_back(nowaPalma);}
				pole = 0xFF;
				break;
			case 0x37:				//- punkt stabilny 
				DodajPunktStabilny(-300 + 0.4*k, -w*0.4);
				pole = 0xFF;
				
				break;
			case 0xF9:				//- skrzynka z nagrod¹ 1

				pole = 0xFF;
				break;
			case 0xFA:				//- skrzynka z nagrod¹ 2

				pole = 0xFF;
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
			if (tabPol[w][k] == 0x71)
			{
				tabPol[w][k] = 0x55;
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

	glGenLists(LISTA_PUNKT_STABILNY);
	glNewList(LISTA_PUNKT_STABILNY, GL_COMPILE);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 100; i++)
		{
			glVertex2f(sin(6.2832*i/100)*4, cos(6.2832*i/100)*4);
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
	
	SOIL_load_OGL_texture("tx\\Przemek.png", SOIL_LOAD_AUTO, 77, SOIL_FLAG_INVERT_Y);
}
