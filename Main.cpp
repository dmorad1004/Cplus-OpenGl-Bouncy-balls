#include <GL/glut.h>
#include<GL/freeglut.h>

#include"DrawObjects.h"
#include"LeapFrog.h"

GLfloat Drotation = 0.05f;
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  /* Red diffuse light. */
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };  /* Infinite light location. */

GLfloat rotangv = 0.005; //camera angle rotation frecuency

//Delete?
GLfloat PosX = 0.0f;   //Posición del centro del yoyo
GLfloat PosY = 0.0f; 
GLfloat PosZ = 0.0f;//------
GLfloat RAD = 0.27f;  //radio
GLfloat DX = 0.0003f;GLfloat DY = -0.0005f;GLfloat DZ = 0.0005f;
//
void Draw(void);
void Initialize();
int main(int argc, char** argv)
{
    Particle ball;
	ball.read("ball.txt");
    ball.print("ball-out.txt");
     Config conf; 
    conf.read("conf.txt");
    conf.print("conf-out.conf");

	  // LeapFrog
    for(int ii = 0; ii < conf.NSTEPS; ++ii) {
    float t = conf.TMIN + ii*conf.DT;
    timestep(conf.DT, ball);
    compute_force(ball, conf);
  }


	FillSphereVertices();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH |GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("boucing");
	Initialize();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutDisplayFunc(Draw);
	
	
	glutMainLoop();
	
	return 0;
}
void Draw(Particle& b)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawGrid(50,0.1f,-1.0f);
	//glRotatef(Drotation, 0.0, 1.0, 0.0);
	DrawBoxGrid(1.0f, 0.0f, 0.01f, 0.0f);
	glColor3f(0.5f, 0.1f, 0.1f);
	DrawSphere(b.R[0], b.R[1], b.R[2], b.rad);
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WhiteMaterial);
	//glutSolidCone(0.5f, 1.0f, 10, 10);

	  // LeapFrog
    for(int ii = 0; ii < conf.NSTEPS; ++ii) {
    float t = conf.TMIN + ii*conf.DT;
    timestep(conf.DT, ball);
    compute_force(ball, conf);
  }
  
	//Delete?
	PosX += DX;
	PosY += DY;
	PosZ += DZ;

	if( PosX<= -1.0f +RAD)
	{
		DX *= -1;
	}
	if( PosY-RAD <= -1.0f )
	{
		DY *= -1;
	}
	if( PosZ-RAD <= -1.0f )
	{
		DZ *= -1;
	}
	if (PosX + RAD >= 1.0f)
	{
		DX *= -1;
	}
	if (PosY + RAD >= 1.0f)
	{
		DY *= -1;
	}
	if (PosZ + RAD >= 1.0f)
	{
		DZ *= -1;
	}

	glutSwapBuffers();
	glutPostRedisplay();
}
void Initialize()
{
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glClearColor(0.03f, 0.03f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
			/* aspect ratio */ 8.0/6.0,
			/* Z near */ 1.0, /* Z far */ 10.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 2.0, 4.0,  /* eye is at */
		0.0, 0.0, 0.0,      /* center is at (0,0,0) */
		0.0, 1.0, 0.0);      /* up is in posiBtive Y direction */

	 /* Adjust cube position to be asthetic angle. */
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	
}

