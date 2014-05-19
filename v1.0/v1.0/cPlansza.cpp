#include "cPlansza.h"
#include "naglowki.h"



cPlansza::cPlansza(void)
{
	rozmiarOkna.x = 800;
	rozmiarOkna.y = 600;
	rozmiarOkna.proporcja = (float) rozmiarOkna.x / rozmiarOkna.y;

	kamera.x = 0;
	kamera.xCel = 0;
	kamera.y = 0;
	kamera.yCel = 0;
	kamera.zakres = 50;
	kamera.zakresCel = 50;
	kamera.przesuwaj = 0;

	testowy = 0;
	testowy2 = 0;

	TworzTekstury();

	for (int i = 0; i < ILOSC_CHMUR; i++)
	{
		sKOLOR kolor;
		kolor.b = 0.9;
		kolor.r = 1 - i/20.0;
		kolor.g = 1;
		tabChmur[i] = new cChmura(((rand()%2) ? TEKSTURA_CHMURA1 : TEKSTURA_CHMURA2), -400+100*i+rand()%30, 30+rand()%20, -12, kolor, 5+rand()%7, rand()%2*180-5+rand()%10, 10+rand()%15);
	}
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
		if (kamera.przesuwaj)
		{

			kamera.x += kamera.przesuwaj * 0.01 * kamera.zakres;
			kamera.xCel += kamera.przesuwaj * 0.01 * kamera.zakres;
			OdswiezKamere();

			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_MYSZ_PRZESUN_X);
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

	if (kamera.przesuwaj == 0)
	{
		if (x < 70)
		{
			kamera.przesuwaj = -1;
			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_MYSZ_PRZESUN_X);
		}
		if (x > rozmiarOkna.x - 70)
		{
			kamera.przesuwaj = +1;
			glutTimerFunc(20, Dzialaj, TIMER_KAMERA_MYSZ_PRZESUN_X);
		}
	}
	else
	{
		if (x > 70 && x < rozmiarOkna.x - 70) kamera.przesuwaj = 0;
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



void cPlansza::TworzTekstury()
{
	SOIL_load_OGL_texture("C:\\Users\\Przemek\\Desktop\\tx\\chmura1.png", SOIL_LOAD_AUTO, TEKSTURA_CHMURA1, SOIL_FLAG_INVERT_Y);
	SOIL_load_OGL_texture("C:\\Users\\Przemek\\Desktop\\tx\\chmura2.png", SOIL_LOAD_AUTO, TEKSTURA_CHMURA2, SOIL_FLAG_INVERT_Y);

}
