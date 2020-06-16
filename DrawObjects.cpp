#include"DrawObjects.h"


//dividiremos la esfera en trozos discretos por cordenadas esf�ricas, variando phi y theta
const int Nphi = 20;
const int Ntheta = 40;
const float Dtheta = 2 * 3.14159265359f / (1.0 * Ntheta);
const float Dphi = 3.14159265359f / (1.0 * Nphi);
GLfloat phi = 0.0;
GLfloat theta = 0.0f;
float SphereVertices[Ntheta * Nphi * 3] = { 0.0 };
void FillSphereVertices()
{
	for (int ii = 0; ii < Nphi; ii++)
		for (int kk = 0; kk < Ntheta; kk++)
		{
			SphereVertices[ii * Ntheta * 3 + kk * 3] = std::sinf(ii * Dphi) * std::cosf(kk * Dtheta);
			SphereVertices[ii * Ntheta * 3 + kk * 3 + 1] = std::sinf(ii * Dphi) * std::sinf(kk * Dtheta);
			SphereVertices[ii * Ntheta * 3 + kk * 3 + 2] = std::cosf(ii * Dphi);
		}
}


void DrawSphere(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius)
{
	glColor3f(0.5f, 0.02f, 0.0f);
	for (int ii = 0; ii < Nphi; ii++)
	{

		glBegin(GL_QUAD_STRIP);

		for (int kk = 0; kk < Ntheta; kk++)
		{
			if (ii == 10)
			{
				glColor3f(0.5f, 0.4f, 0.0f);
			}
			if (ii == 15)
			{
				glColor3f(0.1f, 0.4f, 0.9f);
			}

			glVertex3f(centerx + radius * SphereVertices[ii * Ntheta * 3 + kk * 3],
				centery + radius * SphereVertices[ii * Ntheta * 3 + kk * 3 + 1],
				centerz + radius * SphereVertices[ii * Ntheta * 3 + kk * 3 + 2]);
			glVertex3f(centerx + radius * SphereVertices[(ii + 1) * Ntheta * 3 + kk * 3],
				centery + radius * SphereVertices[(ii + 1) * Ntheta * 3 + kk * 3 + 1],
				centerz + radius * SphereVertices[(ii + 1) * Ntheta * 3 + kk * 3 + 2]);

		}
		glVertex3f(centerx + radius * SphereVertices[ii * Ntheta * 3],
			centery + radius * SphereVertices[ii * Ntheta * 3 + 1],
			centerz + radius * SphereVertices[ii * Ntheta * 3 + 2]);
		glVertex3f(centerx + radius * SphereVertices[(ii + 1) * Ntheta * 3],
			centery + radius * SphereVertices[(ii + 1) * Ntheta * 3 + 1],
			centerz + radius * SphereVertices[(ii + 1) * Ntheta * 3 + 2]);

		glEnd();
	}
}

void DrawGrid(int HALF_GRID_SIZE, GLfloat GRID_SQUARE_SIZE, GLfloat GRID_HEIGHT)
{

	glBegin(GL_LINES);
	glColor3f(0.2f, 0.2f, 0.2f);
	for (int i = -HALF_GRID_SIZE; i <= HALF_GRID_SIZE; i++)
	{
		glVertex3f((float)i *GRID_SQUARE_SIZE, GRID_HEIGHT, (float)-HALF_GRID_SIZE*GRID_SQUARE_SIZE );
		glVertex3f((float)i *GRID_SQUARE_SIZE, GRID_HEIGHT, (float)HALF_GRID_SIZE*GRID_SQUARE_SIZE );

		glVertex3f((float)-HALF_GRID_SIZE*GRID_SQUARE_SIZE, GRID_HEIGHT, (float)i * GRID_SQUARE_SIZE);
		glVertex3f((float)HALF_GRID_SIZE*GRID_SQUARE_SIZE , GRID_HEIGHT, (float)i * GRID_SQUARE_SIZE);
	}
	glEnd();

}
