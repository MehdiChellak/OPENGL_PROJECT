#include<GL/glew.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include "objets.h"
#include<math.h>
#include "Exam20182019.h"
//::::::::::::::::::::::::::::::::::::::::::::: surface :::::::::::::::::::::::::::::
void surfaceGraphique(float R, float r,float h, float seg, float segH)
{
    float pas=2*M_PI/seg;
    float dr = R-r;
    float pasH = 1.0/(segH-1);
    float ra = 0, ya =0, rb = 0, yb = 0;
    glBegin(GL_QUAD_STRIP);
    for(int j = 0; j < segH-1; j++)
    {
        ra = R*(1-j*pasH) + j*pasH*r;
        ya  = h*(j*pasH);

        rb = R*(1-(j+1)*pasH) + (j+1)*pasH*r;
        ya  = h*((j+1)*pasH);
        float cosphi = float(h/sqrt(dr*dr+h*h));
        float sinphi = float(dr/sqrt(dr*dr+h*h));
        for (int i = 0; i <= seg ; i++)
        {
            glNormal3f(cosphi*cos(i*pas),sinphi,cosphi*sin(i*pas));
            glVertex3f(ra*cos(i*pas),ya,ra*sin(i*pas));
            glVertex3f(rb*cos(i*pas),yb,rb*sin(i*pas));
        }
    }
    glEnd();
}
//::::::::::::::::::::::::::::::::::::::::::::: semi cone :::::::::::::::::::::::::::
void coneTranque(float R, float r, float h, int seg)
{
    float pas=2*M_PI/seg;
    float dr = R-r;
    glBegin(GL_QUAD_STRIP);
        //glNormal3f(0,1,0);
        //glVertex3f(0,h,0);
        float cosphi = float(h/sqrt(dr*dr+h*h));
        float sinphi = float(dr/sqrt(dr*dr+h*h));

        for(int i = 0; i <=seg; i++)
        {
            glNormal3f(cosphi*cos(i*pas),sinphi,cosphi*sin(i*pas));
            glVertex3f(R*cos(i*pas),0,R*sin(i*pas));
            glVertex3f(r*cos(i*pas),h,r*sin(i*pas));
        }
    glEnd();

}

//:::::::::::::::::::::::::::::::::::::::::::::: cone ::::::::::::::::::::::::::::::::::::
void cone(float r, float h, int seg)
{
    float pas=2*M_PI/seg;
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0,1,0);
        glVertex3f(0,h,0);
        float cosphi = float(h/sqrt(r*r+h*h));
        float sinphi = float(r/sqrt(r*r+h*h));

        for(int i = 0; i <=seg; i++)
        {
            glNormal3f(cosphi*cos(i*pas),sinphi,cosphi*sin(i*pas));
            glVertex3f(r*cos(i*pas),0,r*sin(i*pas));
        }
    glEnd();
}

/////::::::::::::::::::::::::::::::::::::::::::: cylindre ::::::::::::::::::::::::::::::::::::::::::

void cylindre (float r, float h, int seg)
{

    float pas = 2*M_PI/seg;
    glBegin(GL_QUAD_STRIP);
        for(int i = 0; i <=seg; i++)
        {
            //glNormal3f(cos(i*pas),h,sin(i*pas));
             glNormal3f(cos(i*pas),h,sin(i*pas));

            glVertex3f(r*cos(i*pas),0,r*sin(i*pas));
            glVertex3f(r*cos(i*pas),h,r*sin(i*pas));
        }
    glEnd();
}

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

struct Materiau
{
    float r,g,b;
    float spec;
    float lustre;//chining


}mat={0.2,0.2,1.0,0.9,100};

struct Lumiere
{
    float r,g,b;// rgb de couleur
    float x,y,z; // position source lumiere
    float type;

}lum={1,1,1,5,0,0,0};


void appliquerMateriau(const Materiau& m)
{
    float coul[4]={m.r,m.g,m.b,10};
    float sepec[4]={m.spec,m.spec,m.spec,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,coul);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,sepec);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,m.lustre);
}
void appliquerLumiere(const Lumiere& l)
{
    float ambiande[4]={0.2*l.r,0.2*l.g,0.2*l.b,1.0};
    float diff[4]={l.r,l.g,l.b,1.0};
    float spec[4]={0.9*l.r,0.9*l.g,0.9*l.b,1.0};
    float pos[4]={l.x,l.y,l.z,l.type};
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambiande);
    glLightfv(GL_LIGHT0  ,GL_DIFFUSE,diff);
    glLightfv(GL_LIGHT0  ,GL_SPECULAR,spec);
    glLightfv(GL_LIGHT0  ,GL_POSITION,pos);
}

////////////////////////////////////////////////////////////////////////////////
int r = 10;
float theta = 0, phi = 0;

bool AFF_GRILLE = false;
bool AFF_REPERE = true;
bool AFF_CONE = false;

void menuAffichage(int num)
{
    switch(num)
    {
        case 1:AFF_GRILLE = !AFF_GRILLE; break;
        case 2:AFF_REPERE = !AFF_REPERE; break;
        case 3:AFF_CONE = !AFF_CONE; break;
    }
    glutPostRedisplay();
}

void menuMode(int num)
{
    switch(num)
    {
         case 1: glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);break; // sommet
         case 2: glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);break; // filaire
         case 3: glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);break; // solid
    }
    glutPostRedisplay();
}

void menuArp(int num)
{
    switch(num)
    {
        case 1: glClearColor(0,0,0,1);break;
        case 2: glClearColor(0.75,0.75,0.75,1);break;
        case 3: glClearColor(1,1,1,1);break;

    }
    glutPostRedisplay();
}

void menuPrincipale(int num)
{
    switch(num)
    {
        case 0: exit(0); break;
    }
}

void creerMenu()
{
    int idaffichage = glutCreateMenu(menuAffichage);
    glutAddMenuEntry("Grille    G",1);
    glutAddMenuEntry("Repere    M",2);
    glutAddMenuEntry("Cone  R",3);

    int idMode = glutCreateMenu(menuMode);
    glutAddMenuEntry("Sommet",1);
    glutAddMenuEntry("Filaire",2);
    glutAddMenuEntry("Solid",3);

    int idArp = glutCreateMenu(menuArp);
    glutAddMenuEntry("Noire",1);
    glutAddMenuEntry("Gris",2);
    glutAddMenuEntry("Blanc",3);

    int idPrincipale = glutCreateMenu(menuPrincipale);
    glutAddSubMenu("Affichage",idaffichage);
    glutAddSubMenu("Mode",idMode);
    glutAddSubMenu("Arrier plan",idArp);
    glutAddMenuEntry("Quitter   Q",0);
    // associer la fonction pour le button droit de la souris
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

// var global
float sauv_r, sauv_phi, sauv_theta;
int sauv_x, sauv_y;
int sauv_button;
void grille(float a, int n)
{
    float pas = a/(n-1);
    glBegin(GL_LINES);
    glColor3f(0.75,0.75,0.75);
    float calcule1 = 0;
    for (int i = 0;i<n;i++)
    {
        calcule1 = (a/2)-(i*pas);
        glVertex3f(a/2,0,calcule1);
        glVertex3f(-a/2,0,calcule1);

        glVertex3f(calcule1,0,a/2);
        glVertex3f(calcule1,0,-a/2);
    }
    glEnd();
}
void click(int button, int etat, int x, int y)
{
    sauv_r = r;
    sauv_phi = phi;
    sauv_theta = theta;
    sauv_x = x;
    sauv_y = y;
    sauv_button = button;

}

void motion(int x, int y)
{
    if(sauv_button == GLUT_LEFT_BUTTON)
    {
        theta = sauv_theta+(x-sauv_x)*0.25;
        phi = sauv_phi+(y-sauv_y)*0.25;
        glutPostRedisplay();
    }else if(sauv_button == GLUT_MIDDLE_BUTTON)
    {
        r = sauv_r + 0.1*(y - sauv_y);
        glutPostRedisplay();
    }
}
// la personalisation  d'affichage
void orbite(float r, float theta, float phi)
{
    glTranslatef(0,0,-r);
    glRotatef(-phi,1,0,0);
    glRotatef(-theta,0,1,0);
}

void clavier(unsigned char key, int x, int y){
    switch(key){
        case '-': r+=1; break;
        case '+': if(r > 0.1) r-=0.1; break;
        case 'G':
        case 'g':menuAffichage(1);break;
        case 'R':
        case 'r': menuAffichage(2);break;
        case 'Q':
        case 'q':exit(0);break;
        default: r+0.1;break;
    }
    glutPostRedisplay();
}

void special(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:theta-=1;break;
        case GLUT_KEY_RIGHT:theta+=1;break;
        case GLUT_KEY_DOWN: phi++;break;
        case GLUT_KEY_UP: phi--;break;
    }
    glutPostRedisplay();
}


void Afficher(void){
    //Effacer l'image precedentre GL_COLOR_BUFFER_BIT
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //placer la caméra
    glMatrixMode(GL_MODELVIEW);//GLAPI void GLAPIENTRY glLoadMatrixd (const GLdouble *m);
    glLoadIdentity(); //travailler avec la matrice unite(I)

    orbite(r,theta,phi);

    //gluLookAt(1,2,3,0,0,0,0,1,0);

    //Afficher des objets
    //repere(1.0);
    //rectangle(1,0.5);
    //rectangle3D(1,0.5,0.5);
    if(AFF_REPERE)
       {
       repere(6);
       }

    if (AFF_CONE)
        cone(0.5,1,30);


   // cercle (0.5,40);
    //glColor3b(255,250,255);
    //commence par la transformation pour les objects qui suivent
    // x,y,z pour etilation
    int i=0;


// :::::::::::::::::::::::::::::::::::::::  exercice 2 ::::::::::::::::::::::::::::::
    /*glPushMatrix();
        //glTranslatef(-1,2,1);
        glRotated(45,0,1,0);
        glScalef(1,1,2);
        glutSolidSphere(0.25,100,100);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1,2,-2);
        glScalef(1,0.5,1);
        glutSolidCube(0.5);
    glPopMatrix();*/
  /*      glTranslatef(1,2,-2);
        glRotated(45,1,0,0);
        glutSolidCube(0.5);

    glPushMatrix();
        glRotatef(45,1,0,0);
        glTranslatef(1,2,-2);
        glutWireCube(0.5);
    glPopMatrix();*/
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// ::::::::::::::::::::::::::::::::::::::::: exercice 3 ::::::::::::::::::::::::::::
        //disk_traingle_fan(0.5,100);
        //disc(0.5,100);

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// ::::::::::::::::::::::::::::::::::::::::: exercice 5 ::::::::::::::::::::::::::::

        //sabalier(0.25,0.15,100);
        /*glBegin(GL_QUAD_STRIP);
        glVertex3f(0,0,1);
        glVertex3f(1,0,1);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(0,1,0);
        glVertex3f(1,1,0);
        glEnd();*/

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// ::::::::::::::::::::::::::::::::::::::::::::: Exam 2018 - 2019 ::::::::::::::::::::::::::
    //exrcice 2
    //glColor3f(100,0,0);
    //etoile(0.5,0.25,16);
    //exrcice 1
    //pyramid(0.25,0.5);
    //VersoPyramid(0.25,0.5);
    //approche1(0.25,0.25,0.5);
    //approche2(0.25,0.25,0.5);

    piece(2,1,5);
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


    //glPushMatrix();
        //glTranslatef(0.5,0,0);
        //glRotated(30,0,0,1);
        //glScalef(1,1,2);
        //cylindre(0.25,M_PI/12,100);
    //glPopMatrix();
    //glutWireCube(0.25);

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    i++;
// glutWireTeapot(0.25);
    //Terminer
    if (AFF_GRILLE)
        grille(5,20);
        //ourGrille(10,5);

        appliquerLumiere(lum);
        appliquerMateriau(mat);
        //glutSolidTeapot(0.5);

            //cone(0.25,M_PI/12,100);
        //coneTranque(2,1,1,100);

        //surfaceGraphique(1.5,0.5,2,30,30);
    //creerMenu();
    glFlush();
    glutSwapBuffers();
}

void Redim(int L,int H){ //redimensionner

    //définir la projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,(float)L/H,0.1,1000);

    //0 et 1 par defaut pour near et far
    //glOrtho(-1,1,-1*(float)H/L,1*(float)H/L,0.1,1000);

    //Portion de l'ecran(fenetre)
    glViewport(0,0,L,H);
}

int main(int argc, char **argv){
    //initialisation de glut et glew
    glutInit(&argc,argv);//st utilisé pour initialiser la bibliothèque GLUT.
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); //définit le mode d'affichage initial
    glutInitWindowSize(800,600); //définissent respectivement la position et la taille initiales de la fenêtre .
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL"); //crée une fenêtre de niveau supérieur.
    GLenum msg=glewInit();
    if(msg!=GLEW_OK){
        printf("Erreur: %s\n",glewGetErrorString(msg));
        exit(1);
    }else{
        printf("Version OpenGL %s\n",glGetString(GL_VERSION));
    }
    //fonction de Rappel
    glutDisplayFunc(Afficher); //uniqument un pointeur de fonction un appel sans parametre
    glutReshapeFunc(Redim);
    glutSpecialFunc(special);
    glutKeyboardFunc(clavier);
    glutMouseFunc(click);
    glutMotionFunc(motion);
    creerMenu();
    //Init de gl
    glClearColor(0,0,0,1); //la couleur d'effacement
    glEnable(GL_DEPTH);

    // activer la lumiere
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //La boucle des evenemensts
    glutMainLoop();

    return 0;
}
