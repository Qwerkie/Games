class StartPad
{
public:
	double startX = 0.0;
	double startZ = 0.0;
};

StartPad startPad;
const float DEG2RAD = 3.14159 / 180;

void drawStartPad()
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, 0.1);
	glTranslatef(startPad.startX, -startPad.startZ, 0);

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
	glColor3f(0.5, 0.8, 0.5);
	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	glScalef(1, 1, 0.1);
	glutSolidCube(10);
	glScalef(1, 1, 10);
	glTranslatef(0, 0, 0.5);
	glPopMatrix();

	//edges
	//top edge
	glColor3f(0, 0.3, 0);
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glScalef(1.1, 0.1, 0.2);
	glutSolidCube(10);
	glScalef(0.909, 10, 5);
	glTranslatef(0, -5, 0);
	glPopMatrix();

	//bottom edge
	glColor3f(0, 0.3, 0);
	glPushMatrix();
	glTranslatef(0, -5, 0);
	glScalef(1.1, 0.1, 0.2);
	glutSolidCube(10);
	glScalef(0.909, 10, 5);
	glTranslatef(0, 5, 0);
	glPopMatrix();

	//left edge
	glColor3f(0, 0.3, 0);
	glPushMatrix();
	glTranslatef(-5, 0, 0);
	glScalef(0.1, 1.1, 0.2);
	glutSolidCube(10);
	glScalef(0.909, 10, 5);
	glTranslatef(5, 0, 0);
	glPopMatrix();

	//right edge
	glColor3f(0, 0.3, 0);
	glPushMatrix();
	glTranslatef(5, 0, 0);
	glScalef(0.1, 1.1, 0.2);
	glutSolidCube(10);
	glScalef(0.909, 10, 5);
	glTranslatef(-5, 0, 0);
	glPopMatrix();
	glTranslatef(-startPad.startX, -startPad.startZ, 0);
	glTranslatef(0, 0, -0.1);
	glRotatef(90, 1, 0, 0);

	glPopMatrix();
	glPopMatrix();


}

void setStartParams(double startX, double startZ)
{
	if (startPad.startZ == 0)
	{
		startPad.startZ = startZ;

	}
	if (startPad.startX == 0)
	{
		startPad.startX = startX;
	}
}