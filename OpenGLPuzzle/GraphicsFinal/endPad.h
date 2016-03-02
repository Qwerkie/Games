class EndPad
{
public:
	double endX = 0.0;
	double endZ = 0.0;
};

EndPad endPad;

void drawEndPad()
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, 0.1);
	glTranslatef(endPad.endX, -endPad.endZ, 0);

	//circle
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float degInRad = i*DEG2RAD;
		glVertex2f(cos(degInRad) * 4, sin(degInRad) * 4);
	}
	glEnd();

	//letter H
	glTranslatef(-1.5, 0, 0);
	glRectf(-0.5, 2.5, 0.5, -2.5);
	glTranslatef(3, 0, 0);
	glRectf(-0.5, 2.5, 0.5, -2.5);
	glTranslatef(-1.5, 0, 0);
	glRectf(-2, 0.5, 2, -0.5);
	glTranslatef(1.5, 0, 0);
	glTranslatef(-3, 0, 0);
	glTranslatef(1.5, 0, 0);
	glPopMatrix();


	//base
	glColor3f(0.8, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	glScalef(1, 1, 0.1);
	glutSolidCube(10);
	glScalef(1, 1, 10);
	glTranslatef(0, 0, 0.5);
	glPopMatrix();

	//edges
	//top edge
	glColor3f(0.3, 0.0, 0);
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glScalef(1.1, 0.1, 0.2);
	glutSolidCube(10);
	glScalef(0.909, 10, 5);
	glTranslatef(0, -5, 0);
	glPopMatrix();

	//bottom edge
	glColor3f(0.3, 0, 0);
	glPushMatrix();
	glTranslatef(0, -5, 0);
	glScalef(1.1, 0.1, 0.2);
	glutSolidCube(10);
	glScalef(0.909, 10, 5);
	glTranslatef(0, 5, 0);
	glPopMatrix();

	//left edge
	glColor3f(0.3, 0, 0);
	glPushMatrix();
	glTranslatef(-5, 0, 0);
	glScalef(0.1, 1.1, 0.2);
	glutSolidCube(10);
	glScalef(0.909, 10, 5);
	glTranslatef(5, 0, 0);
	glPopMatrix();

	//right edge
	glColor3f(0.3, 0, 0);
	glPushMatrix();
	glTranslatef(5, 0, 0);
	glScalef(0.1, 1.1, 0.2);
	glutSolidCube(10);
	glScalef(0.909, 10, 5);
	glTranslatef(-5, 0, 0);
	glPopMatrix();
	glTranslatef(100, 0, 0);
	glTranslatef(0, 0, -0.1);
	glRotatef(90, 1, 0, 0);

	glPopMatrix();
	glPopMatrix();
}

void setEndParams(double endX, double endZ)
{
	if (endPad.endZ == 0)
	{
		endPad.endZ = endZ;

	}
	if (endPad.endX == 0)
	{
		endPad.endX = endX;
	}
}