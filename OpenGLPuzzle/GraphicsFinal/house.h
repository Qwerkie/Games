class House
{
public:
	double houseX = 0.0;
	double houseZ = 0.0;
	double houseRot = 0.0;
	void setHouseParams(std::vector<House> houses, std::vector<Tree> trees, double startX, double startZ, double endX, double endZ);
};

GLuint bricks;


void loadHouseTextures()
{
	bricks = SOIL_load_OGL_texture
		(
		"bricks.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	/* check for an error during the load process */
	if (0 == bricks)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}

void drawHouse(int houseX, int houseZ, int houseRot)
{
	glTranslatef(houseX, 0, houseZ);
	glRotatef(houseRot, 0, 1, 0);
	//house
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, bricks);
	//glutSolidCube(10);
	glScalef(5, 5, 5);
	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
	// Back Face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
	// Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
	glEnd();
	glScalef(0.2, 0.2, 0.2);
	glEnable(GL_NORMALIZE);
	glDisable(GL_TEXTURE_2D);
	glTranslatef(0, -5, 0);
	glPopMatrix();

	//roof
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glColor3f(0.6, 0.3, 0.2);
	glTranslatef(0, 5, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(-5, 0, -5);
	glVertex3f(0, 5, 0);
	glVertex3f(5, 0, -5);

	glVertex3f(5, 0, -5);
	glVertex3f(0, 5, 0);
	glVertex3f(5, 0, 5);

	glVertex3f(5, 0, 5);
	glVertex3f(0, 5, 0);
	glVertex3f(-5, 0, 5);

	glVertex3f(-5, 0, 5);
	glVertex3f(0, 5, 0);
	glVertex3f(-5, 0, -5);
	glEnd();
	glTranslatef(0, -5, 0);
	glTranslatef(0, -5, 0);
	glPopMatrix();

	//door
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glColor3f(0.125, 0.125, 0.125);
	glTranslatef(-0.9, -3, 5.1);
	glRectf(-0.8, 2, 0.8, -2);
	glTranslatef(1.8, 0, 0);
	glRectf(-0.8, 2, 0.8, -2);
	glTranslatef(-1.8, 0, 0);
	glTranslatef(0.9, 3, -5.1);
	glTranslatef(0, -5, 0);
	glPopMatrix();

	//left window
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glColor3f(1, 1, 1);
	glTranslatef(-3.5, 3, 5.1);
	glRectf(-0.5, 0.5, 0.5, -0.5);
	glTranslatef(0, -1.1, 0);
	glRectf(-0.5, 0.5, 0.5, -0.5);
	glTranslatef(1.1, 0, 0);
	glRectf(-0.5, 0.5, 0.5, -0.5);
	glTranslatef(0, 1.1, 0);
	glRectf(-0.5, 0.5, 0.5, -0.5);
	glTranslatef(0, -1.1, 0);
	glTranslatef(-1.1, 0, 0);
	glTranslatef(0, 1.1, 0);
	glTranslatef(3.5, -3, -5.1);
	glTranslatef(0, -5, 0);
	glPopMatrix();

	//right window
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glColor3f(1, 1, 1);
	glTranslatef(2.5, 3, 5.1);
	glRectf(-0.5, 0.5, 0.5, -0.5);
	glTranslatef(0, -1.1, 0);
	glRectf(-0.5, 0.5, 0.5, -0.5);
	glTranslatef(1.1, 0, 0);
	glRectf(-0.5, 0.5, 0.5, -0.5);
	glTranslatef(0, 1.1, 0);
	glRectf(-0.5, 0.5, 0.5, -0.5);
	glTranslatef(0, -1.1, 0);
	glTranslatef(-1.1, 0, 0);
	glTranslatef(0, 1.1, 0);
	glTranslatef(-2.5, -3, -5.1);
	glTranslatef(0, -5, 0);
	glPopMatrix();
	glRotatef(-houseRot, 0, 1, 0);
	glTranslatef(-houseX, 0, -houseZ);
	glPopMatrix();
}

void House::setHouseParams(std::vector<House> houses, std::vector<Tree> trees, double startX, double startZ, double endX, double endZ)
{
	if (houseRot == 0)
	{
		houseRot = (rand() % 4) * 90;
	}
	if (houseZ == 0)
	{
		houseZ = (rand() % 1500) - 750;
		for (int i = 0; i < houses.size(); i++)
		{
			if (houseZ<houses[i].houseZ + 10 && houseZ>houses[i].houseZ - 10)
			{
				houseZ = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
			if ((houseZ>490 && houseZ<510) || (houseZ<(-490) && houseZ>(-510)))
			{
				houseZ = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
		}
	}
	if (houseZ == 0)
	{
		houseZ = (rand() % 1500) - 750;
		for (int i = 0; i < trees.size(); i++)
		{
			if (houseZ<trees[i].treeZ + 10 && houseZ>trees[i].treeZ - 10)
			{
				houseZ = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
		}
	}
	if (houseX == 0)
	{
		houseX = (rand() % 1500) - 750;
		for (int i = 0; i < houses.size(); i++)
		{
			if (houseX<houses[i].houseX + 10 && houseX>houses[i].houseX - 10)
			{
				houseX = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
			if ((houseX>490 && houseX<510) || (houseX<(-490) && houseX>(-510)))
			{
				houseX = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
		}
	}
	if (houseX == 0)
	{
		houseX = (rand() % 1500) - 750;
		for (int i = 0; i < trees.size(); i++)
		{
			if (houseX<trees[i].treeX + 10 && houseX>trees[i].treeX - 10)
			{
				houseX = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
		}
	}

	if (houseZ == 0)
	{
		houseZ = (rand() % 1500) - 750;
		for (int i = 0; i < houses.size(); i++)
		{
			if (houseZ<startZ + 20 && houseZ>startZ - 20)
			{
				houseZ = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
			if ((houseZ>490 && houseZ<510) || (houseZ<(-490) && houseZ>(-510)))
			{
				houseZ = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
		}
	}
	if (houseX == 0)
	{
		houseX = (rand() % 1500) - 750;
		for (int i = 0; i < houses.size(); i++)
		{
			if (houseX<startX + 20 && houseX>startX - 20)
			{
				houseX = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
			if ((houseX>490 && houseX<510) || (houseX<(-490) && houseX>(-510)))
			{
				houseX = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
		}
	}
	if (houseZ == 0)
	{
		houseZ = (rand() % 1500) - 750;
		for (int i = 0; i < houses.size(); i++)
		{
			if (houseZ<endZ + 20 && houseZ>endZ - 20)
			{
				houseZ = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
			if ((houseZ>490 && houseZ<510) || (houseZ<(-490) && houseZ>(-510)))
			{
				houseZ = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
		}
	}
	if (houseX == 0)
	{
		houseX = (rand() % 1500) - 750;
		for (int i = 0; i < houses.size(); i++)
		{
			if (houseX<endX + 20 && houseX>endX - 20)
			{
				houseX = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
			if ((houseX>490 && houseX<510) || (houseX<(-490) && houseX>(-510)))
			{
				houseX = 0;
				setHouseParams(houses, trees, startX, startZ, endX, endZ);
			}
		}
	}
}