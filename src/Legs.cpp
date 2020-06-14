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
    kneeGirth = 0.05f * scale;
    ankleWidth = footWidth * 2.3f;
    ankleGirth = 0.05f * scale;


    walkingLegs.isWalking = 0;
    walkingLegs.walkingMinRotation = -20.f;
    walkingLegs.walkingMaxRotation = 30.f;
    walkingLegs.walkingShoulderWay = 1;
    walkingLegs.animationSpeed = 1.f;
    walkingLegs.walkingCurrentRotation = 0.f;

    for (int i = 0; i < 6; i++) {
        textures[i] = 0;
    }

}

void Legs::Draw() {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    GLUquadric *pObj = gluNewQuadric();
    gluQuadricTexture(pObj, GL_TRUE);

    glColor3f(1.0f, 1.0f, 1.0f);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTranslatef(posx, posy, posz);
    /**Rotation Y**/
    glRotatef(roty, 0.f, 1.f, 0.f);

    glTranslatef(0.f, (thighLength + calfLength + footHeight), 0.f);
    glRotatef(walkingLegs.walkingCurrentRotation, 1.f, 0.f, 0.f);
    glTranslatef(0.f, -(thighLength + calfLength + footHeight), 0.f);


    // Thigh
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTranslatef(0, footHeight + calfLength + thighLength, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(pObj, legGirth, legGirth, thighLength, 32, 32);
    glPopMatrix();

    // Knee
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTranslatef(-kneeWidth / 2, footHeight + calfLength, 0);
    glRotatef(90, 0, 1, 0);
    gluCylinder(pObj, kneeGirth, kneeGirth, kneeWidth, 32, 32);
    gluDisk(pObj, 0, kneeGirth, 32, 32);
    glTranslatef(0, 0, kneeWidth);
    gluDisk(pObj, 0, kneeGirth, 32, 32);
    glPopMatrix();

    // Calf
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTranslatef(0, footHeight + calfLength, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(pObj, legGirth, legGirth, calfLength, 32, 32);
    glPopMatrix();

    // Ankle
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTranslatef(-ankleWidth / 2, footHeight, 0);
    glRotatef(90, 0, 1, 0);
    gluCylinder(pObj, ankleGirth, ankleGirth, ankleWidth, 32, 32);
    gluDisk(pObj, 0, ankleGirth, 32, 32);
    glTranslatef(0, 0, ankleWidth);
    gluDisk(pObj, 0, ankleGirth, 32, 32);
    glPopMatrix();

    // Foot
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    // BASE OF THE FOOT
    glBegin(GL_QUADS);
    // Top face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(footWidth, footHeight, -heelLength);       // back right
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-footWidth, footHeight, -heelLength);       // back left
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-footWidth, footHeight, footLength);       // front left
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(footWidth, footHeight, footLength);       // front right

    // Bottom face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(footWidth, 0.0f, footLength);          // front right
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-footWidth, 0.0f, footLength);          // front left
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-footWidth, 0.0f, -heelLength);          // back left
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(footWidth, 0.0f, -heelLength);          // back right

    // Back face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(footWidth, 0.0f, -heelLength);          // bottom right
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-footWidth, 0.0f, -heelLength);          // bottom left
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-footWidth, footHeight, -heelLength);      // top left
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(footWidth, footHeight, -heelLength);      // top right

    // Left face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-footWidth, footHeight, footLength);      // top right
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-footWidth, footHeight, -heelLength);      // top left
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-footWidth, 0.0f, -heelLength);          // bottom left
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-footWidth, 0.0f, footLength);          // bottom right

    // Right face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(footWidth, footHeight, -heelLength);       // top right
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(footWidth, footHeight, footLength);       // top left
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(footWidth, 0.0f, footLength);           // bottom left
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(footWidth, 0.0f, -heelLength);           // bottom right
    glEnd();

    // TOES
    glBegin(GL_TRIANGLES);
    // Top face
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(footWidth, footHeight, footLength);       // base right
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-footWidth, footHeight, footLength);       // base left
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 0.0f, toeLength);                 // point

    // Bottom face
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(footWidth, 0.0f, footLength);          // base right
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-footWidth, 0.0f, footLength);          // base left
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 0.0f, toeLength);                 // point

    // Left face
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-footWidth, footHeight, footLength);      // base top
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-footWidth, 0.0f, footLength);          // base bottom
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 0.0f, toeLength);                 // point

    // Right face
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(footWidth, footHeight, footLength);        // base top
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(footWidth, 0.0f, footLength);           // base bottom
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 0.0f, toeLength);                 // point
    glEnd();

    glPopMatrix();
    gluDeleteQuadric(pObj);
    glPopMatrix();
}


void Legs::setWalkingAnimationInactive() {
    walkingLegs.isWalking = 0;
}

void Legs::setWalkingAnimationActive() {
    walkingLegs.isWalking = 1;
}

void Legs::UpdateAnimation() {
    if (walkingLegs.isWalking) {
        UpdateWalkingAnimation();
    } else {
        StopWalking();
    }
}

void Legs::UpdateWalkingAnimation() {
    switch (walkingLegs.walkingShoulderWay) {
        case 1:
            walkingLegs.walkingCurrentRotation += walkingLegs.animationSpeed;
            if (walkingLegs.walkingCurrentRotation > walkingLegs.walkingMaxRotation) {
                walkingLegs.walkingCurrentRotation = walkingLegs.walkingMaxRotation;
                InverseWalkingAnimationWay();
            }
            break;
        case -1:
            walkingLegs.walkingCurrentRotation -= walkingLegs.animationSpeed;
            if (walkingLegs.walkingCurrentRotation < -walkingLegs.walkingMaxRotation) {
                walkingLegs.walkingCurrentRotation = -walkingLegs.walkingMaxRotation;
                InverseWalkingAnimationWay();
            }
            break;
        default:
            break;
    }
}

void Legs::StopWalking() {
    if (walkingLegs.walkingCurrentRotation > walkingLegs.animationSpeed + 0.1f)
        walkingLegs.walkingCurrentRotation -= walkingLegs.animationSpeed;
    else if (walkingLegs.walkingCurrentRotation < walkingLegs.animationSpeed - 0.1f)
        walkingLegs.walkingCurrentRotation += walkingLegs.animationSpeed;
}

void Legs::InverseWalkingAnimationWay() {
    walkingLegs.walkingShoulderWay = -walkingLegs.walkingShoulderWay;
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