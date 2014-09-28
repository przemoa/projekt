#include "naglowki.h"
#include "cPlansza.h"
#include "cJednostka.h"

cPlansza* Plansza = 0;
int cJednostka::aktualneId = 0;




void Przerysuj(void)
{	

	Plansza->_Przerysuj();
	
}
void Dzialaj(int value)
{
	Plansza->_Dzialaj(value);
}
void idle(void)
{
	Plansza->_Idle();
}
void Klawisz(unsigned char key, int x, int y)
{
	Plansza->_Klawiatura(key, x, y);
}
void ZmienRozmiar(int width, int height)
{
	Plansza->_ZmianaRozmiaruOkna(width, height);
}
void Mysz(int button, int state, int x, int y)
{
	Plansza->_MyszKlawisz(button, state, x, y);

}
void RuchMyszy(int x,int y)
{

	Plansza->_MyszRuch(x, y);
}

void KlawiszeSpecjalne(int key, int x, int y)
{
	Plansza->_KlawiszeSpecjalne(key, x, y);
}








bool dodawanieBelki = 0;
float a = -10000;
float b = -10000;
float c = -10000;
float d = -10000;

int main(int argc, char **argv)
{
	srand(time(NULL));

	glutInitWindowSize (1000, 600);
	glutInitWindowPosition (11, 11);
	glutInit (&argc, argv);	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow ("Program");

	

	glClearColor(1,1,1,1);

	
	
	glutDisplayFunc(Przerysuj);
	glutKeyboardFunc(Klawisz);
	glutReshapeFunc(ZmienRozmiar);
	glutMouseFunc(Mysz);
	glutPassiveMotionFunc(RuchMyszy);
	glutIdleFunc(idle);
	glutSpecialFunc(KlawiszeSpecjalne);


	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	//glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	
	glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	Plansza = new cPlansza();
	  
	
	glutTimerFunc(20, Dzialaj, TIMER_ANIMACJI_TLA);
	glutTimerFunc(2000, Dzialaj, TIMER_CO_DWASEKUNDOWY);
	glutTimerFunc(20, Dzialaj, TIMER_20);
	glutTimerFunc(50, Dzialaj, TIMER_50);

	glLineWidth(2);


	glutMainLoop();
	return EXIT_SUCCESS;
}