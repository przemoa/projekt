#include "cBelka.h"


cBelka::cBelka(void)
{
}

cBelka::cBelka(float xp, float yp, float xk, float yk, bool _animuj)
{
	animuj = _animuj;
	x_poczatku = xp;
	x_konca = xk;
	y_poczatku = yp;
	y_konca = yk;
	kolor_r = 0.6;
	kolor_g = 0.3;
	kolor_b = 0;
	z = 0;
	grubosc = 0.4;
}

cBelka::~cBelka(void)
{
}

void cBelka::Rysuj()
{
	glPushMatrix();
	glTranslatef(0.5 * (x_poczatku + x_konca), 0.5 * (y_poczatku + y_konca), z);
	glRotatef(180 / 3.1416 * atan2((y_konca - y_poczatku),(x_konca - x_poczatku)), 0, 0, 1);
	glColor3f(kolor_r, kolor_g, kolor_b);

	glBegin(GL_POLYGON);
		glVertex3f(-0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),grubosc / 2, 0);
		glVertex3f(-0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),grubosc / 2, -grubosc);
		glVertex3f(-0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),-grubosc / 2, -grubosc);
		glVertex3f(-0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),-grubosc / 2, 0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),grubosc / 2, 0);
		glVertex3f(0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),grubosc / 2, -grubosc);
		glVertex3f(0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),-grubosc / 2, -grubosc);
		glVertex3f(0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),-grubosc / 2, 0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(-0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),grubosc / 2, -grubosc);
		glVertex3f(0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),grubosc / 2, -grubosc);
		glVertex3f(0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),-grubosc / 2, -grubosc);
		glVertex3f(-0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),-grubosc / 2, -grubosc);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(-0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),grubosc / 2, -grubosc);
		glVertex3f(-0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),grubosc / 2, 0);
		glVertex3f(0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),grubosc / 2, 0);
		glVertex3f(0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),grubosc / 2, -grubosc);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(-0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),-grubosc / 2, -grubosc);
		glVertex3f(-0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),-grubosc / 2, 0);
		glVertex3f(0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),-grubosc / 2, 0);
		glVertex3f(0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),-grubosc / 2, -grubosc);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),grubosc / 2, 0);
		glVertex3f(0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),grubosc / 2, 0);
		glVertex3f(0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),-grubosc / 2, 0);
		glVertex3f(-0.5 * sqrt(pow((x_poczatku - x_konca), 2) + pow((y_poczatku - y_konca), 2)),-grubosc / 2, 0);
	glEnd();

	glPopMatrix();
}


