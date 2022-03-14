#ifndef EXAM20182019_H_INCLUDED
#define EXAM20182019_H_INCLUDED

void etoile(float r, float R, int nb)
{
    float pas = 2*M_PI/nb;
    float x,z;
    int c=0;
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i<= nb; i++)
        {
            if(c==0)
            {
                x = r*cos(pas*i);
                z = r*sin(pas*i);
                c = 1;
            }else
            {
                x = R*cos(pas*i);
                z = R*sin(pas*i);
                c = 0;
            }
            glVertex3f(x,0,z);

        }
    glEnd();
}

void etoile_2(float r, float R, int nb)
{
    float pas = 2*M_PI/nb;
    float x,z;
    int c=0;
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i< nb; i+=2)
        {
            glVertex3f(r*cos(pas*i),0,r*sin(pas*i));
            glVertex3f(R*cos(pas*(i+1)),0,R*sin(pas*(i+1)));
        }
    glEnd();
}


void pyramid(float c, float h)
{
    float pas = M_PI*2/4;
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0,1,0);
    glVertex3f(0,h,0);

    float r = c/sqrt(2);

    float cosphi = float(h/sqrt(r*r+h*h));
    float sinphi = float(r/sqrt(r*r+h*h));

    for(int i = 0; i<= 4;i++)
    {
        glNormal3f(cosphi*cos(i*pas),sinphi,cosphi*sin(i*pas));
        glVertex3f(r*cos(pas*i),0,r*sin(pas*i));
    }
    glEnd();

}
void VersoPyramid1(float c, float h)
{
    pyramid(c,h);
    glPushMatrix();
        glRotatef(180,1,0,0);
        pyramid(c,h);
    glPopMatrix();

}

void VersoPyramid2(float c, float h)
{
    pyramid(c,h);
    pyramid(c,-h);
}
void approche1(float c, float h,float d)
{

    VersoPyramid2(c, h);

    glPushMatrix();
    glTranslatef(d,0,0);
    VersoPyramid2(c, h);
    glPopMatrix();

      glPushMatrix();
        glTranslatef(0,0,d);
           VersoPyramid2(c, h);
    glPopMatrix();

      glPushMatrix();
        glTranslatef(d,0,d);
           VersoPyramid2(c, h);
    glPopMatrix();


}

void approche2(float c, float h,float d)
{
    int nb=4;
    float pas = 2*M_PI/nb;


    float rayon = d/sqrt(2);
    for(int  i = 0; i <= nb ; i++)
    {
        glPushMatrix();
            glTranslatef(rayon*cos(pas*i),0,rayon*sin(pas*i));
            VersoPyramid2(c,h);
        glPopMatrix();
    }

}

void ourGrille(int nb, float pas)
{
    glBegin(GL_LINES);

    float c = pas*nb/2;
    for (int  i = 0; i <= nb ; i++)
    {
        glVertex3f(c,0,c-pas*i);
        glVertex3f(-c,0,c-pas*i);
    }

     for (int  i = 0; i <= nb ; i++)
    {
        glVertex3f(c-pas*i,0,c);
        glVertex3f(c-pas*i,0,-c);
    }

    glEnd();
}

void piece(float R, float r, int nb)
{
    float pas = (2*M_PI)/(nb*2);
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i <= nb*2; i+=2)
    {
        glVertex3f(R*cos(pas*i),0,R*sin(pas*i));
        glVertex3f(r*cos(pas*i),0,r*sin(pas*i));

        glVertex3f(r*cos(pas*(i+1)),0,r*sin(pas*(i+1)));
        glVertex3f(R*cos(pas*(i+1)),0,R*sin(pas*(i+1)));
    }
    glEnd();

}
#endif // EXAM20182019_H_INCLUDED
