#include"DrawObjects.h"




// dividiremos la esfera en trozos discretos por cordenadas esféricas, variando phi y theta
GLfloat RedMaterial[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat BlueMaterial[4] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat YellowMaterial[4] = { 0.8,0.8,0.1,1.0 };
GLfloat WhiteMaterial[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat BlackMaterial[4] = { 0.0, 0.0, 0.0, 1.0 };

const int Nphi = 25;
const int Ntheta = 25;
const float Dtheta = 2 * 3.14159265359f / (1.0f * Ntheta);
const float Dphi = 3.14159265359f / (1.0f * Nphi);
float SphereVertices[Ntheta * (Nphi + 1) * 3] = { 0.0 };
void FillSphereVertices()
{
	for (int ii = 0; ii < Nphi + 1; ii++)
		for (int kk = 0; kk < Ntheta; kk++)
		{
			SphereVertices[ii * Ntheta * 3 + kk * 3] = std::sinf(ii * Dphi) * std::cosf(kk * Dtheta);
			SphereVertices[ii * Ntheta * 3 + kk * 3 + 1] = std::sinf(ii * Dphi) * std::sinf(kk * Dtheta);
			SphereVertices[ii * Ntheta * 3 + kk * 3 + 2] = std::cosf(ii * Dphi);
		}
}


void DrawSphere(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius)
{
	GLfloat spec[4] = { 1.0, 0.0, 1.0, 1.0 };
	GLfloat Theta = 0.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RedMaterial);
	for (int ii = 0; ii < Nphi; ii++)
	{

		glBegin(GL_QUAD_STRIP);

		for (int kk = 0; kk < Ntheta; kk++)
		{

			glNormal3f(SphereVertices[ii * Ntheta * 3 + kk * 3],
				SphereVertices[ii * Ntheta * 3 + kk * 3 + 1],
				SphereVertices[ii * Ntheta * 3 + kk * 3 + 2]);
			glVertex3f(centerx + radius * SphereVertices[ii * Ntheta * 3 + kk * 3],
				centery + radius * SphereVertices[ii * Ntheta * 3 + kk * 3 + 1],
				centerz + radius * SphereVertices[ii * Ntheta * 3 + kk * 3 + 2]);
			glNormal3f(SphereVertices[(ii + 1) * Ntheta * 3 + kk * 3],
				SphereVertices[(ii + 1) * Ntheta * 3 + kk * 3 + 1],
				SphereVertices[(ii + 1) * Ntheta * 3 + kk * 3 + 2]);
			glVertex3f(centerx + radius * SphereVertices[(ii + 1) * Ntheta * 3 + kk * 3],
				centery + radius * SphereVertices[(ii + 1) * Ntheta * 3 + kk * 3 + 1],
				centerz + radius * SphereVertices[(ii + 1) * Ntheta * 3 + kk * 3 + 2]);

		}
		glNormal3f(SphereVertices[ii * Ntheta * 3],
			SphereVertices[ii * Ntheta * 3 + 1],
			SphereVertices[ii * Ntheta * 3 + 2]);
		glVertex3f(centerx + radius * SphereVertices[ii * Ntheta * 3],
			centery + radius * SphereVertices[ii * Ntheta * 3 + 1],
			centerz + radius * SphereVertices[ii * Ntheta * 3 + 2]);
		glNormal3f(SphereVertices[(1 + ii) * Ntheta * 3],
			SphereVertices[(ii + 1) * Ntheta * 3 + 1],
			SphereVertices[(ii + 1) * Ntheta * 3 + 2]);
		glVertex3f(centerx + radius * SphereVertices[(ii + 1) * Ntheta * 3],
			centery + radius * SphereVertices[(ii + 1) * Ntheta * 3 + 1],
			centerz + radius * SphereVertices[(ii + 1) * Ntheta * 3 + 2]);

		glEnd();
	}
}

void DrawGrid(int HALF_GRID_SIZE, GLfloat GRID_SQUARE_SIZE, GLfloat GRID_HEIGHT)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BlueMaterial);
	glBegin(GL_LINES);

	glNormal3f(0.0f, 1.0f, 0.0f);
	for (int i = -HALF_GRID_SIZE; i <= HALF_GRID_SIZE; i++)
	{
		glVertex3f((float)i * GRID_SQUARE_SIZE, GRID_HEIGHT, (float)-HALF_GRID_SIZE * GRID_SQUARE_SIZE);
		glVertex3f((float)i * GRID_SQUARE_SIZE, GRID_HEIGHT, (float)HALF_GRID_SIZE * GRID_SQUARE_SIZE);

		glVertex3f((float)-HALF_GRID_SIZE * GRID_SQUARE_SIZE, GRID_HEIGHT, (float)i * GRID_SQUARE_SIZE);
		glVertex3f((float)HALF_GRID_SIZE * GRID_SQUARE_SIZE, GRID_HEIGHT, (float)i * GRID_SQUARE_SIZE);
	}
	glEnd();

}

void DrawBoxGrid(GLfloat HalfLength, GLfloat centerx, GLfloat centery, GLfloat centerz)
{
	GLfloat L = HalfLength;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WhiteMaterial);
	glNormal3f(0.0f, 1.0f, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(centerx - L, centery - L, centerz - L);
	glVertex3f(centerx - L, centery - L, centerz + L);
	glVertex3f(centerx + L, centery - L, centerz + L);
	glVertex3f(centerx + L, centery - L, centerz - L);
	glVertex3f(centerx - L, centery - L, centerz - L);
	glVertex3f(centerx - L, centery + L, centerz - L);
	glVertex3f(centerx - L, centery + L, centerz + L);
	glVertex3f(centerx + L, centery + L, centerz + L);
	glVertex3f(centerx + L, centery + L, centerz - L);
	glVertex3f(centerx - L, centery + L, centerz - L);

	glEnd();

	glBegin(GL_LINES);
	glVertex3f(centerx - L, centery - L, centerz + L);
	glVertex3f(centerx - L, centery + L, centerz + L);
	glVertex3f(centerx + L, centery - L, centerz + L);
	glVertex3f(centerx + L, centery + L, centerz + L);
	glVertex3f(centerx + L, centery - L, centerz - L);
	glVertex3f(centerx + L, centery + L, centerz - L);

	glEnd();

}
