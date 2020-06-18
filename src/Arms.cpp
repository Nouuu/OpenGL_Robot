#include "Arms.h"

// Initialisations des positions et rotations + constructeur par défaut
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

// Initialisations des positions et rotation sur Y en paramètres + constructeur par défaut
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

// Constructeur par défaut
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
    // Si Clank marche, on met à jour les animations
    if (walking.isWalking) {
        UpdateWalkingAnimation();
    }
}

void Arms::setWalkingAnimationgActive() {
    // Active la marche
    walking.isWalking = 1;
}

void Arms::setWalkingAnimationInactive() {
    // Désactive la marche
    walking.isWalking = 0;
}

void Arms::UpdateWalkingAnimation() {
    if (walking.walkingShoulderWay == 1) {                              // Si le bras va vers l'avant
        shoulderRotation += walking.animationSpeed;                     // On incrémente l'angle de rotation
        if (shoulderRotation > walking.walkingShoulderMaxRotation) {    // Si on dépasse l'angle max
            shoulderRotation = walking.walkingShoulderMaxRotation;      // On cappe à l'angle max
            walking.walkingShoulderWay = -1;                            // On repart en arrière
        }
        forearmRotation += walking.animationSpeed;                      // Même chose pour l'avant bras
        if (forearmRotation > walking.walkingForearmMaxRotation) {
            forearmRotation = walking.walkingForearmMaxRotation;
            walking.walkingForearmWay = -1;
        }
    } else {                                                            // Si le bras va vers l'arrière
        shoulderRotation -= walking.animationSpeed;                     // On décrémente l'angle de rotation
        if (shoulderRotation < walking.walkingShoulderMinRotation) {    // Si on est plus bas que l'angle min
            shoulderRotation = walking.walkingShoulderMinRotation;      // On cappe à l'angle min
            walking.walkingShoulderWay = 1;                             // On repart en avant
        }

        forearmRotation -= walking.animationSpeed;                      // Même chose pour l'avant bras
        if (forearmRotation < walking.walkingForearmMinRotation) {
            forearmRotation = walking.walkingForearmMinRotation;
            walking.walkingForearmWay = 1;
        }
    }
}

void Arms::InverseWalkingAnimationWay() {
    // Inversion de la direction des mouvements du bras
    walking.walkingForearmWay = -walking.walkingForearmWay;
    walking.walkingShoulderWay = -walking.walkingShoulderWay;
}

void Arms::Draw() {
    // Active le placage de textures a deux dimensions
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

        // Crée et retourne un pointeur vers un nouvel objet quadrics
        GLUquadric *pObj = gluNewQuadric();
        // On définit qu'on veut des textures que le quad
        gluQuadricTexture(pObj, GLU_TRUE);

        // Définit et conserve une couleur courante
        glColor3f(1.0f, 1.0f, 1.0f);

        // Set les paramètres de la texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // dimension horizontale de la texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // dimension verticale de la texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Méthode d'agrandissement
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Méthode de réduction

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

            // Détruit l'objet
            gluDeleteQuadric(pObj);
        glPopMatrix();

    glPopMatrix();
}

void Arms::DrawShoulder(GLUquadric *pObj) {
    // Spécifie la texture
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    gluCylinder(pObj, 0.25f * scale, 0.25f * scale, 0.15f * scale, 32, 32);
    gluDisk(pObj, 0.15f * scale, 0.25f * scale, 32, 32);

    glTranslatef(0.f, 0.f, 0.15 * scale);

    gluDisk(pObj, 0.15f * scale, 0.25f * scale, 32, 32);

    glTranslatef(0.f, 0.f, -0.075 * scale);

    // Spécifie la texture
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    gluSphere(pObj, 0.20f * scale, 32, 32);

}

void Arms::DrawUpperarm(GLUquadric *pObj) {
    // Spécifie la texture
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    // ROTATION BRAS SUPERIEUR JOINTURE EPAULE
    glRotatef(shoulderRotation, 0.f, 0.f, 1.f);
    glTranslatef(0.f, -0.22f * scale, 0.f);
    glRotatef(90, 1.f, 0.f, 0.f);
    gluCylinder(pObj, 0.07f * scale, 0.07f * scale, 0.3f * scale, 32, 32);
}

void Arms::DrawElbow(GLUquadric *pObj) {
    glTranslatef(0.f, 0.075f * scale, 0.3f * scale);
    glRotatef(90, 1.f, 0.f, 0.f);
    // Spécifie la texture
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    gluCylinder(pObj, 0.1f * scale, 0.1f * scale, 0.15f * scale, 32, 32);
    glTranslatef(0.f, 0.f, 0.05f * scale);
    gluSphere(pObj, 0.1f * scale, 32, 32);
    glTranslatef(0.f, 0.f, 0.05f * scale);
    gluSphere(pObj, 0.1f * scale, 32, 32);
}

void Arms::DrawForearm(GLUquadric *pObj) {
    // Spécifie la texture
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glTranslatef(0.f, 0.f, -0.1f * scale);
    glRotatef(-90, 1.f, 0.f, 0.f);
    // ROTATION BRAS INFERIEUR JOINTURE COUDE
    glRotatef(forearmRotation, 0.f, 1.f, 0.f);
    glTranslatef(0.f, -0.075f * scale, 0.05f * scale);
    gluCylinder(pObj, 0.07f * scale, 0.07f * scale, 0.3f * scale, 32, 32);
}

void Arms::DrawHand(GLUquadric *pObj) {
    // MAIN
    glRotatef(180, 0.f, 0.f, 1.f); // ROTATION POIGNET
    glTranslatef(0.f, 0.07f * scale, 0.26f * scale);

    //BOULON
    // Spécifie la texture
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTranslatef(0.f, -0.07f * scale, 0.12f * scale);
    gluSphere(pObj, 0.1f * scale, 32, 32);
    glTranslatef(0.f, 0.07f * scale, -0.12f * scale);

    // Spécifie la texture
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
    // Spécifie la texture
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
