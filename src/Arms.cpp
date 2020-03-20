//
// Created by Unknow on 20/03/2020.
//

#include "Arms.h"

Arms::Arms() {
    posx = 0.0f;
    posy = 0.0f;
    posz = 0.0f;

    x = 2.0f;
    y = 1.0f;
    z = 0.5f;

    for (int i = 0; i < 6; i++) {
        textures[i] = 0;
    }
}

Arms::Arms(float x, float y, float z, float posx, float posy, float posz) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;

    for (int i = 0; i < 6; i++) {
        textures[i] = 0;
    }
}

void Arms::Draw() {
    glEnable(GL_TEXTURE_2D);
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();

    /** Epaule **/
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLUquadric *pObj = gluNewQuadric();
    gluQuadricTexture(pObj, GLU_TRUE);
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
//    glRotatef(90, 1.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.25f, 0.25f, 0.25f, 32, 32);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluDisk(pObj, 0.0f, 0.25f, 32, 32);
    glTranslatef(0.0f, 0.0f, 0.25f);
    glColor3f(0.0f, 0.0f, 1.0f);
    gluDisk(pObj, 0.0f, 0.25f, 32, 32);

    glPopMatrix();


}

void Arms::SetTexture(int index, GLuint texture) {
    textures[index] = texture;
}


float Arms::getPosx() const {
    return posx;
}

void Arms::setPosx(float posx) {
    Arms::posx = posx;
}

float Arms::getPosy() const {
    return posy;
}

void Arms::setPosy(float posy) {
    Arms::posy = posy;
}

float Arms::getPosz() const {
    return posz;
}

void Arms::setPosz(float posz) {
    Arms::posz = posz;
}

float Arms::getX() const {
    return x;
}

void Arms::setX(float x) {
    Arms::x = x;
}

float Arms::getY() const {
    return y;
}

void Arms::setY(float y) {
    Arms::y = y;
}

float Arms::getZ() const {
    return z;
}

void Arms::setZ(float z) {
    Arms::z = z;
}

const GLuint *Arms::getTextures() const {
    return textures;
}
