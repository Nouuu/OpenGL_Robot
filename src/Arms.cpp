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

    ConstructDefault();
}

Arms::Arms(float scale, float posx, float posy, float posz, float roty) {
    rotx = 0.f;
    rotz = 0.f;
    this->roty = roty;
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;

    this->scale = scale;

    ConstructDefault();
}

void Arms::ConstructDefault() {
    walking.isWalking = 0;
    walking.walkingShoulderMinRotation = -20.f;
    walking.walkingShoulderMaxRotation = 30.f;
    walking.walkingShoulderWay = 1;
    walking.walkingForearmWay = 1;
    walking.walkingForearmMinRotation = -20.f;
    walking.walkingForearmMaxRotation = 30.f;
    walking.animationSpeed = 1.f;

    shoulderRotation = -10.f;
    forearmRotation = 15.f;

    for (int i = 0; i < 6; i++) {
        textures[i] = 0;
    }
}

void Arms::UpdateAnimations() {
    if (walking.isWalking) {
        UpdateWalkingAnimation();
    }
}

void Arms::setWalkingAnimationgActive() {
    walking.isWalking = 1;
}

void Arms::setWalkingAnimationInactive() {
    walking.isWalking = 0;
}

void Arms::UpdateWalkingAnimation() {
    if (walking.walkingShoulderWay == 1) {
        shoulderRotation += walking.animationSpeed;
        if (shoulderRotation > walking.walkingShoulderMaxRotation) {
            shoulderRotation = walking.walkingShoulderMaxRotation;
            walking.walkingShoulderWay = -1;
        }
        forearmRotation += walking.animationSpeed;
        if (forearmRotation > walking.walkingForearmMaxRotation) {
            forearmRotation = walking.walkingForearmMaxRotation;
            walking.walkingForearmWay = -1;
        }
    } else {
        shoulderRotation -= walking.animationSpeed;
        if (shoulderRotation < walking.walkingShoulderMinRotation) {
            shoulderRotation = walking.walkingShoulderMinRotation;
            walking.walkingShoulderWay = 1;
        }

        forearmRotation -= walking.animationSpeed;
        if (forearmRotation < walking.walkingForearmMinRotation) {
            forearmRotation = walking.walkingForearmMinRotation;
            walking.walkingForearmWay = 1;
        }
    }
}

void Arms::InverseWalkingAnimationWay() {
    walking.walkingForearmWay = -walking.walkingForearmWay;
    walking.walkingShoulderWay = -walking.walkingShoulderWay;
}

void Arms::Draw() {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    GLUquadric *pObj = gluNewQuadric();
    gluQuadricTexture(pObj, GLU_TRUE);

    glColor3f(1.0f, 1.0f, 1.0f);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


    /** Epaule **/
    glPushMatrix();
    glTranslatef(posx, posy, posz);
    /**Rotation Y**/
    glRotatef(roty, 0.f, 1.f, 0.f);

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

//    glRotatef(-roty, 0.f, 1.f, 0.f);
    gluDeleteQuadric(pObj);
    glPopMatrix();
    glPopMatrix();

}

void Arms::DrawShoulder(GLUquadric *pObj) {
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    gluCylinder(pObj, 0.25f * scale, 0.25f * scale, 0.15f * scale, 32, 32);
    gluDisk(pObj, 0.15f * scale, 0.25f * scale, 32, 32);

    glTranslatef(0.f, 0.f, 0.15 * scale);

    gluDisk(pObj, 0.15f * scale, 0.25f * scale, 32, 32);

    glTranslatef(0.f, 0.f, -0.075 * scale);

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    gluSphere(pObj, 0.20f * scale, 32, 32);

}

void Arms::DrawUpperarm(GLUquadric *pObj) {
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glRotatef(shoulderRotation, 0.f, 0.f, 1.f); // ROTATION BRAS SUPERIEUR JOINTURE EPAULE
    glTranslatef(0.f, -0.22f * scale, 0.f);
    glRotatef(90, 1.f, 0.f, 0.f);
    gluCylinder(pObj, 0.07f * scale, 0.07f * scale, 0.3f * scale, 32, 32);
}

void Arms::DrawElbow(GLUquadric *pObj) {
    glTranslatef(0.f, 0.075f * scale, 0.3f * scale);
    glRotatef(90, 1.f, 0.f, 0.f);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    gluCylinder(pObj, 0.1f * scale, 0.1f * scale, 0.15f * scale, 32, 32);
    glTranslatef(0.f, 0.f, 0.05f * scale);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    gluSphere(pObj, 0.1f * scale, 32, 32);
    glTranslatef(0.f, 0.f, 0.05f * scale);
    gluSphere(pObj, 0.1f * scale, 32, 32);
}

void Arms::DrawForearm(GLUquadric *pObj) {
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glTranslatef(0.f, 0.f, -0.1f * scale);
    glRotatef(-90, 1.f, 0.f, 0.f);
    glRotatef(forearmRotation, 0.f, 1.f, 0.f); // ROTATION BRAS INFERIEUR JOINTURE EPAULE
    glTranslatef(0.f, -0.075f * scale, 0.05f * scale);
    gluCylinder(pObj, 0.07f * scale, 0.07f * scale, 0.3f * scale, 32, 32);
}

void Arms::DrawHand(GLUquadric *pObj) {
    // MAIN
    glRotatef(180, 0.f, 0.f, 1.f); // ROTATION POIGNET
    glTranslatef(0.f, 0.07f * scale, 0.26f * scale);

    //BOULON
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTranslatef(0.f, -0.07f * scale, 0.12f * scale);
    gluSphere(pObj, 0.1f * scale, 32, 32);
    glTranslatef(0.f, 0.07f * scale, -0.12f * scale);

    glBindTexture(GL_TEXTURE_2D, textures[0]);

    //AVANT
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.f, 0.f, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.15f * scale, 0.f, 0.05f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.15f * scale, 0.f, 0.4f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.f, 0.f, 0.4f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.15f * scale, 0.f, 0.05f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.20f * scale, 0.f, 0.15f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.2f * scale, 0.f, 0.4f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.15f * scale, 0.f, 0.4f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.f, 0.f, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.15f * scale, 0.f, 0.05f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.15f * scale, 0.f, 0.4f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.f, 0.f, 0.4f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.15f * scale, 0.f, 0.05f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.20f * scale, 0.f, 0.15f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.2f * scale, 0.f, 0.4f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.15f * scale, 0.f, 0.4f * scale);

    // ARRIERE
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.f, -0.14f * scale, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.15f * scale, -0.14f * scale, 0.05f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.15f * scale, -0.14f * scale, 0.4f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.f, -0.14f * scale, 0.4f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.15f * scale, -0.14f * scale, 0.05f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.2f * scale, -0.14f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.2f * scale, -0.14f * scale, 0.4f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.15f * scale, -0.14f * scale, 0.4f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.f, -0.14f * scale, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.15f * scale, -0.14f * scale, 0.05f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.15f * scale, -0.14f * scale, 0.4f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.f, -0.14f * scale, 0.4f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.15f * scale, -0.14f * scale, 0.05f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.2f * scale, -0.14f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.2f * scale, -0.14f * scale, 0.4f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.15f * scale, -0.14f * scale, 0.4f * scale);

    //CONTOURS
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.f, 0.f, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.f, -0.14f * scale, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.15f * scale, -0.14f * scale, 0.05f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.15f * scale, 0.f, 0.05f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.15f * scale, 0.f, 0.05f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.15f * scale, -0.14f * scale, 0.05f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.2f * scale, -0.14f * scale, 0.15f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.2f * scale, 0.f, 0.15f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.2f * scale, 0.f, 0.15f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.2f * scale, -0.14f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.2f * scale, -0.14f * scale, 0.4f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.2f * scale, 0.f, 0.4f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.f, 0.f, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.f, -0.14f * scale, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.15f * scale, -0.14f * scale, 0.05f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.15f * scale, 0.f, 0.05f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.15f * scale, 0.f, 0.05f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.15f * scale, -0.14f * scale, 0.05f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.2f * scale, -0.14f * scale, 0.15f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.2f * scale, 0.f, 0.15f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.2f * scale, 0.f, 0.15f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.2f * scale, -0.14f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.2f * scale, -0.14f * scale, 0.4f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.2f * scale, 0.f, 0.4f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.2f * scale, 0.f, 0.4f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.2f * scale, -0.14f * scale, 0.4f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.2f * scale, -0.14f * scale, 0.4f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.2f * scale, 0.f, 0.4f * scale);
    glEnd();

    glTranslatef(0.f, 0.f, 0.4f * scale);

    // DOIGTS
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_QUADS);
    //1
    //AVANT
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.025f * scale, -0.02f * scale, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.175f * scale, -0.02f * scale, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.175f * scale, -0.02f * scale, 0.15f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.025f * scale, -0.02f * scale, 0.15f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.025f * scale, -0.02f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.175f * scale, -0.02f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.13f * scale, -0.02f * scale, 0.25f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.07f * scale, -0.02f * scale, 0.25f * scale);

    //ARRIERE
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.025f * scale, -0.12f * scale, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.175f * scale, -0.12f * scale, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.175f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.025f * scale, -0.12f * scale, 0.15f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.025f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.175f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.13f * scale, -0.12f * scale, 0.25f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.07f * scale, -0.12f * scale, 0.25f * scale);

    //CONTOURS
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.025f * scale, -0.02f * scale, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.025f * scale, -0.12f * scale, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.025f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.025f * scale, -0.02f * scale, 0.15f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.175f * scale, -0.02f * scale, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.175f * scale, -0.12f * scale, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.175f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.175f * scale, -0.02f * scale, 0.15f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.025f * scale, -0.02f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.025f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.07f * scale, -0.12f * scale, 0.25f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.07f * scale, -0.02f * scale, 0.25f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.175f * scale, -0.02f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.175f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.13f * scale, -0.12f * scale, 0.25f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.13f * scale, -0.02f * scale, 0.25f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.13f * scale, -0.12f * scale, 0.25f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(0.13f * scale, -0.02f * scale, 0.25f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(0.07f * scale, -0.02f * scale, 0.25f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(0.07f * scale, -0.12f * scale, 0.25f * scale);

    //2
    //AVANT
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.175f * scale, -0.02f * scale, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.025f * scale, -0.02f * scale, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.025f * scale, -0.02f * scale, 0.15f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.175f * scale, -0.02f * scale, 0.15f * scale);

    glVertex3d(-0.175f * scale, -0.02f * scale, 0.15f * scale);
    glVertex3d(-0.025f * scale, -0.02f * scale, 0.15f * scale);
    glVertex3d(-0.07f * scale, -0.02f * scale, 0.25f * scale);
    glVertex3d(-0.13f * scale, -0.02f * scale, 0.25f * scale);

    //ARRIERE
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.025f * scale, -0.12f * scale, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.175f * scale, -0.12f * scale, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.175f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.025f * scale, -0.12f * scale, 0.15f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.025f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.175f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.13f * scale, -0.12f * scale, 0.25f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.07f * scale, -0.12f * scale, 0.25f * scale);

    //CONTOURS
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.025f * scale, -0.02f * scale, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.025f * scale, -0.12f * scale, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.025f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.025f * scale, -0.02f * scale, 0.15f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.175f * scale, -0.02f * scale, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.175f * scale, -0.12f * scale, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.175f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.175f * scale, -0.02f * scale, 0.15f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.025f * scale, -0.02f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.025f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.07f * scale, -0.12f * scale, 0.25f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.07f * scale, -0.02f * scale, 0.25f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.175f * scale, -0.02f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.175f * scale, -0.12f * scale, 0.15f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.13f * scale, -0.12f * scale, 0.25f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.13f * scale, -0.02f * scale, 0.25f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.13f * scale, -0.12f * scale, 0.25f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.13f * scale, -0.02f * scale, 0.25f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.07f * scale, -0.02f * scale, 0.25f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.07f * scale, -0.12f * scale, 0.25f * scale);

    //3
    //AVANT
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.2f * scale, -0.02f * scale, -0.25f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.2f * scale, -0.02f * scale, -0.05f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.32f * scale, -0.02f * scale, 0.1f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.37f * scale, -0.02f * scale, -0.05f * scale);

    //ARRIERE
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.2f * scale, -0.12f * scale, -0.25f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.2f * scale, -0.12f * scale, -0.05f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.32f * scale, -0.12f * scale, 0.1f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.37f * scale, -0.12f * scale, -0.05f * scale);

    //CONTOURS
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.37f * scale, -0.02f * scale, -0.05f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.2f * scale, -0.02f * scale, -0.25f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.2f * scale, -0.12f * scale, -0.25f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.37f * scale, -0.12f * scale, -0.05f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.2f * scale, -0.02f * scale, -0.05f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.32f * scale, -0.02f * scale, 0.1f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.32f * scale, -0.12f * scale, 0.1f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.2f * scale, -0.12f * scale, -0.05f * scale);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.37f * scale, -0.02f * scale, -0.05f * scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(-0.32f * scale, -0.02f * scale, 0.1f * scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-0.32f * scale, -0.12f * scale, 0.1f * scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.37f * scale, -0.12f * scale, -0.05f * scale);

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
