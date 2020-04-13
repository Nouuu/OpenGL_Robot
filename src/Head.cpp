#include "Head.h"

Head::Head() {
    posx = 0.0f;
    posy = 0.5f;
    posz = 0.0f;

    rotx = 0.0f;
    roty = 0.0f;
    rotz = 0.0f;

    scale = 1.f;

    shoulderRotation = -10.f;
    forearmRotation = 15.f;

    for (int i = 0; i < 6; i++) {
        textures[i] = 0;
    }
}

Head::Head(float scale, float posx, float posy, float posz, float rotx, float roty, float rotz) {
    this->rotx = rotx;
    this->roty = roty;
    this->rotz = rotz;
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;

    this->scale = scale;

    shoulderRotation = -10.f;
    forearmRotation = 15.f;

    for (int i = 0; i < 6; i++) {
        textures[i] = 0;
    }
}

void Head::Draw() {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLUquadricObj* params_cylindre = gluNewQuadric();
    GLUquadric* params_sphere = gluNewQuadric();
    GLUquadric* params_oeil = gluNewQuadric();

    glColor3f(0.6, 0.6, 0.6);
    glTranslatef(0.0, 0.0, 7.0);

    drawHalfSphere(20, 20, 4.7);

    glColor3f(0.3, 0.3, 0.3);
    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(180, 1.0, 0.0, 0.0);

    drawHalfSphere(20, 20, 5);

    glColor3f(1.0, 0.1, 0.1);
    glTranslatef(0.0, -7.0, 0.0);
    gluSphere(params_sphere,0.4,10,10);

    glColor3f(0.6, 0.6, 0.6);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, -3.0);

    gluCylinder(params_cylindre,0.1f,0.1f,3.0f,32,32);

    glColor3f(0.2, 1.0, 0.2);
    glTranslatef(3.0, -1.4, -1.0);

    gluSphere(params_sphere,0.7,10,10);

    glTranslatef(0.0, 2.8, 0.0);

    gluSphere(params_sphere,0.7,10,10);
    glPopMatrix();
}

/*
    scalex - scaling of sphere around x-axis
   scaley - scaling of sphere around y-axis
   rayon - radius of sphere
*/
void Head::drawHalfSphere(int scaley, int scalex, GLfloat rayon) {
   int i, j;
   GLfloat data[scalex*scaley][3];

   /*
   construction du tableau
   */
   for (i=0; i<scalex; i += 1) {
        for (j=0; j<scaley; j += 1) {
        data[i*scaley+j][0]=rayon*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
        data[i*scaley+j][1]=rayon*sin(i*M_PI/(2*scalex));
        data[i*scaley+j][2]=rayon*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
        }
    }
    /*
    Construction de la sphère
    */
    glBegin(GL_QUADS);
        for (i=0; i<scalex-1; i += 1) {
            for (j=0; j<scaley; j += 1) {
                glVertex3fv(data[i*scaley+j]);
                glVertex3fv(data[i*scaley+(j+1)%scaley]);
                glVertex3fv(data[(i+1)*scaley+(j+1)%scaley]);
                glVertex3fv(data[(i+1)*scaley+j]);
            }
        }
    glEnd();
 }
