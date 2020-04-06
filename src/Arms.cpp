//
// Created by Unknow on 20/03/2020.
//

#include "Arms.h"

Arms::Arms() {
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

Arms::Arms(float scale, float posx, float posy, float posz, float rotx, float roty, float rotz) {
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

void Arms::Draw() {
    glEnable(GL_TEXTURE_2D);
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
    glTranslatef(posx, posy, posz);
    //TODO Appliquer le scale partout
    
    // EPAULE
    DrawShoulder(pObj);

    // BRAS SUPERIEUR
    DrawUpperarm(pObj);

    // COUDE
    DrawElbow(pObj);

    // BRAS INFERIEUR
    DrawForearm(pObj);
    //MAIN
    DrawHand(pObj);

    gluDeleteQuadric(pObj);
    glPopMatrix();


}

void Arms::DrawShoulder(GLUquadric *pObj) {
    glColor3f(0.5f, 0.5f, 0.5f);
    gluCylinder(pObj, 0.25f, 0.25f, 0.15f, 32, 32);
    gluDisk(pObj, 0.15f, 0.25f, 32, 32);
    glTranslatef(0.f, 0.f, 0.1f);
    glColor3f(0.35f, 0.35f, 0.35f);
    gluSphere(pObj, 0.20f, 32, 32);
}

void Arms::DrawUpperarm(GLUquadric *pObj) {
    glRotatef(shoulderRotation, 0.f, 0.f, 1.f); // ROTATION BRAS SUPERIEUR JOINTURE EPAULE
    glTranslatef(0.f, -0.22f, -0.025f);
    glRotatef(90, 1.f, 0.f, 0.f);
    glColor3f(0.2f, 0.2f, 0.2f);
    gluCylinder(pObj, 0.07f, 0.07f, 0.3f, 32, 32);
}

void Arms::DrawElbow(GLUquadric *pObj) {
    glTranslatef(0.f, 0.075f, 0.3f);
    glRotatef(90, 1.f, 0.f, 0.f);
    gluCylinder(pObj, 0.1f, 0.1f, 0.15f, 32, 32);
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(0.f, 0.f, 0.05f);
    gluSphere(pObj, 0.1f, 32, 32);
    glTranslatef(0.f, 0.f, 0.05f);
    gluSphere(pObj, 0.1f, 32, 32);
}

void Arms::DrawForearm(GLUquadric *pObj) {
    glTranslatef(0.f, 0.f, -0.1f);
    glRotatef(-90, 1.f, 0.f, 0.f);
    glRotatef(forearmRotation, 0.f, 1.f, 0.f); // ROTATION BRAS INFERIEUR JOINTURE EPAULE
    glTranslatef(0.f, -0.075f, 0.05f);
    glColor3f(0.2f, 0.2f, 0.2f);
    gluCylinder(pObj, 0.07f, 0.07f, 0.3f, 32, 32);
}

void Arms::DrawHand(GLUquadric *pObj) {
    // MAIN
    glRotatef(180, 0.f, 0.f, 1.f); // ROTATION POIGNET
    glTranslatef(0.f, 0.07f, 0.26f);

    //BOULON
    glTranslatef(0.f, -0.07f, 0.12f);
    gluSphere(pObj, 0.1f, 32, 32);
    glTranslatef(0.f, 0.07f, -0.12f);

    //AVANT
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
    glVertex3d(0.f, 0.f, 0.f);
    glVertex3d(0.15f, 0.f, 0.05f);
    glVertex3d(0.15f, 0.f, 0.4f);
    glVertex3d(0.f, 0.f, 0.4f);

    glVertex3d(0.15f, 0.f, 0.05f);
    glVertex3d(0.20f, 0.f, 0.15f);
    glVertex3d(0.2f, 0.f, 0.4f);
    glVertex3d(0.15f, 0.f, 0.4f);

    glVertex3d(0.f, 0.f, 0.f);
    glVertex3d(-0.15f, 0.f, 0.05f);
    glVertex3d(-0.15f, 0.f, 0.4f);
    glVertex3d(0.f, 0.f, 0.4f);

    glVertex3d(-0.15f, 0.f, 0.05f);
    glVertex3d(-0.20f, 0.f, 0.15f);
    glVertex3d(-0.2f, 0.f, 0.4f);
    glVertex3d(-0.15f, 0.f, 0.4f);

    // ARRIERE
    glVertex3d(0.f, -0.14f, 0.f);
    glVertex3d(0.15f, -0.14f, 0.05f);
    glVertex3d(0.15f, -0.14f, 0.4f);
    glVertex3d(0.f, -0.14f, 0.4f);

    glVertex3d(0.15f, -0.14f, 0.05f);
    glVertex3d(0.2f, -0.14f, 0.15f);
    glVertex3d(0.2f, -0.14f, 0.4f);
    glVertex3d(0.15f, -0.14f, 0.4f);

    glVertex3d(0.f, -0.14f, 0.f);
    glVertex3d(-0.15f, -0.14f, 0.05f);
    glVertex3d(-0.15f, -0.14f, 0.4f);
    glVertex3d(0.f, -0.14f, 0.4f);

    glVertex3d(-0.15f, -0.14f, 0.05f);
    glVertex3d(-0.20f, -0.14f, 0.15f);
    glVertex3d(-0.2f, -0.14f, 0.4f);
    glVertex3d(-0.15f, -0.14f, 0.4f);

    //CONTOURS
    glVertex3d(0.f, 0.f, 0.f);
    glVertex3d(0.f, -0.14f, 0.f);
    glVertex3d(0.15f, -0.14f, 0.05f);
    glVertex3d(0.15f, 0.f, 0.05f);

    glVertex3d(0.15f, 0.f, 0.05f);
    glVertex3d(0.15f, -0.14f, 0.05f);
    glVertex3d(0.2f, -0.14f, 0.15f);
    glVertex3d(0.2f, 0.f, 0.15f);

    glVertex3d(0.2f, 0.f, 0.15f);
    glVertex3d(0.2f, -0.14f, 0.15f);
    glVertex3d(0.2f, -0.14f, 0.4f);
    glVertex3d(0.2f, 0.f, 0.4f);

    glVertex3d(0.f, 0.f, 0.f);
    glVertex3d(0.f, -0.14f, 0.f);
    glVertex3d(-0.15f, -0.14f, 0.05f);
    glVertex3d(-0.15f, 0.f, 0.05f);

    glVertex3d(-0.15f, 0.f, 0.05f);
    glVertex3d(-0.15f, -0.14f, 0.05f);
    glVertex3d(-0.2f, -0.14f, 0.15f);
    glVertex3d(-0.2f, 0.f, 0.15f);

    glVertex3d(-0.2f, 0.f, 0.15f);
    glVertex3d(-0.2f, -0.14f, 0.15f);
    glVertex3d(-0.2f, -0.14f, 0.4f);
    glVertex3d(-0.2f, 0.f, 0.4f);

    glVertex3d(0.2f, 0.f, 0.4f);
    glVertex3d(0.2f, -0.14f, 0.4f);
    glVertex3d(-0.2f, -0.14f, 0.4f);
    glVertex3d(-0.2f, 0.f, 0.4f);
    glEnd();

    glTranslatef(0.f, 0.f, 0.4f);

    // DOIGTS
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    //1
    //AVANT
    glVertex3d(0.025f, -0.02f, 0.f);
    glVertex3d(0.175f, -0.02f, 0.f);
    glVertex3d(0.175f, -0.02f, 0.15f);
    glVertex3d(0.025f, -0.02f, 0.15f);

    glVertex3d(0.025f, -0.02f, 0.15f);
    glVertex3d(0.175f, -0.02f, 0.15f);
    glVertex3d(0.13f, -0.02f, 0.25f);
    glVertex3d(0.07f, -0.02f, 0.25f);

    //ARRIERE
    glVertex3d(0.025f, -0.12f, 0.f);
    glVertex3d(0.175f, -0.12f, 0.f);
    glVertex3d(0.175f, -0.12f, 0.15f);
    glVertex3d(0.025f, -0.12f, 0.15f);

    glVertex3d(0.025f, -0.12f, 0.15f);
    glVertex3d(0.175f, -0.12f, 0.15f);
    glVertex3d(0.13f, -0.12f, 0.25f);
    glVertex3d(0.07f, -0.12f, 0.25f);

    //CONTOURS
    glVertex3d(0.025f, -0.02f, 0.f);
    glVertex3d(0.025f, -0.12f, 0.f);
    glVertex3d(0.025f, -0.12f, 0.15f);
    glVertex3d(0.025f, -0.02f, 0.15f);

    glVertex3d(0.175f, -0.02f, 0.f);
    glVertex3d(0.175f, -0.12f, 0.f);
    glVertex3d(0.175f, -0.12f, 0.15f);
    glVertex3d(0.175f, -0.02f, 0.15f);

    glVertex3d(0.025f, -0.02f, 0.15f);
    glVertex3d(0.025f, -0.12f, 0.15f);
    glVertex3d(0.07f, -0.12f, 0.25f);
    glVertex3d(0.07f, -0.02f, 0.25f);

    glVertex3d(0.175f, -0.02f, 0.15f);
    glVertex3d(0.175f, -0.12f, 0.15f);
    glVertex3d(0.13f, -0.12f, 0.25f);
    glVertex3d(0.13f, -0.02f, 0.25f);

    glVertex3d(0.13f, -0.12f, 0.25f);
    glVertex3d(0.13f, -0.02f, 0.25f);
    glVertex3d(0.07f, -0.02f, 0.25f);
    glVertex3d(0.07f, -0.12f, 0.25f);

    //2
    //AVANT
    glVertex3d(-0.175f, -0.02f, 0.f);
    glVertex3d(-0.025, -0.02f, 0.f);
    glVertex3d(-0.025, -0.02f, 0.15f);
    glVertex3d(-0.175, -0.02f, 0.15f);

    glVertex3d(-0.175f, -0.02f, 0.15f);
    glVertex3d(-0.025f, -0.02f, 0.15f);
    glVertex3d(-0.07f, -0.02f, 0.25f);
    glVertex3d(-0.13f, -0.02f, 0.25f);

    //ARRIERE
    glVertex3d(-0.025f, -0.12f, 0.f);
    glVertex3d(-0.175f, -0.12f, 0.f);
    glVertex3d(-0.175f, -0.12f, 0.15f);
    glVertex3d(-0.025f, -0.12f, 0.15f);

    glVertex3d(-0.025f, -0.12f, 0.15f);
    glVertex3d(-0.175f, -0.12f, 0.15f);
    glVertex3d(-0.13f, -0.12f, 0.25f);
    glVertex3d(-0.07f, -0.12f, 0.25f);

    //CONTOURS
    glVertex3d(-0.025f, -0.02f, 0.f);
    glVertex3d(-0.025f, -0.12f, 0.f);
    glVertex3d(-0.025f, -0.12f, 0.15f);
    glVertex3d(-0.025f, -0.02f, 0.15f);

    glVertex3d(-0.175f, -0.02f, 0.f);
    glVertex3d(-0.175f, -0.12f, 0.f);
    glVertex3d(-0.175f, -0.12f, 0.15f);
    glVertex3d(-0.175f, -0.02f, 0.15f);

    glVertex3d(-0.025f, -0.02f, 0.15f);
    glVertex3d(-0.025f, -0.12f, 0.15f);
    glVertex3d(-0.07f, -0.12f, 0.25f);
    glVertex3d(-0.07f, -0.02f, 0.25f);

    glVertex3d(-0.175f, -0.02f, 0.15f);
    glVertex3d(-0.175f, -0.12f, 0.15f);
    glVertex3d(-0.13f, -0.12f, 0.25f);
    glVertex3d(-0.13f, -0.02f, 0.25f);

    glVertex3d(-0.13f, -0.12f, 0.25f);
    glVertex3d(-0.13f, -0.02f, 0.25f);
    glVertex3d(-0.07f, -0.02f, 0.25f);
    glVertex3d(-0.07f, -0.12f, 0.25f);

    //3
    //AVANT
    glVertex3d(-0.2f, -0.02f, -0.25f);
    glVertex3d(-0.2f, -0.02f, -0.05f);
    glVertex3d(-0.32f, -0.02f, 0.1f);
    glVertex3d(-0.37f, -0.02f, -0.05f);

    //ARRIERE
    glVertex3d(-0.2f, -0.12f, -0.25f);
    glVertex3d(-0.2f, -0.12f, -0.05f);
    glVertex3d(-0.32f, -0.12f, 0.1f);
    glVertex3d(-0.37f, -0.12f, -0.05f);

    //CONTOURS
    glVertex3d(-0.37f, -0.02f, -0.05f);
    glVertex3d(-0.2f, -0.02f, -0.25f);
    glVertex3d(-0.2f, -0.12f, -0.25f);
    glVertex3d(-0.37f, -0.12f, -0.05f);

    glVertex3d(-0.2f, -0.02f, -0.05f);
    glVertex3d(-0.32f, -0.02f, 0.1f);
    glVertex3d(-0.32f, -0.12f, 0.1f);
    glVertex3d(-0.2f, -0.12f, -0.05f);

    glVertex3d(-0.37f, -0.02f, -0.05f);
    glVertex3d(-0.32f, -0.02f, 0.1f);
    glVertex3d(-0.32f, -0.12f, 0.1f);
    glVertex3d(-0.37f, -0.12f, -0.05f);


    glEnd();

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

const GLuint *Arms::getTextures() const {
    return textures;
}

float Arms::getRotx() const {
    return rotx;
}

void Arms::setRotx(float rotx) {
    Arms::rotx = rotx;
}

float Arms::getRoty() const {
    return roty;
}

void Arms::setRoty(float roty) {
    Arms::roty = roty;
}

float Arms::getRotz() const {
    return rotz;
}

void Arms::setRotz(float rotz) {
    Arms::rotz = rotz;
}

float Arms::getScale() const {
    return scale;
}

void Arms::setScale(float scale) {
    Arms::scale = scale;
}

float Arms::getShoulderRotation() const {
    return shoulderRotation;
}

void Arms::setShoulderRotation(float shoulderRotation) {
    Arms::shoulderRotation = shoulderRotation;
}

float Arms::getForearmRotation() const {
    return forearmRotation;
}

void Arms::setForearmRotation(float forearmRotation) {
    Arms::forearmRotation = forearmRotation;
}
