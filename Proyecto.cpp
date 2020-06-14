#include <GL/glut.h>
#include<GL/freeglut.h>

void Draw(void);
void Initialize();
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100,200);
	glutCreateWindow("boucing");

	glutDisplayFunc(Draw);
	
	
	glutMainLoop();
	
	return 0;
}
void Draw()
{
	glBegin(GL_LINES);
	glVertex3f(-1.0f, -1.0f,0.0f);
	glVertex3f(1.0f, 1.0f,0.0f);
	glEnd();

	glutSwapBuffers();
}
void Initialize()
{
	glClearColor(0.9, 0.9, 0.9, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
			/* aspect ratio */ 1.0,
			/* Z near */ 1.0, /* Z far */ 10.0);
	glutPostRedisplay();
}