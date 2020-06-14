#include "Head.h"

Head::Head() {
    posx = 0.0f;
    posy = 0.5f;
    posz = 0.0f;

    roty = 0.0f;

    scale = 1.f;
    defaultConstruct();
}

Head::Head(float scale, float posx, float posy, float posz, float roty) {
    this->roty = roty;
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;

    this->scale = scale;
    defaultConstruct();
}

void Head::defaultConstruct() {
    headAnimation1.currentRotation = 0.f;
    headAnimation1.deltaHeadJaw = 1;
    headAnimation1.deltaRotation = 0;
    headAnimation1.headJawCurrentRotation = 0.f;
    headAnimation1.headJawMaxRotation = 50.f;
    headAnimation1.headJawSpeed = 1.2f;
    headAnimation1.isWalking = 0;
    headAnimation1.maxRotation = 50.f;
    headAnimation1.rotationSpeed = 1.2f;

    antenna1.currentDelay = 0;
    antenna1.maxDelay = 50;
    antenna1.on.R = 1.f;
    antenna1.on.G = 0.1f;
    antenna1.on.B = 0.1f;
    antenna1.off.R = 0.5f;
    antenna1.off.G = 0.1f;
    antenna1.off.B = 0.1f;
    antenna1.currentRGB = &(antenna1.on);

    eyes1.currentDelay = 0;
    eyes1.maxDelay = 100;
    eyes1.on.R = 0.1f;
    eyes1.on.G = 1.f;
    eyes1.on.B = 0.1f;
    eyes1.off.R = 0.1f;
    eyes1.off.G = 0.5f;
    eyes1.off.B = 0.1f;
    eyes1.currentRGB = &(eyes1.on);

    rotx = 0.f;
    rotz = 0.f;

    for (int i = 0; i < 6; i++) {
        textures[i] = 0;
    }
}

void Head::Draw() {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLUquadricObj *params_cylindre = gluNewQuadric();
    GLUquadric *params_sphere = gluNewQuadric();
    GLUquadric *params_oeil = gluNewQuadric();
    GLUquadric *params_marchoire = gluNewQuadric();

    gluQuadricTexture(params_cylindre, GLU_TRUE);
    gluQuadricTexture(params_sphere, GLU_TRUE);
    gluQuadricTexture(params_oeil, GLU_TRUE);
    gluQuadricTexture(params_marchoire, GLU_TRUE);

    glPushMatrix();
    glTranslatef(posx, posy, posz);
    /**Rotation Y**/
    glTranslatef(0.0 * this->scale, 0.0 * this->scale, 7.0 * this->scale);
    glRotatef(roty, 0.f, 1.f, 0.f);
    glRotatef(headAnimation1.currentRotation, 0.f, 1.f, 0.f);


    /** topside head **/
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    drawHalfSphere(20, 20, 4.7 * this->scale);

    /** downside head **/

    glTranslatef(0.5 * this->scale, 0.1 * this->scale, 0.0 * this->scale);
    glRotatef(180, 1.0, 0.0, 0.0);

    glPushMatrix();

    glRotatef(headAnimation1.headJawCurrentRotation, 0.0, 0.0, 1.0);

    glBindTexture(GL_TEXTURE_2D, textures[0]);
    drawHalfSphere(20, 20, 4.6 * this->scale);

    glPopMatrix();


    /** antenna **/
    glBindTexture(GL_TEXTURE_2D, NULL);
    glColor3f(antenna1.currentRGB->R, antenna1.currentRGB->G, antenna1.currentRGB->B);
    glTranslatef(0.0, -7.0 * this->scale, 0.0);
    gluSphere(params_sphere, 0.4 * this->scale, 10, 10);

    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, -3.0 * this->scale);

    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    gluCylinder(params_cylindre, 0.1f * this->scale, 0.1f * this->scale, 3.0f * this->scale, 32, 32);

    /** eyes **/
    glColor3f(eyes1.currentRGB->R, eyes1.currentRGB->G, eyes1.currentRGB->B);
    glTranslatef(3.0 * this->scale, -1.4 * this->scale, -1.0 * this->scale);

    gluSphere(params_sphere, 0.7 * this->scale, 10, 10);

    glTranslatef(0.0, 2.8 * this->scale, 0.0);

    gluSphere(params_sphere, 0.7 * this->scale, 10, 10);

    /********* Machoire ************/

    glTranslatef(-5.0 * this->scale, 3.5 * this->scale, -3.0 * this->scale);
    glRotatef(90.0, 1.0, 0.0, 0.0);

    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    gluCylinder(params_cylindre, 1.1f * this->scale, 1.1f * this->scale, 1.5f * this->scale, 32, 32);
    gluDisk(params_marchoire, 0.0f * this->scale, 1.1f * this->scale, 32, 32);

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    gluSphere(params_sphere, 0.5f * this->scale, 32, 32);

    /*********** other Machoire **********/

    glTranslatef(0.0 * this->scale, 0.0 * this->scale, 8.5 * this->scale);

    glBindTexture(GL_TEXTURE_2D, textures[0]);
    gluCylinder(params_cylindre, 1.1f * this->scale, 1.1f * this->scale, 1.5f * this->scale, 32, 32);

    glTranslatef(0.0 * this->scale, 0.0 * this->scale, 1.1 * this->scale);
    gluDisk(params_marchoire, 0.0f * this->scale, 1.1f * this->scale, 32, 32);

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    gluSphere(params_sphere, 0.5f * this->scale, 32, 32);

    gluDeleteQuadric(params_cylindre);
    gluDeleteQuadric(params_sphere);
    gluDeleteQuadric(params_oeil);
    gluDeleteQuadric(params_marchoire);
    glPopMatrix();
    glPopMatrix();
}

/*
    scalex - scaling of sphere around x-axis
   scaley - scaling of sphere around y-axis
   rayon - radius of sphere
*/
void Head::drawHalfSphere(int scaley, int scalex, GLfloat rayon) {
    int i, j;
    GLfloat data[scalex * scaley][3];

    /*
    construction du tableau
    */
    for (i = 0; i < scalex; i += 1) {
        for (j = 0; j < scaley; j += 1) {
            data[i * scaley + j][0] = rayon * cos(j * 2 * M_PI / scaley) * cos(i * M_PI / (2 * scalex));
            data[i * scaley + j][1] = rayon * sin(i * M_PI / (2 * scalex));
            data[i * scaley + j][2] = rayon * sin(j * 2 * M_PI / scaley) * cos(i * M_PI / (2 * scalex));
        }
    }
    /*
    Construction de la sphère
    */
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    for (i = 0; i < scalex - 1; i += 1) {
        for (j = 0; j < scaley; j += 1) {
            glVertex3fv(data[i * scaley + j]);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3fv(data[i * scaley + (j + 1) % scaley]);
            glVertex3fv(data[(i + 1) * scaley + (j + 1) % scaley]);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3fv(data[(i + 1) * scaley + j]);
        }
    }
    glTexCoord2f(0.0f, 1.0f);
    glEnd();
}

void Head::setDeltaRotation(char delta) {
    headAnimation1.deltaRotation = delta;
}

void Head::setWalkingAnimationActive() {
    headAnimation1.isWalking = 1;
}

void Head::setWalkingAnimationInactive() {
    headAnimation1.isWalking = 0;
}

void Head::updateHeadWalkingAnimation() {
    if (!headAnimation1.isWalking && headAnimation1.headJawCurrentRotation > 0.f) {
        headAnimation1.headJawCurrentRotation -= headAnimation1.headJawSpeed;
    } else if (headAnimation1.isWalking) {
        switch (headAnimation1.deltaHeadJaw) {
            case -1:
                headAnimation1.headJawCurrentRotation -= headAnimation1.headJawSpeed;
                if (headAnimation1.headJawCurrentRotation < 0.f) {
                    headAnimation1.headJawCurrentRotation = 0.f;
                    headAnimation1.deltaHeadJaw = 1;
                }
                break;
            case 1:
                headAnimation1.headJawCurrentRotation += headAnimation1.headJawSpeed;
                if (headAnimation1.headJawCurrentRotation > headAnimation1.headJawMaxRotation) {
                    headAnimation1.headJawCurrentRotation = headAnimation1.headJawMaxRotation;
                    headAnimation1.deltaHeadJaw = -1;
                }
                break;
        }
    }

}

void Head::updateAnimation() {
    updateHeadRotation();
    updateHeadWalkingAnimation();
    updateAntennaColor();
    updateEyesColor();
}

void Head::updateHeadRotation() {
    switch (headAnimation1.deltaRotation) {
        case -1:
            headAnimation1.currentRotation -= headAnimation1.rotationSpeed;
            if (headAnimation1.currentRotation < -headAnimation1.maxRotation)
                headAnimation1.currentRotation = -headAnimation1.maxRotation;
            break;
        case 1:
            headAnimation1.currentRotation += headAnimation1.rotationSpeed;
            if (headAnimation1.currentRotation > headAnimation1.maxRotation)
                headAnimation1.currentRotation = headAnimation1.maxRotation;
            break;
        default:
            if (headAnimation1.currentRotation > 1.f)
                headAnimation1.currentRotation -= headAnimation1.rotationSpeed;
            else if (headAnimation1.currentRotation < -1.f)
                headAnimation1.currentRotation += headAnimation1.rotationSpeed;
            break;
    }
}

void Head::updateAntennaColor() {
    antenna1.currentDelay++;
    if (antenna1.currentDelay > antenna1.maxDelay) {
        antenna1.currentDelay = 0;
        if (antenna1.currentRGB == &(antenna1.on)) {
            antenna1.currentRGB = &(antenna1.off);
        } else {
            antenna1.currentRGB = &(antenna1.on);
        }
    }
}

void Head::updateEyesColor() {
    eyes1.currentDelay++;
    if (eyes1.currentDelay > eyes1.maxDelay) {
        eyes1.currentDelay = 0;
        if (eyes1.currentRGB == &(eyes1.on)) {
            eyes1.currentRGB = &(eyes1.off);
        } else {
            eyes1.currentRGB = &(eyes1.on);
        }
    }
}

float Head::getPosx() const {
    return posx;
}

void Head::setPosx(float posx) {
    Head::posx = posx;
}

float Head::getPosy() const {
    return posy;
}

void Head::setPosy(float posy) {
    Head::posy = posy;
}

float Head::getPosz() const {
    return posz;
}

void Head::setPosz(float posz) {
    Head::posz = posz;
}

float Head::getRotx() const {
    return rotx;
}

void Head::setRotx(float rotx) {
    Head::rotx = rotx;
}

float Head::getRoty() const {
    return roty;
}

void Head::setRoty(float roty) {
    Head::roty = roty;
}

float Head::getRotz() const {
    return rotz;
}

void Head::setRotz(float rotz) {
    Head::rotz = rotz;
}

const GLuint *Head::getTextures() const {
    return textures;
}

void Head::SetTexture(int index, GLuint texture) {
    textures[index] = texture;
}

