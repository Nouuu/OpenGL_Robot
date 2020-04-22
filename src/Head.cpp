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
    headAnimation1.deltaRotation = 0;
    headAnimation1.rotationSpeed = 1.2f;
    headAnimation1.maxRotation = 50.f;
    headAnimation1.currentRotation = 0.f;

    rotx = 0.f;
    rotz = 0.f;

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

    GLUquadricObj *params_cylindre = gluNewQuadric();
    GLUquadric *params_sphere = gluNewQuadric();
    GLUquadric *params_oeil = gluNewQuadric();
    GLUquadric *params_marchoire = gluNewQuadric();

    glPushMatrix();
    glTranslatef(posx, posy, posz);
    /**Rotation Y**/
    glTranslatef(0.0 * this->scale, 0.0 * this->scale, 7.0 * this->scale);
    glRotatef(roty, 0.f, 1.f, 0.f);
    glRotatef(headAnimation1.currentRotation, 0.f, 1.f, 0.f);


    /** topside head **/
    glColor3f(0.6, 0.6, 0.6);

    drawHalfSphere(20, 20, 4.7 * this->scale);

    /** downside head **/

    glColor3f(0.3, 0.3, 0.3);
    glTranslatef(0.5 * this->scale, 0.0 * this->scale, 0.0 * this->scale);
    glRotatef(180, 1.0, 0.0, 0.0);

    drawHalfSphere(20, 20, 5 * this->scale);

    /** antenna **/

    glColor3f(1.0, 0.1, 0.1);
    glTranslatef(0.0, -7.0 * this->scale, 0.0);
    gluSphere(params_sphere, 0.4 * this->scale, 10, 10);

    glColor3f(0.6, 0.6, 0.6);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, -3.0 * this->scale);

    gluCylinder(params_cylindre, 0.1f * this->scale, 0.1f * this->scale, 3.0f * this->scale, 32, 32);

    /** eyes **/
    glColor3f(0.2, 1.0, 0.2);
    glTranslatef(3.0 * this->scale, -1.4 * this->scale, -1.0 * this->scale);

    gluSphere(params_sphere, 0.7 * this->scale, 10, 10);

    glTranslatef(0.0, 2.8 * this->scale, 0.0);

    gluSphere(params_sphere, 0.7 * this->scale, 10, 10);

    /********* Machoire ************/

    glTranslatef(-5.0 * this->scale, 3.5 * this->scale, -3.0 * this->scale);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glColor3f(0.4, 0.4, 0.4);

    gluCylinder(params_cylindre, 1.1f * this->scale, 1.1f * this->scale, 1.5f * this->scale, 32, 32);
    gluDisk(params_marchoire, 0.0f * this->scale, 1.1f * this->scale, 32, 32);

    glColor3f(0.1, 0.1, 0.1);
    gluSphere(params_sphere, 0.5f * this->scale, 32, 32);

    /*********** other Machoire **********/

    glTranslatef(0.0 * this->scale, 0.0 * this->scale, 8.5 * this->scale);
    glColor3f(0.4, 0.4, 0.4);

    gluCylinder(params_cylindre, 1.1f * this->scale, 1.1f * this->scale, 1.5f * this->scale, 32, 32);
    glTranslatef(0.0 * this->scale, 0.0 * this->scale, 1.1 * this->scale);
    gluDisk(params_marchoire, 0.0f * this->scale, 1.1f * this->scale, 32, 32);

    glColor3f(0.1, 0.1, 0.1);
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
    for (i = 0; i < scalex - 1; i += 1) {
        for (j = 0; j < scaley; j += 1) {
            glVertex3fv(data[i * scaley + j]);
            glVertex3fv(data[i * scaley + (j + 1) % scaley]);
            glVertex3fv(data[(i + 1) * scaley + (j + 1) % scaley]);
            glVertex3fv(data[(i + 1) * scaley + j]);
        }
    }
    glEnd();
}

void Head::setDeltaRotation(char delta) {
    headAnimation1.deltaRotation = delta;
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
            if (headAnimation1.currentRotation > 0.1f)
                headAnimation1.currentRotation -= headAnimation1.rotationSpeed;
            else if (headAnimation1.currentRotation < -0.1f)
                headAnimation1.currentRotation += headAnimation1.rotationSpeed;
            break;
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
