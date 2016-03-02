/*
	Graphics Final Project
	Helicopter Flight Simulator

	Mark Stankiewicz & James Shultz

	April 30, 2015
*/

#include <cstdlib>
#include <GL/freeglut.h>
#include <iostream>
#include <cstring>
#include <time.h>
#include <vector>

#include "SOIL.h"
#include "tree.h"
#include "startPad.h"
#include "endPad.h"
#include "house.h"
#include "helicopter.h"
#include "fence.h"

using namespace std;

GLUquadric *obj = gluNewQuadric();
GLuint grass;
std::vector<Tree> trees;
std::vector<House> houses;
int width;
int height;
int heliMode = 1;
bool win = false;

double minHeight = -3;

double intensity = 0.9;
int treeCount = 0;
int houseCount = 0;

float lx = 0.0;
float ly = 0.0;
float lz = 0.0;
double xPos = 0.0;
double yPos = 0.0;
double zPos = 0.0;

float angle = 0.0;

float yz = 1.0;

bool alive = 1;

double startX = 0.0;
double startZ = 0.0;
double endX = 0.0;
double endZ = 0.0;
double velocity;
int fly = 1;
int f_tilt = 0;
int b_tilt = 0;
int right_turn = 0;
int left_turn = 0;
double xMod = 12.5;
double yMod = 8;
double zMod = 12.5;

//heli variables
double blade_angle = 0;
double side_angle = 0;

void setStartEnd(){
	if (startX == 0){
		startX = rand() % 90 + 400;
		xPos = startX;
	}
	if (startZ == 0){
		startZ = rand() % 980 - 490;
		zPos = startZ;
	}
	if (endX == 0){
		endX = (rand() % 90)*-1 - 400;
	}
	if (endZ == 0){
		endZ = rand() % 980 - 490;
	}
}

void initializeTextures()
{
	grass = SOIL_load_OGL_texture
		(
		"grass.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	/* check for an error during the load process */
	if (0 == grass)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}

void init()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	yPos = minHeight;
	setStartEnd();
	setStartParams(startX, startZ);
	setEndParams(endX, endZ);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);

}

void initTransformation()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspect = ((double)height) / ((double)width);
	gluPerspective(90.0, 1.0, 0.1, 1500);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLoadIdentity();
	gluLookAt(xPos - lx * xMod, yPos + yz * yMod, zPos - lz * zMod,//changes angle of looking at
		xPos + lx, yPos, zPos + lz,
		0, 1, 0);
}

void turnOffTilt(){
	f_tilt = 0;
	b_tilt = 0;
	left_turn = 0;
	right_turn = 0;
}

void turnOnTilt(int i){
	turnOffTilt();
	if (i == 0) f_tilt = 1;
	else if (i == 1) left_turn = 1;
	else if (i == 2) right_turn = 1;
	else if (i == 3) b_tilt = 1;
}

void drawObjects()
{
	glPushMatrix();
	GLfloat mat_amb_diff[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat mat_specular[] = { 0.1, 0.1, 0.1, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	glEnable(GL_COLOR_MATERIAL);

	glColor3f(0, 0, 0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(xPos, 0.01, zPos);

	double radius = 2.5;

	for (double c_angle = 1.0f; c_angle<361.0f; c_angle += 1)
	{
		double x2 = xPos + sin(c_angle)*radius;
		double z2 = zPos + cos(c_angle)*radius;
		glVertex3f(x2, 0.01, z2);
	}

	glEnd();

	if (alive == 1 || alive == -1){
		glPushMatrix();
		if (heliMode == 1){
			drawHelicopter(xPos, yPos, zPos, f_tilt, b_tilt, right_turn, left_turn, blade_angle, side_angle, angle);	//draws helicopter
		}
		else if (heliMode == 2){
			drawHeli(xPos, yPos, zPos, f_tilt, b_tilt, right_turn, left_turn, blade_angle, side_angle, angle);	//draws heli
		}
		else if (heliMode == 3){
			drawDaniel(xPos, yPos, zPos, f_tilt, b_tilt, right_turn, left_turn, blade_angle, angle);	//draws daniel
		}
		else{
			drawOala(xPos, yPos, zPos, f_tilt, b_tilt, right_turn, left_turn, blade_angle, angle);	//draws gener
		}
		glPopMatrix();
		//drawDeaths();		//draws the deaths
	}
	else{
		//deathX.push_back(xPos);
		//deathZ.push_back(zPos);
		alive = 1;
		xPos = startX;
		zPos = startZ;
		yPos = minHeight;
		fly = 2;
	}

	glDisable(GL_LIGHTING);
	drawStartPad();
	drawEndPad();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0, -2, 0);
	drawFence();
	glTranslatef(0, 2, 0);
	glScalef(2, 2, 2);
	glEnable(GL_LIGHTING);


	for (treeCount; treeCount < 100; treeCount++)
	{
		Tree tree;
		trees.push_back(tree);
		trees[treeCount].setTreeParams(trees, startX, startZ, endX, endZ);
	}
	for (int i = 0; i < trees.size(); i++)
	{
		drawTree(trees[i].treeBase, trees[i].treeHeight, trees[i].treeX, trees[i].treeZ, trees[i].treeRot, trees[i].texture);
	}

	for (houseCount; houseCount < 100; houseCount++)
	{
		House house;
		houses.push_back(house);
		houses[houseCount].setHouseParams(houses, trees, startX, startZ, endX, endZ);
	}
	for (int i = 0; i < houses.size(); i++)
	{
		drawHouse(houses[i].houseX, houses[i].houseZ, houses[i].houseRot);
	}


	initializeTextures();

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, grass);               // Select Our Texture
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-768, 0, -768);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(192.0f, 0.0f); glVertex3f(768, 0, -768);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(192.0f, 192.0f); glVertex3f(768, 0, 768);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 192.0f); glVertex3f(-768, 0, 768);  // Top Left Of The Texture and Quad
	glEnd();
	glEnable(GL_NORMALIZE);
	glDisable(GL_TEXTURE_2D);

	//central light
	GLfloat light0_position[] = { xPos, 50, zPos, 0 };
	GLfloat ambient0[4] = { intensity, intensity, intensity, intensity };
	GLfloat diffuse0[4] = { intensity, intensity, intensity, intensity };
	GLfloat specular0[4] = { 0, 0.3, 0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

	glPopMatrix();
}

void display()
{
	glClearColor(0.53, 0.81, 0.98, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	initTransformation();
	drawObjects();
	glFlush();
	glutSwapBuffers();
}

void reshape(int new_width, int new_height)
{
	glViewport(0, 0, new_width, new_height);
	height = new_height;
	width = new_width;
}

void timer_func(int n)
{
	if (!win){
		if (yPos > minHeight && fly == 0){
			if (velocity > 0){
				velocity = 0;
			}
			else{
				velocity -= 0.05;
			}
			yPos += velocity;
		}
		if (yPos < minHeight){
			yPos = 0;
			if ((xPos < endPad.endX + 2.5) && (xPos > endPad.endX - 2.5) && (zPos < endPad.endZ + 2.5) && (zPos > endPad.endZ - 2.5) && (velocity > -0.5)){
				yPos = minHeight;
				win = true;
			}
			else{
				alive = 0;
			}
			//check if died lolz
			//boundaries and shit
			//exit(0);
		}
		if (fly == 0 && yPos > minHeight){
			blade_angle += 15;
			if (blade_angle > 360) blade_angle - 360;
		}
		else if (fly == 1){
			if (velocity > 0){
				blade_angle += velocity * 30;
			}
			else{
				blade_angle += 15;
				if (blade_angle > 360) blade_angle - 360;
			}
		}
		else if (fly == 2){
			blade_angle += 15;
			if (blade_angle > 360) blade_angle - 360;
		}
	}
	else{
		angle = (angle + 6);
		if (angle > 360){
			angle -= 360;
		}
		blade_angle = (blade_angle - 26);
		if (blade_angle < 360){
			blade_angle += 360;
		}
		side_angle = (side_angle - 27);
		if (side_angle < 360){
			side_angle += 360;
		}
	}
	glutPostRedisplay();  //redraw
	glutTimerFunc(n, timer_func, n); // recursively call timer_func
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key){
	case 8:
		win = false;
		alive = 1;
		xPos = startX;
		yPos = minHeight;
		zPos = startZ;
		velocity = 0;
		fly = 2;
		break;
	}
	if (!win){
		if (alive == 1){
			switch (key)
			{
			case 27: exit(0);
				// the real deal helichopter
			case 49:
				heliMode = 1;
				break;
				//mehh
			case 50:
				heliMode = 2;
				break;
				//daniel the glorious aircraft
			case 51:
				heliMode = 3;
				break;
				//forward 1
			case 52:
				heliMode = 4;
				break;
			case 53:
				xMod = 12.5;
				yMod = 8;
				zMod = 12.5;
				break;
				//forward 2
			case 54:
				xMod = 15;
				yMod = 10;
				zMod = 15;
				break;
				//forward 3
			case 55:
				xMod = 20;
				yMod = 15;
				zMod = 20;
				break;
				//far away forward
			case 56:
				xMod = 25;
				yMod = 20;
				zMod = 25;
				break;
				//rear
			case 57:
				xMod = -20;
				yMod = 15;
				zMod = -20;
				break;
				//dat rear doe
			case 48:
				xMod = -30;
				yMod = 24;
				zMod = -30;
				break;
			case 107://level
				turnOffTilt();
				velocity = 0;
				if (fly == 2){
					fly = 0;
				}
				else
					fly = 2;
				break;
			case 105://vertical
				turnOffTilt();
				if (velocity < 0 || fly != 1){
					velocity = 0;
				}
				else{
					velocity += 0.1;
				}
				if (yPos < 300){
					fly = 1;
				}
				if (fly == 1 && yPos < 300){
					yPos += velocity;
				}
				break;
			}
		}
	}
	glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y){
	if (!win){
		if (alive == 1){
			switch (key){
			case 105:
				fly = 0;
			}
		}
	}
	glutPostRedisplay();
}

void specialUp(int key, int x, int y){
	if (!win){
		if (alive == 1){
			switch (key) {
			case GLUT_KEY_LEFT:
				turnOffTilt();
				break;
			case GLUT_KEY_RIGHT:
				turnOffTilt();
				break;
			case GLUT_KEY_UP:
				turnOffTilt();
				break;
			case GLUT_KEY_DOWN:
				turnOffTilt();
				break;
			}
		}
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	if (!win){
		if (alive == 1){
			float fraction = 2.0f;//was0.5
			switch (key) {
			case GLUT_KEY_LEFT:
				if (yPos > minHeight){
					turnOnTilt(2);
					angle -= 6;
					side_angle += 29;
					if (side_angle > 360) side_angle - 360;
					lx = sin(angle*0.0174532925);
					lz = -cos(angle*0.0174532925);
				}
				break;
			case GLUT_KEY_UP:
				if (yPos > minHeight){
					turnOnTilt(0);
					xPos += lx*fraction;
					zPos += lz*fraction;
				}
				//boundary check
				if (xPos > 496)			xPos = 496;
				else if (xPos < -496)	xPos = -496;
				if (zPos > 496)			zPos = 496;
				else if (zPos < -496)	zPos = -496;
				break;
			case GLUT_KEY_RIGHT:
				turnOnTilt(1);	//this is so broken it aint fixable
				angle += 6;
				side_angle += 29;
				if (side_angle > 360) side_angle - 360;
				lx = sin(angle*0.0174532925);
				lz = -cos(angle*0.0174532925);
				break;
			case GLUT_KEY_DOWN:
				if (yPos > minHeight){
					turnOnTilt(3);
					xPos -= lx*fraction;
					zPos -= lz*fraction;
					if (xPos > 496)			xPos = 496;
					else if (xPos < -496)	xPos = -496;
					if (zPos > 496)			zPos = 496;
					else if (zPos < -496)	zPos = -496;
				}
				break;
			default:
				return;
			}
		}
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("Helicopter Simulator");
	cout << "-------Helicopter Simulator-------" << endl;
	cout << "----------------------------------" << endl;
	cout << "------------Directions------------" << endl;
	cout << "Fly from the start pad to end pad" << endl;
	cout << "while keeping a steady velocity" << endl;
	cout << "when landing in the fastest time." << endl << endl;
	cout << "Press right on D-pad to start." << endl;
	cout << endl;
	cout << "-------------Controls-------------" << endl;
	cout << endl;
	cout << "Keys 1-4: Set Helicopter" << endl << endl;
	cout << "Keys 5-0: Set Camera Perspective" << endl << endl;
	cout << "I key: Ascend" << endl << endl;
	cout << "K key: Steady Helicopter" << endl << endl;
	cout << "Direction Pad: Move Helicopter" << endl << endl;
	cout << "Backspace Key: Restart" << endl << endl;
	cout << "Escape Key: Quit" << endl;

	initializeTextures();
	loadFenceTextures();
	loadHouseTextures();
	loadTreeTextures();
	loadHelicopterTextures();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp);
	init();
	glutTimerFunc(15, timer_func, 1);
	glutMainLoop();
}
