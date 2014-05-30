#include "cPlansza.h"
#include "naglowki.h"



void cPlansza::_Przerysuj(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);

	glPushMatrix();
	glEnable (GL_BLEND);
	
		RysujTlo();
		



		//RysujPodloze();

		//glColor3f(0,1,0);
		//glBegin(GL_POLYGON);
		//	for (int i = 0; i < licznikPunktow; i++)
		//	{
		//		glVertex2f(tabPunktow[i][0], tabPunktow[i][1]);
		//	}
		//glEnd();

		//glPushMatrix();
		//	RysujSzescian();
		//	glTranslatef(32, -5, 0);
		//	RysujSzescian();
		//	glTranslatef(-89, -15, 0);
		//	RysujSzescian();
		//glPopMatrix();

		//glPushMatrix();
		//	glColor4f(1, 0.6, 0.6, 0.5);
		//	glTranslatef(testowy, testowy2, 0);
		//	glBegin(GL_POLYGON);
		//		glVertex2f(1,1);
		//		glVertex2f(-1,1);
		//		glVertex2f(-1,-1);
		//		glVertex2f(1,-1);
		//	glEnd();
		//glPopMatrix();


		for (int i = 0; i < ILOSC_CHMUR; i++)
		{
			tabChmur[i]->Rysuj();
		}

		for (int i = 0; i < tabPalm.size(); i++)
		{
			tabPalm[i]->Rysuj();
		}

		RysujTeren();
		

	// napis przemek
			//glPushMatrix();
			//	glBindTexture(GL_TEXTURE_2D, 77);
			//	glTranslatef(-250,-240,0);
			//	glEnable(GL_TEXTURE_2D);
			//	glColor4f(1, 1, 1, 0.7);
			//	glBegin(GL_POLYGON);
			//		for (int i = 0; i < 100; i++)
			//		{
			//			glTexCoord2f(i/99.0, 0.0); glVertex3f(i, 0.005*i*i, -0.1*i);
			//		}
			//		for (int i = 99; i >= 0; i--)
			//		{
			//			glTexCoord2f(i/99.0, 1); glVertex3f(i, 0.005*i*i+95, -0.1*i);
			//		}
			//	glEnd();
			//	glDisable(GL_TEXTURE_2D);
			//glPopMatrix();

		for (int i = 0; i < tabGraczy.size(); i++)
		{
			tabGraczy[i]->Rysuj();
		}

		for (int i = 0; i < tabPunktStab.size(); i++)
		{
			tabPunktStab[i]->Rysuj();
		}


		RysujRamkeOpisu();

	glPopMatrix();
	glutSwapBuffers();
}


void cPlansza::RysujTlo()
{
	glBegin(GL_POLYGON);
		glColor3f(0, 0, 0.3);
		glVertex2f(3*KAMERA_MAX_POLOZENIE_X, 5*KAMERA_MAX_POLOZENIE_Y / 2.0);
		glVertex2f(-3*KAMERA_MAX_POLOZENIE_X, 5*KAMERA_MAX_POLOZENIE_Y / 2.0);
		glColor3f(0, 0, 0.55);
		glVertex2f(-3*KAMERA_MAX_POLOZENIE_X, 2*KAMERA_MAX_POLOZENIE_Y / 2.0);
		glVertex2f(3*KAMERA_MAX_POLOZENIE_X, 2*KAMERA_MAX_POLOZENIE_Y / 2.0);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0, 0, 0.55);
		glVertex2f(3*KAMERA_MAX_POLOZENIE_X, 2*KAMERA_MAX_POLOZENIE_Y / 2.0);
		glVertex2f(-3*KAMERA_MAX_POLOZENIE_X, 2*KAMERA_MAX_POLOZENIE_Y / 2.0);
		glColor3f(0.25, 0.85, 1);
		glVertex2f(-3*KAMERA_MAX_POLOZENIE_X, 2*KAMERA_MIN_POLOZENIE_Y);
		glVertex2f(3*KAMERA_MAX_POLOZENIE_X, 2*KAMERA_MIN_POLOZENIE_Y);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0.25, 0.85, 1);
		glVertex2f(3*KAMERA_MAX_POLOZENIE_X, 2*KAMERA_MIN_POLOZENIE_Y);
		glVertex2f(-3*KAMERA_MAX_POLOZENIE_X, 2*KAMERA_MIN_POLOZENIE_Y);
		glColor3f(0.39, 0.95, 1);
		glVertex2f(-3*KAMERA_MAX_POLOZENIE_X, 12*KAMERA_MIN_POLOZENIE_Y);
		glVertex2f(3*KAMERA_MAX_POLOZENIE_X, 12*KAMERA_MIN_POLOZENIE_Y);
		
	glEnd();
}

void cPlansza::RysujPodloze()
{

	glBegin(GL_POLYGON);
		glColor3f(0.3, 0.8, 0);
		glVertex2f(500, -30);
		glVertex2f(-500, -30);
		glColor3f(0.2, 0.5, 0.05);
		glVertex2f(-500, -50);
		glVertex2f(500, -50);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(500, -50);
		glVertex2f(-500, -50);
		glColor3f(0.1, 0.15, 0);
		glVertex2f(-500, -300);
		glVertex2f(500, -300);
	glEnd();

}

void cPlansza::RysujTeren()
{
	
	glColor4f(0, 0.7, 0, 0.5);
	glBegin(GL_LINES);
	
	int ostatniTypPola = -1;

		for (int i = 0; i < 50000; i+= 10)		// tylko co 10
		{
			if (tabTypowPol[i] != -7777 && tabTypowPol[i] != ostatniTypPola)
			{
				ostatniTypPola = tabTypowPol[i];
				switch(ostatniTypPola)
				{
				case POLE_WODA:
					glColor4f(0, 0, 1, 0.8);
					break;
				case POLE_ZIEMIA:
					glColor4f(0.2, 0.1, 0.05, 0.8);
					break;
				case POLE_TRAWA:
					glColor4f(0, 1, 0, 0.8);
					break;

				}
			}

			glVertex3f(TabDoX(i), tabPol[i], 0);
			glVertex3f(TabDoX(i), tabPol[i], -2);
		}
	glEnd();

	ostatniTypPola = -1;
	glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 50000; i+= 20)
		{
			if (tabTypowPol[i] != -7777 && tabTypowPol[i] != ostatniTypPola)
			{
				ostatniTypPola = tabTypowPol[i];
				switch(ostatniTypPola)
				{
				case POLE_WODA:
					glColor4f(0, 0, 1, 0.8);
					break;
				case POLE_ZIEMIA:
					glColor4f(0.2, 0.1, 0.05, 0.8);
					break;
				case POLE_TRAWA:
					glColor4f(0, 1, 0, 0.8);
					break;

				}
			}

			glVertex3f(TabDoX(i), tabPol[i], -2);
		}
	glEnd();
	

	


	glPushMatrix();
		glColor4f(1, 1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, TEKSTURA_MAPA_TERENU);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(-1000, -170);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(1000, -170);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(1000, 170);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(-1000, 170);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();



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


void cPlansza::DrawString(int x, int y, const char * string)
{
    //DrawString(kamera.x, kamera.y, "tttsefaeafwe");
	// po³o¿enie napisu
    glRasterPos2i( x, y );
    
    // wyœwietlenie napisu
    int len = strlen( string );
    for (int i = 0; i < len; i++)
         glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
    
}

void cPlansza::RysujRamkeOpisu()
{
	

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glOrtho(0, 90, 0, 90, -10, 10);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();

			glBegin(GL_POLYGON);			// RAMKA
				glColor4f(0, 0, 0.15, 1);
				glVertex2f(37,0);

				glColor4f(0, 0, 0.15, 0);
				glVertex2f(39,0);

				glColor4f(0.15, 0, 0, 0);
				glVertex2f(39, 32);

				glColor4f(0.15, 0, 0, 1);
				glVertex2f(37, 30);
			glEnd();


			glBegin(GL_POLYGON);
				glColor4f(0.15, 0.02, 0.02, 1);
				glVertex2f(37, 30);

				glColor4f(0.15, 0.02, 0.02, 0);
				glVertex2f(39, 32);

				glColor4f(0.02, 0.02, 0.15, 0);
				glVertex2f(0,32);

				glColor4f(0.02, 0.02, 0.15, 1);
				glVertex2f(0,30);
			glEnd();


			glBegin(GL_POLYGON);
				glColor4f(0.0, 0.15, 0.0, 1);
				glVertex2f(0,0);

				glColor4f(0.02, 0.02, 0.15, 1);
				glVertex2f(37,0);

				glColor4f(0.15, 0.02, 0.02, 1);
				glVertex2f(37, 30);

				glColor4f(0.02, 0.02, 0.15, 1);
				glVertex2f(0,30);
			glEnd();
				


			glScalef(23, 1, 1);
			glColor3f(0.1, 0.5, 0.8);
			DrawString(1, 29, "ppp\npp");



		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}