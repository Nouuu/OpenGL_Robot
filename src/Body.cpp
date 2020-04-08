//
// Created by Unknow on 08/04/2020.
//

#include "Body.h"

Body::Body() {
    posx = 0.0f;
    posy = 0.5f;
    posz = 0.0f;

    rotx = 0.0f;
    roty = 0.0f;
    rotz = 0.0f;

    scale = 1.f;

    ConstructDefault();
}

Body::Body(float scale, float posx, float posy, float posz, float rotx, float roty, float rotz) {
    this->rotx = rotx;
    this->roty = roty;
    this->rotz = rotz;
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;

    this->scale = scale;

    ConstructDefault();
}

void Body::ConstructDefault() {

    for (int i = 0; i < 6; i++) {
        textures[i] = 0;
    }
}

void Body::Draw() {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    /** Corps **/

    GLUquadric *pObj = gluNewQuadric();
    gluQuadricTexture(pObj, GLU_TRUE);
    glPushMatrix();
    glTranslatef(posx, posy, posz);

    DrawInterior(pObj);

    DrawExterior(pObj);
}

void Body::DrawInterior(GLUquadric *pObj) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    //Face Avant
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.f, 0.f, 0.f);
    glTexCoord2f(1.f, 0.0f);
    glVertex3d(0.3f, 0.f, 0.f);
    glTexCoord2f(1.f, 1.f);
    glVertex3d(0.3f, 0.3f, 0.f);
    glTexCoord2f(0.0f, 1.f);
    glVertex3d(0.f, 0.3f, 0.f);

    //Face Arrière
    glTexCoord2f(0.0f, 0.0f);

    glVertex3d(0.f, 0.f, 0.15f);
    glTexCoord2f(1.f, 0.0f);
    glVertex3d(0.3f, 0.f, 0.15f);
    glTexCoord2f(1.f, 1.f);
    glVertex3d(0.3f, 0.3f, 0.15f);
    glTexCoord2f(0.0f, 1.f);
    glVertex3d(0.f, 0.3f, 0.15f);

    //Face Dessous
    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.f, 0.f, 0.f);
    glTexCoord2f(1.f, 0.0f);
    glVertex3d(0.3f, 0.f, 0.f);
    glTexCoord2f(1.f, 0.5f);
    glVertex3d(0.3f, 0.f, 0.15f);
    glTexCoord2f(0.0f, 0.5f);
    glVertex3d(0.f, 0.f, 0.15f);

    //Face côtés
    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.f, 0.f, 0.f);
    glTexCoord2f(0.5f, 0.0f);
    glVertex3d(0.f, 0.3f, 0.f);
    glTexCoord2f(0.5f, 1.f);
    glVertex3d(0.f, 0.3f, 0.15f);
    glTexCoord2f(0.0f, 1.f);
    glVertex3d(0.f, 0.f, 0.15f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.3f, 0.f, 0.f);
    glTexCoord2f(0.5f, 0.0f);
    glVertex3d(0.3f, 0.3f, 0.f);
    glTexCoord2f(0.5f, 1.f);
    glVertex3d(0.3f, 0.3f, 0.15f);
    glTexCoord2f(0.0f, 1.f);
    glVertex3d(0.3f, 0.f, 0.15f);
    glEnd();

    glTranslatef(0.f, 0.3f, 0.075f);
    glRotatef(90, 0.f, 1.f, 0.f);
    gluCylinder(pObj, 0.075f, 0.075f, 0.3f, 32, 32);
    glColor3f(0.5f, 0.5f, 0.3f);
    gluDisk(pObj, 0.f, 0.075f, 32, 32);
    glTranslatef(0.f, 0.f, 0.3f);
    gluDisk(pObj, 0.f, 0.075f, 32, 32);

    glRotatef(-90, 0.f, 1.f, 0.f);
    glTranslatef(-0.3f, -0.3f, -0.075f);

}

void Body::DrawExterior(GLUquadric *pObj) {

    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


    glBegin(GL_QUADS);
//    glColor3f(0.5f, 0.5f, 0.5f);

    //AVANT
    glTexCoord2f(0.f, 0.f);
    glVertex3d(-0.01f, 0.f, -0.01f);
    glTexCoord2f(0.5f, 0.f);
    glVertex3d(0.31f, 0.f, -0.01f);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3d(0.31f, 0.05f, -0.01f);
    glTexCoord2f(0.f, 0.5f);
    glVertex3d(-0.01f, 0.05f, -0.01f);

    glTexCoord2f(0.f, 0.f);
    glVertex3d(-0.01f, 0.05f, -0.01f);
    glTexCoord2f(1.f, 0.f);
    glVertex3d(0.31f, 0.05f, -0.01f);
    glTexCoord2f(1.f, 1.f);
    glVertex3d(0.3f, 0.3f, -0.01f);
    glTexCoord2f(0.f, 1.f);
    glVertex3d(0.f, 0.3f, -0.01f);

    //ARRIERE
    glTexCoord2f(0.f, 0.f);
    glVertex3d(-0.01f, 0.f, 0.16f);
    glTexCoord2f(0.5f, 0.f);
    glVertex3d(0.31f, 0.f, 0.16f);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3d(0.31f, 0.05f, 0.16f);
    glTexCoord2f(0.f, 0.5f);
    glVertex3d(-0.01f, 0.05f, 0.16f);

    glTexCoord2f(0.f, 0.f);
    glVertex3d(-0.01f, 0.05f, 0.16f);
    glTexCoord2f(1.f, 0.f);
    glVertex3d(0.31f, 0.05f, 0.16f);
    glTexCoord2f(1.f, 1.f);
    glVertex3d(0.3f, 0.3f, 0.16f);
    glTexCoord2f(0.f, 1.f);
    glVertex3d(0.f, 0.3f, 0.16f);

    //COTES BAS
    glTexCoord2f(0.f, 0.f);
    glVertex3d(-0.01f, 0.f, -0.01f);
    glTexCoord2f(0.5f, 0.f);
    glVertex3d(-0.01f, 0.05f, -0.01f);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3d(-0.01f, 0.05f, 0.16f);
    glTexCoord2f(0.f, 0.5f);
    glVertex3d(-0.01f, 0.f, 0.16f);

    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.31f, 0.f, -0.01f);
    glTexCoord2f(0.5f, 0.f);
    glVertex3d(0.31f, 0.05f, -0.01f);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3d(0.31f, 0.05f, 0.16f);
    glTexCoord2f(0.f, 0.5f);
    glVertex3d(0.31f, 0.f, 0.16f);

    // SURFACE BAS

    glTexCoord2f(0.f, 0.f);
    glVertex3d(-0.01f, 0.05f, -0.01f);
    glTexCoord2f(1.f, 0.f);
    glVertex3d(0.31f, 0.05f, -0.01f);
    glTexCoord2f(1.f, 1.f);
    glVertex3d(0.31f, 0.05f, 0.16f);
    glTexCoord2f(0.f, 1.f);
    glVertex3d(-0.01f, 0.05f, 0.16f);

    glEnd();

    //DESSUS EPAULE G
    glBegin(GL_QUAD_STRIP);
    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.f, 0.3f, -0.01f);
    glTexCoord2f(0.1f, 0.f);
    glVertex3d(0.06f, 0.3f, -0.01f);

    glTexCoord2f(0.f, 0.1f);
    glVertex3d(0.f, 0.32f, -0.005f);
    glTexCoord2f(0.1f, 0.1f);
    glVertex3d(0.06f, 0.32f, -0.005f);

    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.f, 0.34f, 0.005f);
    glTexCoord2f(0.1f, 0.f);
    glVertex3d(0.06f, 0.34f, 0.005f);

    glTexCoord2f(0.f, 0.1f);
    glVertex3d(0.f, 0.36f, 0.02f);
    glTexCoord2f(0.1f, 0.1f);
    glVertex3d(0.06f, 0.36f, 0.02f);

    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.f, 0.37f, 0.045f);
    glTexCoord2f(0.1f, 0.f);
    glVertex3d(0.06f, 0.37f, 0.045f);
/////////////////////////////////////////////////////////
    glTexCoord2f(0.f, 0.1f);
    glVertex3d(0.f, 0.38f, 0.075f);
    glTexCoord2f(0.1f, 0.1f);
    glVertex3d(0.06f, 0.38f, 0.075f);
/////////////////////////////////////////////////////////
    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.f, 0.37f, 0.105f);
    glTexCoord2f(0.1f, 0.f);
    glVertex3d(0.06f, 0.37f, 0.105f);

    glTexCoord2f(0.f, 0.1f);
    glVertex3d(0.f, 0.36f, 0.13f);
    glTexCoord2f(0.1f, 0.1f);
    glVertex3d(0.06f, 0.36f, 0.13f);

    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.f, 0.34f, 0.145f);
    glTexCoord2f(0.1f, 0.f);
    glVertex3d(0.06f, 0.34f, 0.145f);

    glTexCoord2f(0.f, 0.1f);
    glVertex3d(0.f, 0.32f, 0.155f);
    glTexCoord2f(0.1f, 0.1f);
    glVertex3d(0.06f, 0.32f, 0.155f);

    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.f, 0.3f, 0.16f);
    glTexCoord2f(0.1f, 0.f);
    glVertex3d(0.06f, 0.3f, 0.16f);
    glEnd();

    //DESSUS EPAULE D
    glBegin(GL_QUAD_STRIP);
    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.24f, 0.3f, -0.01f);
    glTexCoord2f(0.1f, 0.f);
    glVertex3d(0.3f, 0.3f, -0.01f);

    glTexCoord2f(0.f, 0.1f);
    glVertex3d(0.24f, 0.32f, -0.005f);
    glTexCoord2f(0.1f, 0.1f);
    glVertex3d(0.3f, 0.32f, -0.005f);

    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.24f, 0.34f, 0.005f);
    glTexCoord2f(0.1f, 0.f);
    glVertex3d(0.3f, 0.34f, 0.005f);

    glTexCoord2f(0.f, 0.1f);
    glVertex3d(0.24f, 0.36f, 0.02f);
    glTexCoord2f(0.1f, 0.1f);
    glVertex3d(0.3f, 0.36f, 0.02f);

    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.24f, 0.37f, 0.045f);
    glTexCoord2f(0.1f, 0.f);
    glVertex3d(0.3f, 0.37f, 0.045f);
/////////////////////////////////////////////////////////
    glTexCoord2f(0.f, 0.1f);
    glVertex3d(0.24f, 0.38f, 0.075f);
    glTexCoord2f(0.1f, 0.1f);
    glVertex3d(0.3f, 0.38f, 0.075f);
/////////////////////////////////////////////////////////
    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.24f, 0.37f, 0.105f);
    glTexCoord2f(0.1f, 0.f);
    glVertex3d(0.3f, 0.37f, 0.105f);

    glTexCoord2f(0.f, 0.1f);
    glVertex3d(0.24f, 0.36f, 0.13f);
    glTexCoord2f(0.1f, 0.1f);
    glVertex3d(0.3f, 0.36f, 0.13f);

    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.24f, 0.34f, 0.145f);
    glTexCoord2f(0.1f, 0.f);
    glVertex3d(0.3f, 0.34f, 0.145f);

    glTexCoord2f(0.f, 0.1f);
    glVertex3d(0.24f, 0.32f, 0.155f);
    glTexCoord2f(0.1f, 0.1f);
    glVertex3d(0.3f, 0.32f, 0.155f);

    glTexCoord2f(0.f, 0.f);
    glVertex3d(0.24f, 0.3f, 0.16f);
    glTexCoord2f(0.1f, 0.f);
    glVertex3d(0.3f, 0.3f, 0.16f);

    glEnd();
}

void Body::SetTexture(int index, GLuint texture) {
    textures[index] = texture;
}

float Body::getPosx() const {
    return posx;
}

void Body::setPosx(float posx) {
    Body::posx = posx;
}

float Body::getPosy() const {
    return posy;
}

void Body::setPosy(float posy) {
    Body::posy = posy;
}

float Body::getPosz() const {
    return posz;
}

void Body::setPosz(float posz) {
    Body::posz = posz;
}

float Body::getRotx() const {
    return rotx;
}

void Body::setRotx(float rotx) {
    Body::rotx = rotx;
}

float Body::getRoty() const {
    return roty;
}

void Body::setRoty(float roty) {
    Body::roty = roty;
}

float Body::getRotz() const {
    return rotz;
}

void Body::setRotz(float rotz) {
    Body::rotz = rotz;
}

float Body::getScale() const {
    return scale;
}

void Body::setScale(float scale) {
    Body::scale = scale;
}

const GLuint *Body::getTextures() const {
    return textures;
}
