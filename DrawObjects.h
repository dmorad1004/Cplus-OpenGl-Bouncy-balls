#ifndef _OBJECTS_
#define _OBJECTS_

#include <glut.h>
#include<freeglut.h>
#include<array>
#include <cmath>
#include <vector>


void DrawBoxGrid(GLfloat HalfLength, GLfloat centerx, GLfloat centery, GLfloat centerz);
void DrawGrid(int HALF_GRID_SIZE, GLfloat GRID_SQUARE_SIZE, GLfloat GRID_HEIGHT);
void FillSphereVertices();
void DrawSphere(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius);

#endif  // !_SPHERE_
