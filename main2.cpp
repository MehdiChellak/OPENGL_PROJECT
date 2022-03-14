#include<GL/glew.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include "Objets.h"

//Variables globales
float r=10;
float theta=10,phi=0;

void Orbite(float r, float theta, float phi)
{
    glTranslated(0,0,-r);
    glRotatef(-phi,1,0,0);
    glRotatef(-theta,0,1,0);
}
void Afficher(void)
{
	//Effacer l'image precedente

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Placer la camera

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Fontion qui permet de plqcer le camera
	//gluLookAt(1,2,3,0,0,0,0,1,0);

	Orbite(r,theta,phi);

    Repere(2.0);
    glColor3f(1,1,1);

	glutWireTeapot(1);

	glFlush();
	glutSwapBuffers();
}

void Redim(int L, int H)
{
	//Definir la projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(-1,1,-1.0*H/L,1.0*H/L,0.1,1000);

	//OR

	gluPerspective(45,(float)L/H,0.1,1000);

	//Portion de la fenetre
	glViewport(0,0,L,H);
}



void Clavier(unsigned char key, int x, int y)
{
    switch(key)
    {
    case '-':
        r+=0.1;
        break;
    case '+':
        if(r>0.1)
            r-=0.1;
            break;
    }
    glutPostRedisplay();
}

void Special(int key,int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_LEFT :
        theta--;
        break;
    case GLUT_KEY_RIGHT :
        theta++;
        break;
    case GLUT_KEY_UP :
        phi++;
        break;
    case GLUT_KEY_DOWN :
        phi--;
        break;
    }
    glutPostRedisplay();
}

int main(int argc,char** argv)
{
	//init.de glut et glew
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("OpenGL--SOUKAYNA");
	GLenum msg = glewInit();
	if(msg !=GLEW_OK)
	{
		printf("Erreur : %s \n", glewGetErrorString(msg));
		exit(1);
	}
	else
		printf("Version OpenGL: %s \n", glGetString(GL_VERSION));

	//fonction  de Rappel
	glutDisplayFunc(Afficher);
	glutReshapeFunc(Redim);
	glutKeyboardFunc(Clavier);
	glutSpecialFunc(Special);

	//Init de gl
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH);

	//Boucle d'evenments
	glutMainLoop();

	return 0;
}
