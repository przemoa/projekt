#include "cPlansza.h"
#include "naglowki.h"



void cPlansza::_Przerysuj(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);

	glPushMatrix();
	glEnable (GL_BLEND);
	
		RysujTloNiebo();
		



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


void cPlansza::RysujTloNiebo()
{

	glBegin(GL_POLYGON);
		glColor3f(0, 0, 0);
		glVertex2f(3*KAMERA_MAX_POLOZENIE_X, 15*KAMERA_MAX_POLOZENIE_Y / 2.0);
		glVertex2f(-3*KAMERA_MAX_POLOZENIE_X, 15*KAMERA_MAX_POLOZENIE_Y / 2.0);
		glColor3f(0, 0, 0.3);
		glVertex2f(-3*KAMERA_MAX_POLOZENIE_X, 5*KAMERA_MAX_POLOZENIE_Y / 2.0);
		glVertex2f(3*KAMERA_MAX_POLOZENIE_X, 5*KAMERA_MAX_POLOZENIE_Y / 2.0);
	glEnd();

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

		for (int i = 0; i < 50000; i+= 30)		// tylko co 10 linia poprzeczna
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
		for (int i = 0; i < 50000; i+= 30)
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
	
	
	// reszta podloza ziemi (brazowe poza tekstura)
	//lewa
	glBegin(GL_QUADS);			
		glColor4f(0, 0, 0, 1);
		glVertex2f(-1000, 61.5);
		glVertex2f(-2000, 61.5);
		glVertex2f(-2000, 56);
		glVertex2f(-1000, 56);
	glEnd();	
	
	glBegin(GL_QUADS);
		glColor4f(0.04, 0.02, 0, 1);
		glVertex2f(-1000, 56);
		glVertex2f(-2000, 56);
		glColor4f(0.25, 0.125, 0, 1);
		glVertex2f(-2000, 49);
		glVertex2f(-1000, 49);
	glEnd();

	glBegin(GL_QUADS);
		glVertex2f(-1000, 49);
		glVertex2f(-2000, 49);
		glColor4f(0.216, 0.108, 0, 1);
		glVertex2f(-2000, 44);
		glVertex2f(-1000, 44);
	glEnd();

	glBegin(GL_QUADS);
		glColor4f(0.216, 0.108, 0, 1);
		glVertex2f(-1000, 44);
		glVertex2f(-2000, 44);
		glColor4f(0.22, 0.11, 0, 1);
		glVertex2f(-2000, -400);
		glVertex2f(-1000, -400);
	glEnd();

	//prawa
	glBegin(GL_QUADS);			
		glColor4f(0, 0, 0, 1);
		glVertex2f(1000, 57.5);
		glVertex2f(2000, 57.5);
		glVertex2f(2000, 52);
		glVertex2f(1000, 52);
	glEnd();	
	
	glBegin(GL_QUADS);
		glColor4f(0.04, 0.02, 0, 1);
		glVertex2f(1000, 52);
		glVertex2f(2000, 52);
		glColor4f(0.25, 0.125, 0, 1);
		glVertex2f(2000, 45);
		glVertex2f(1000, 45);
	glEnd();

	glBegin(GL_QUADS);
		glVertex2f(1000, 45);
		glVertex2f(2000, 45);
		glColor4f(0.216, 0.108, 0, 1);
		glVertex2f(2000, 42);
		glVertex2f(1000, 42);
	glEnd();

	glBegin(GL_QUADS);
		glColor4f(0.216, 0.108, 0, 1);
		glVertex2f(1000, 42);
		glVertex2f(2000, 42);
		glColor4f(0.22, 0.11, 0, 1);
		glVertex2f(2000, -400);
		glVertex2f(1000, -400);
	glEnd();

	glBegin(GL_QUADS);				// dolny proatokat ziemi
		glColor4f(0, 0, 0, 1);
		glVertex2f(-2000, -570);
		glVertex2f(2000, -570);
		glColor4f(0.22, 0.11, 0, 1);
		glVertex2f(2000, -150);
		glVertex2f(-2000, -150);
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


void cPlansza::DrawString(float x, float y, const unsigned char * string, float skala)
{
	
	glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(x, y, 0);
		glScalef(skala/1000, skala/1000, skala/1000);
		glPushMatrix();
			

			for(const unsigned char* p = string; *p; p++)
			{
				if (*p == 10)
				{
					glPopMatrix();
					glTranslatef(0, -180, 0);
					glPushMatrix();
					continue;
				}
				glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
			}
		glPopMatrix();



	glPopMatrix();




	//glRasterPos2i( x, y );
	//glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, string);

    //int len = strlen( string );
    //for (int i = 0; i < len; i++)
    //     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    
}

void cPlansza::RysujRamkeOpisu()
{


	glLineWidth(2);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glOrtho(0, 75*rozmiarOkna.proporcja, 0, 75, -10, 10);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();

			if (ramkaOpisu.czyWidoczna)
			{
				// TLO RAMKI
																																	glBegin(GL_POLYGON);			
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
				// KRESKI ROZDZIELCZE
																glColor4f(0.7, 0.7, 0.7, 0.5);
			glBegin(GL_POLYGON);
				glVertex2f(23, 4);
				glVertex2f(23, 21.5);
				glVertex2f(23.5, 22);
				glVertex2f(23.5, 3);
			glEnd();

			glBegin(GL_POLYGON);
				glVertex2f(2, 22);
				glVertex2f(22, 22);
				glVertex2f(23, 22.5);
				glVertex2f(3, 22.5);
			glEnd();
				// IKONKA jednostki
						
			glColor3f(0,0,0.4);		// ramka
			glBegin(GL_QUADS);
				glVertex2f(24.5, 18);
				glVertex2f(36, 18);
				glVertex2f(36,  18.5);
				glVertex2f(24.5,  18.5);

				glVertex2f(35.5, 18.5);
				glVertex2f(36, 18.5);
				glVertex2f(36,  29.5);
				glVertex2f(35.5,  29.5);

				glVertex2f(35.5, 29);
				glVertex2f(35.5, 29.5);
				glVertex2f(24.5,  29.5);
				glVertex2f(24.5,  29);

				glVertex2f(24.5, 29.5);
				glVertex2f(24.5, 18);
				glVertex2f(25,  18);
				glVertex2f(25,  29.5);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, ramkaOpisu.ikona);			
			glEnable(GL_TEXTURE_2D);
			glColor4f(1, 1, 1, 0.9);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex2f(25, 18.5);
				glTexCoord2f(1.0f, 0.0f); glVertex2f(35.5, 18.5);
				glTexCoord2f(1.0f, 1.0f); glVertex2f(35.5,  29);
				glTexCoord2f(0.0f, 1.0f); glVertex2f(25,  29);
			glEnd();
			glDisable(GL_TEXTURE_2D);
				// IKONA menu
				if (ramkaOpisu.rodzajMenu && ramkaOpisu.rodzajMenu != TEKSTURA_MENU_BUDOWA_WIEZY)
				{
					glBindTexture(GL_TEXTURE_2D, ramkaOpisu.rodzajMenu);			
					glEnable(GL_TEXTURE_2D);
					glColor4f(1, 1, 1, 0.9);
					glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex2f(25, 3);
						glTexCoord2f(1.0f, 0.0f); glVertex2f(36, 3);
						glTexCoord2f(1.0f, 1.0f); glVertex2f(36,  14);
						glTexCoord2f(0.0f, 1.0f); glVertex2f(25,  14);
					glEnd();
					glDisable(GL_TEXTURE_2D);
				}
				if (ramkaOpisu.rodzajMenu == TEKSTURA_MENU_BUDOWA_WIEZY)
				{
					glBindTexture(GL_TEXTURE_2D, ramkaOpisu.rodzajMenu);			
					glEnable(GL_TEXTURE_2D);
					glColor4f(1, 1, 1, 0.9);
					glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex2f(25, 3);
						glTexCoord2f(1.0f, 0.0f); glVertex2f(48, 3);
						glTexCoord2f(1.0f, 1.0f); glVertex2f(48,  14);
						glTexCoord2f(0.0f, 1.0f); glVertex2f(25,  14);
					glEnd();
					glDisable(GL_TEXTURE_2D);
				}




				// PASEK ZYCIA
				glPushMatrix();
					glTranslatef(24.5, 17, 0);
					float rozmiar = 6;
					glColor3f(0.15, 0.15, 0.15);
					glBegin(GL_POLYGON);
						glVertex2f(0, -0.1*rozmiar);
						glVertex2f( rozmiar*2, -0.1*rozmiar);
						glVertex2f( rozmiar*2,  0.1*rozmiar);
						glVertex2f(0,  0.1*rozmiar);
					glEnd();
		
					glColor3f(1-Plansza->ramkaOpisu.poziomZycia/100, Plansza->ramkaOpisu.poziomZycia/100, 0.0);
					glBegin(GL_POLYGON);
						glVertex2f(0.05*rozmiar, -0.08*rozmiar);
						glVertex2f( rozmiar*1.95*Plansza->ramkaOpisu.poziomZycia/100, -0.08*rozmiar);
						glVertex2f( rozmiar*1.95*Plansza->ramkaOpisu.poziomZycia/100,  0.08*rozmiar);
						glVertex2f(0.05*rozmiar,  0.08*rozmiar);
					glEnd();
				glPopMatrix();

				// NAPISY
				glColor3f(0.1, 0.5, 0.8);

				glColor4f(0.7, 0.7, 0.9, 0.7);
				DrawString(3, 25.5, (unsigned char*) Plansza->ramkaOpisu.nazwa.c_str(), 18);

				glColor4f(0.4, 0.4, 0.9, 0.7);
				glLineWidth(1);
				DrawString(2, 19, (unsigned char*) Plansza->ramkaOpisu.opis.c_str(), 12);

				glColor4f(0.9, 0.4, 0.4, 0.7);
				DrawString(2, 2, (const unsigned char*) (Plansza->ramkaOpisu.tekstId), 8);
			}

			glColor4f(0.9, 0.2, 0.2, 0.9);
			if(ramkaOpisu.tekstPomocy[0]) 
			{
				DrawString(75 * (mysz.x / (float) rozmiarOkna.x) * rozmiarOkna.proporcja, 75 - 75 * mysz.y / (float) rozmiarOkna.y,
							(const unsigned char*) ramkaOpisu.tekstPomocy, 25);
				DrawString(75 * (mysz.x / (float) rozmiarOkna.x) * rozmiarOkna.proporcja+0.1, 75 - 75 * mysz.y / (float) rozmiarOkna.y,
							(const unsigned char*) ramkaOpisu.tekstPomocy, 25);
			}


			// ile zlota
	
			glBindTexture(GL_TEXTURE_2D, TEKSTURA_MONETA);			
			glEnable(GL_TEXTURE_2D);
			glColor4f(1, 1, 1, 1);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex2f(2, 69);
				glTexCoord2f(1.0f, 0.0f); glVertex2f(6, 69);
				glTexCoord2f(1.0f, 1.0f); glVertex2f(6,  74);
				glTexCoord2f(0.0f, 1.0f); glVertex2f(2,  74);
			glEnd();
			glDisable(GL_TEXTURE_2D);

			glColor4f(1, 1, 0.3, 1);
			glLineWidth(2);
			DrawString(8, 71, (unsigned char*) tabGraczy[wybranyGracz]->napisZloto, 16);


			glLineWidth(2);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}