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



		glPushMatrix();
			RysujSzescian();
			glTranslatef(32, -5, 0);
			RysujSzescian();
			glTranslatef(-89, -15, 0);
			RysujSzescian();
		glPopMatrix();

		glPushMatrix();
			glColor4f(1, 0.6, 0.6, 0.5);
			glTranslatef(testowy, testowy2, 0);
			glBegin(GL_POLYGON);
				glVertex2f(1,1);
				glVertex2f(-1,1);
				glVertex2f(-1,-1);
				glVertex2f(1,-1);
			glEnd();
		glPopMatrix();

		for (int i = 0; i < ILOSC_CHMUR; i++)
		{
			tabChmur[i]->Rysuj();
		}

		for (int i = 0; i < tabPalm.size(); i++)
		{
			tabPalm[i]->Rysuj();
		}

		

		RysujPola();

		
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, 77);
				glTranslatef(-250,-240,0);
				glEnable(GL_TEXTURE_2D);
				glColor4f(1, 1, 1, 0.7);
				glBegin(GL_POLYGON);
					for (int i = 0; i < 100; i++)
					{
						glTexCoord2f(i/99.0, 0.0); glVertex3f(i, 0.005*i*i, -0.1*i);
					}
					for (int i = 99; i >= 0; i--)
					{
						glTexCoord2f(i/99.0, 1); glVertex3f(i, 0.005*i*i+95, -0.1*i);
					}
				glEnd();
				glDisable(GL_TEXTURE_2D);
			glPopMatrix();


		for (int i = 0; i < tabPunktStab.size(); i++)
		{
			tabPunktStab[i]->Rysuj();
		}

		for (int i = 0; i < tabBohaterow.size(); i++)
		{
			tabBohaterow[i]->Rysuj();
		}
	

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

void cPlansza::RysujPola()
{
	glPushMatrix();
		glTranslatef(-300.0, 0, 0);
		
		

		for (int w = 0; w < 400; w++)
		{
			glTranslatef(0, -0.4, 0);
			glPushMatrix();
			glBegin(GL_QUADS);
				for (int k = 0; k < 1500; k++)
				{
					//glTranslatef(0.4, 0, 0);
					if (tabPol[w][k] == 0xFF) continue; 
					if (tabPol[w][k] == 'P') continue;
					
					switch (tabPol[w][k])
					{
					case 'P':
						glColor3f(0.3, 0.3, 0.3);
						break;
					case 0x71:
						glColor4f(0.6, 0.4, 0.2, 0.5);
						break;
					case 0x55:
						glColor3f(0.2, 0.8, 0.2);
						break;
					}
						//glVertex2f(0, 0);
						//glVertex2f(0.4, 0);
						//glVertex2f(0.4, 0.4);
						//glVertex2f(0, 0.4);
						glVertex2f(0 + 0.4*k, 0);
						glVertex2f(0.4 + 0.4*k, 0);
						glVertex2f(0.4 + 0.4*k, 0.4);
						glVertex2f(0 + 0.4*k, 0.4);
				}
			glEnd();
			glPopMatrix();
		}
		
	glPopMatrix();
}