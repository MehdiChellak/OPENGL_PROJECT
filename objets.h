#ifndef OBJETS_H_INCLUDED
#define OBJETS_H_INCLUDED
#include<math.h>

void repere(float a)
{

    glBegin(GL_LINES);
    glColor3f(100,10,20);
    glVertex3f(0, 0, 0);
    glVertex3f(a, 0, 0);

    glColor3f(10,100,10);
    glVertex3f(0, 0, 0);
    glVertex3f(0, a, 0);

    /*glColor3f(10,100,0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, a);*/

    glEnd();
}

void rectangle(float L,float H, float p){
    glColor3b(100,50,100);

    glBegin(GL_LINE_LOOP);
        glVertex3f(-L/2,0,p);//a
        glVertex3f(-L/2,H,p);//b
        glVertex3f(L/2,H,p);//c
        glVertex3f(L/2,0,p);//d
    glEnd();
}

void rectangle3D(float L, float H, float p)
{
    rectangle(L,H,0);
    rectangle(L,H,p);


    glBegin(GL_LINES);
        glColor3b(100,50,100);

        glVertex3f(-L/2,0,0);//a
        glVertex3f(-L/2,0,p);//a

        glVertex3f(-L/2,H,0);//b
        glVertex3f(-L/2,H,p);//b

        glVertex3f(L/2,H,0);//c
        glVertex3f(L/2,H,p);//c

        glVertex3f(L/2,0,0);//d
        glVertex3f(L/2,0,p);//d;
    glEnd();
}
void cercle(float r, int seg)
{
    int i = 0;
    glBegin(GL_LINE_LOOP);
    float theta = 2*M_PI/seg;
    float x,y;
    for (i = 0; i < seg; i++)
    {
        x = cos(i*theta)*r;
        y = sin(i*theta)*r;

        glVertex3f(cos(i*theta)*r,sin(i*theta)*r,0);
        //theta+=theta;
    }
    glEnd();
}

void Cercle3D(float r,int seg){
    float theta=2*M_PI/seg;
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<=seg;i++){
        glVertex3f(r*cos(i*theta),0,r*sin(i*theta));
    }
    glEnd();
}

void disc(float r,int seg){
    float theta=2*M_PI/seg;
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=seg;i++){
        glVertex3f(r*cos(i*theta),0,r*sin(i*theta));
        glVertex3f(0,0,0);
    }
    glEnd();
}

void disk_traingle_fan(float r,int seg)
{
    float pas  = 2*M_PI/seg;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,0);
    for(int i; i<= seg; i++)
    {
        glNormal3f(1,0,0);
        glVertex3f(0,r*cos(i*pas),r*sin(i*pas));
    }
    glEnd();
}

void demi_Cercle3D(float r,int seg){
    float theta=M_PI/seg;
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<=seg;i++){
        glVertex3f(r*cos(i*theta),r*sin(i*theta),0);
    }
    glEnd();
}

// exetcice 5
void coneTranque1(float R, float r, float h, int seg)
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
            glVertex3f(r*cos(i*pas),h,r*sin(i*pas));
            glVertex3f(R*cos(i*pas),0,R*sin(i*pas));
        }
    glEnd();

}
void sabalier(float r,float h, int seg)
{

    glPushMatrix();
        coneTranque1(r,r/4,h,seg);
         disc(r,seg);
    glPopMatrix();

     glPushMatrix();
        glTranslatef(0,2*h,0);
        glRotatef(180,0,0,1);
        coneTranque1(r,r/4,h,seg);
        disc(r,seg);
    glPopMatrix();

}

#endif // OBJETS_H_INCLUDED
