#include "Legs.h"


Legs::Legs() {
    posx = 0.0f;
    posy = 0.5f;
    posz = 0.0f;

    rotx = 0.0f;
    roty = 0.0f;
    rotz = 0.0f;

    scale = 1.f;

    ConstructDefault();
}

Legs::Legs(float scale, float posx, float posy, float posz, float roty) {
    rotx = 0.0f;
    rotz = 0.0f;
    this->roty = roty;
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;

    this->scale = scale;

    ConstructDefault();
}

void Legs::ConstructDefault() {
// LEG
    thighLength = 0.5f * scale;
    calfLength = 0.5f * scale;
    legGirth = 0.06f * scale;
    legGap = 0.8f * scale;

// FOOT
    footLength = 0.5f * scale;
    footWidth = 0.1f * scale;
    footHeight = 0.2f * scale;
    heelLength = 0.0f * scale;
    toeLength = footLength + footLength * 0.25f;

// ARTICULATION
    kneeWidth = footWidth * 2.3f;
    kneeGirth = 0.05f*scale;
    ankleWidth = footWidth * 2.3f;
    ankleGirth = 0.05f*scale;

    for (int i = 0; i < 6; i++) {
        textures[i] = 0;
    }

}


void Legs::Draw() {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(posx, posy, posz);
    /**Rotation Y**/
    glRotatef(roty, 0.f, 1.f, 0.f);

    GLUquadric *pObj = gluNewQuadric();
    gluQuadricTexture(pObj, GL_TRUE);

    // Thigh
    glPushMatrix();
    glColor3f(0.6f, 0.6f, 0.6f);
    glTranslatef(0, footHeight + calfLength + thighLength, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(pObj, legGirth, legGirth, thighLength, 32, 32);
    glPopMatrix();

    // Knee
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(-kneeWidth / 2, footHeight + calfLength, 0);
    glRotatef(90, 0, 1, 0);
    gluCylinder(pObj, kneeGirth, kneeGirth, kneeWidth, 32, 32);
    gluDisk(pObj, 0, kneeGirth, 32, 32);
    glTranslatef(0, 0, kneeWidth);
    gluDisk(pObj, 0, kneeGirth, 32, 32);
    glPopMatrix();

    // Calf
    glPushMatrix();
    glColor3f(0.6f, 0.6f, 0.6f);
    glTranslatef(0, footHeight + calfLength, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(pObj, legGirth, legGirth, calfLength, 32, 32);
    glPopMatrix();

    // Ankle
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(-ankleWidth / 2, footHeight, 0);
    glRotatef(90, 0, 1, 0);
    gluCylinder(pObj, ankleGirth, ankleGirth, ankleWidth, 32, 32);
    gluDisk(pObj, 0, ankleGirth, 32, 32);
    glTranslatef(0, 0, ankleWidth);
    gluDisk(pObj, 0, ankleGirth, 32, 32);
    glPopMatrix();

    // Foot
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);
    // BASE OF THE FOOT
    glBegin(GL_QUADS);
    // Top face
    glVertex3f(footWidth, footHeight, -heelLength);       // back right
    glVertex3f(-footWidth, footHeight, -heelLength);       // back left
    glVertex3f(-footWidth, footHeight, footLength);       // front left
    glVertex3f(footWidth, footHeight, footLength);       // front right

    // Bottom face
    glVertex3f(footWidth, 0.0f, footLength);          // front right
    glVertex3f(-footWidth, 0.0f, footLength);          // front left
    glVertex3f(-footWidth, 0.0f, -heelLength);          // back left
    glVertex3f(footWidth, 0.0f, -heelLength);          // back right

    // Back face
    glVertex3f(footWidth, 0.0f, -heelLength);          // bottom right
    glVertex3f(-footWidth, 0.0f, -heelLength);          // bottom left
    glVertex3f(-footWidth, footHeight, -heelLength);      // top left
    glVertex3f(footWidth, footHeight, -heelLength);      // top right

    // Left face
    glVertex3f(-footWidth, footHeight, footLength);      // top right
    glVertex3f(-footWidth, footHeight, -heelLength);      // top left
    glVertex3f(-footWidth, 0.0f, -heelLength);          // bottom left
    glVertex3f(-footWidth, 0.0f, footLength);          // bottom right

    // Right face
    glVertex3f(footWidth, footHeight, -heelLength);       // top right
    glVertex3f(footWidth, footHeight, footLength);       // top left
    glVertex3f(footWidth, 0.0f, footLength);           // bottom left
    glVertex3f(footWidth, 0.0f, -heelLength);           // bottom right
    glEnd();

    // TOES
    glBegin(GL_TRIANGLES);
    // Top face
    glVertex3f(footWidth, footHeight, footLength);       // base right
    glVertex3f(-footWidth, footHeight, footLength);       // base left
    glVertex3f(0, 0.0f, toeLength);                 // point

    // Bottom face
    glVertex3f(footWidth, 0.0f, footLength);          // base right
    glVertex3f(-footWidth, 0.0f, footLength);          // base left
    glVertex3f(0, 0.0f, toeLength);                 // point

    // Left face
    glVertex3f(-footWidth, footHeight, footLength);      // base top
    glVertex3f(-footWidth, 0.0f, footLength);          // base bottom
    glVertex3f(0, 0.0f, toeLength);                 // point

    // Right face
    glVertex3f(footWidth, footHeight, footLength);        // base top
    glVertex3f(footWidth, 0.0f, footLength);           // base bottom
    glVertex3f(0, 0.0f, toeLength);                 // point
    glEnd();

    glPopMatrix();
    gluDeleteQuadric(pObj);
    glPopMatrix();
}


float Legs::getPosx() const {
    return posx;
}

void Legs::setPosx(float posx) {
    Legs::posx = posx;
}

float Legs::getPosy() const {
    return posy;
}

void Legs::setPosy(float posy) {
    Legs::posy = posy;
}

float Legs::getPosz() const {
    return posz;
}

void Legs::setPosz(float posz) {
    Legs::posz = posz;
}

float Legs::getRotx() const {
    return rotx;
}

void Legs::setRotx(float rotx) {
    Legs::rotx = rotx;
}

float Legs::getRoty() const {
    return roty;
}

void Legs::setRoty(float roty) {
    Legs::roty = roty;
}

float Legs::getRotz() const {
    return rotz;
}

void Legs::setRotz(float rotz) {
    Legs::rotz = rotz;
}

float Legs::getScale() const {
    return scale;
}

void Legs::setScale(float scale) {
    Legs::scale = scale;
}

const GLuint *Legs::getTextures() const {
    return textures;
}

void Legs::SetTexture(int index, GLuint texture) {
    textures[index] = texture;
}