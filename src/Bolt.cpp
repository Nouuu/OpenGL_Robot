#include "Bolt.h"
#include <string.h>

Bolt::Bolt(float scale, float posx, float posy, float posz, float angleX, float angleY, float angleZ) {
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;

    this->angleX = angleX;
    this->angleY = angleY;
    this->angleZ = angleZ;

    this->scale = scale;
}

void Bolt::Draw() {
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);

    glColor3f(1.0f, 0.9f, 0.f);

    glTranslatef(posx, posy, posz);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);

    glTranslatef(0.0f, 1.0f * scale, 0.0f);
    GLUquadricObj *pObj = gluNewQuadric();

    gluCylinder(pObj, 0.1f * scale, 0.1f * scale, 1.0f * scale, 32, 32);
    glTranslatef(0.0f, 0.0f, 1.0f * scale);
    gluCylinder(pObj, 0.2f * scale, 0.2f * scale, 0.1f * scale, 32, 32);
    gluDisk(pObj, 0.0f, 0.2f * scale, 32, 32);
    glTranslatef(0.0f, 0.0f, -1.0f * scale);
    /*  Pas de vise  */
    glColor3f(1.0f, 1.f, 0.f);

    for (int i = 0; i < 5; i += 1) {
        gluDisk(pObj, 0.0f, 0.15f * scale, 32, 32);
        glTranslatef(0.0f, 0.0f, 0.2f * scale);
    }
    glPopMatrix();
}

