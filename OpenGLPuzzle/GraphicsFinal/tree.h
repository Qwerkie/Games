class Tree
{
public:
	int treeBase = 0;
	int treeHeight = 0;
	int texture = 0;
	double treeX = 0.0;
	double treeZ = 0.0;
	double treeRot = 0.0;
	void setTreeParams(std::vector<Tree> trees, double startX, double startZ, double endX, double endZ);
	void loadTextures();
};

int treeBase = 0;
int treeHeight = 0;
double treeX = 0.0;
double treeZ = 0.0;
double treeRot = 0.0;
GLuint leaves, bark, christmas, needles;

void loadTreeTextures()
{
	leaves = SOIL_load_OGL_texture
		(
		"leaves.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	bark = SOIL_load_OGL_texture
		(
		"bark.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	christmas = SOIL_load_OGL_texture
		(
		"christmas.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	needles = SOIL_load_OGL_texture
		(
		"needles.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	/* check for an error during the load process */
	if (0 == leaves)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
	if (0 == bark)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
	if (0 == christmas)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
	if (0 == needles)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}



void drawTree(int treeBase, int treeHeight, int treeX, int treeZ, int treeRot, int texture)
{
	glTranslatef(treeX, 0, treeZ);
	glRotatef(treeRot, 0, 1, 0);
	glPushMatrix();

	//trunk
	glColor3f(1, 1, 1);
	GLUquadricObj *treeTrunk = gluNewQuadric();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, bark);
	gluQuadricTexture(treeTrunk, GL_TRUE);
	gluQuadricDrawStyle(treeTrunk, GLU_FILL);
	glPolygonMode(GL_FRONT, GL_FILL);
	gluQuadricNormals(treeTrunk, GLU_SMOOTH);
	glTranslatef(0, 3, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(treeTrunk, 1, 1, 10, 10, 10);
	glTranslatef(0, -3, 0);

	glEnable(GL_NORMALIZE);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//leaves

	glPushMatrix();
	glColor3f(1, 1, 1);
	GLUquadricObj *treeLeaves = gluNewQuadric();
	glEnable(GL_TEXTURE_2D);

	if (texture >= 0 && texture < 7)
	{
		glBindTexture(GL_TEXTURE_2D, leaves);
	}
	else if (texture >= 7 && texture < 14)
	{
		glBindTexture(GL_TEXTURE_2D, needles);
	}
	else if (texture == 14)
	{
		glBindTexture(GL_TEXTURE_2D, christmas);
	}

	gluQuadricTexture(treeLeaves, GL_TRUE);
	gluQuadricDrawStyle(treeLeaves, GLU_FILL);
	glPolygonMode(GL_FRONT, GL_FILL);
	gluQuadricNormals(treeLeaves, GLU_SMOOTH);
	glTranslatef(0, 3, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	gluCylinder(treeLeaves, treeBase, 0.0, treeHeight, 10, 10);
	glTranslatef(0, -3, 0);

	glEnable(GL_NORMALIZE);
	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
	glRotatef(-treeRot, 0, 1, 0);
	glTranslatef(-treeX, 0, -treeZ);

	glPopMatrix();


}

void Tree::setTreeParams(std::vector<Tree> trees, double startX, double startZ, double endX, double endZ)
{
	if (treeRot == 0)
	{
		treeRot = (rand() % 360);
	}
	if (texture == 0)
	{
		texture = (rand() % 15);
	}
	if (treeBase == 0)
	{
		treeBase = (rand() % 4) + 3;
	}
	if (treeHeight == 0)
	{
		treeHeight = (rand() % 10) + 10;
	}
	if (treeZ == 0)
	{
		treeZ = (rand() % 1500) - 750;
		for (int i = 0; i < trees.size(); i++)
		{
			if (treeZ<trees[i].treeZ + 10 && treeZ>trees[i].treeZ - 10)
			{
				treeZ = 0;
				setTreeParams(trees, startX, startZ, endX, endZ);
			}
		}
	}
	if (treeX == 0)
	{
		treeX = (rand() % 1500) - 750;
		for (int i = 0; i < trees.size(); i++)
		{
			if (treeX<trees[i].treeX + 10 && treeX>trees[i].treeX - 10)
			{
				treeX = 0;
				setTreeParams(trees, startX, startZ, endX, endZ);
			}
		}
	}
	if (treeZ == 0)
	{
		treeZ = (rand() % 1500) - 750;
		for (int i = 0; i < trees.size(); i++)
		{
			if (treeZ<startZ + 20 && treeZ>startZ - 20)
			{
				treeZ = 0;
				setTreeParams(trees, startX, startZ, endX, endZ);
			}
			if ((treeZ>490 && treeZ<510) || (treeZ<(-490) && treeZ>(-510)))
			{
				treeZ = 0;
				setTreeParams(trees, startX, startZ, endX, endZ);
			}
		}
	}
	if (treeX == 0)
	{
		treeX = (rand() % 1500) - 750;
		for (int i = 0; i < trees.size(); i++)
		{
			if (treeX<startX + 20 && treeX>startX - 20)
			{
				treeX = 0;
				setTreeParams(trees, startX, startZ, endX, endZ);
			}
			if ((treeX>490 && treeX<510) || (treeX<(-490) && treeX>(-510)))
			{
				treeX = 0;
				setTreeParams(trees, startX, startZ, endX, endZ);
			}
		}
	}
	if (treeZ == 0)
	{
		treeZ = (rand() % 1500) - 750;
		for (int i = 0; i < trees.size(); i++)
		{
			if (treeZ<endZ + 20 && treeZ>endZ - 20)
			{
				treeZ = 0;
				setTreeParams(trees, startX, startZ, endX, endZ);
			}
			if ((treeZ>490 && treeZ<510) || (treeZ<(-490) && treeZ>(-510)))
			{
				treeZ = 0;
				setTreeParams(trees, startX, startZ, endX, endZ);
			}
		}
	}
	if (treeX == 0)
	{
		treeX = (rand() % 1500) - 750;
		for (int i = 0; i < trees.size(); i++)
		{
			if (treeX<endX + 20 && treeX>endX - 20)
			{
				treeX = 0;
				setTreeParams(trees, startX, startZ, endX, endZ);
			}
			if ((treeX>490 && treeX<510) || (treeX<(-490) && treeX>(-510)))
			{
				treeX = 0;
				setTreeParams(trees, startX, startZ, endX, endZ);
			}
		}
	}

}