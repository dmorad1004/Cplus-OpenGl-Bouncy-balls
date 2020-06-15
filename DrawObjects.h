#ifndef _OBJECTS_
#define _OBJECTS_

#include <GL/glut.h>
#include<GL/freeglut.h>
#include<array>
#include <cmath>
#include <vector>
void DrawGrid(int HALF_GRID_SIZE, GLfloat GRID_SQUARE_SIZE, GLfloat GRID_HEIGHT);
void FillSphereVertices();
void DrawSphere(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius);

#endif // !_SPHERE_
