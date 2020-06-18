#include "Body.h"

// Initialisations des positions et rotations + constructeur par défaut
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

// Initialisations des positions et rotation sur Y en paramètres + constructeur par défaut
Body::Body(float scale, float posx, float posy, float posz, float roty) {
    rotx = 0.0f;
    rotz = 0.0f;
    this->roty = roty;
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
    // Active le placage de textures a deux dimensions
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        /** Corps **/
        // Crée et retourne un pointeur vers un nouvel objet quadrics
        GLUquadric *pObj = gluNewQuadric();
        gluQuadricTexture(pObj, GLU_TRUE);
        glPushMatrix();
            glTranslatef(posx, posy, posz);
            /**Rotation Y**/
            glRotatef(roty, 0.f, 1.f, 0.f);

            DrawInterior(pObj);

            DrawExterior(pObj);

            gluDeleteQuadric(pObj);
        glPopMatrix();
    glPopMatrix();
}

void Body::DrawInterior(GLUquadric *pObj) {
    // Définit et conserve une couleur courante
    glColor3f(1.0f, 1.0f, 1.0f);
    // Spécifie la texture
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    // Set les paramètres de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // dimension horizontale de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // dimension verticale de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Méthode d'agrandissement
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Méthode de réduction

    glBegin(GL_QUADS);
        //Face Avant
        glTexCoord2f(0.0f, 0.0f);
        glVertex3d(0.f, 0.f, 0.f);
        glTexCoord2f(1.f, 0.0f);
        glVertex3d(0.3f * scale, 0.f, 0.f);
        glTexCoord2f(1.f, 1.f);
        glVertex3d(0.3f * scale, 0.3f * scale, 0.f);
        glTexCoord2f(0.0f, 1.f);
        glVertex3d(0.f, 0.3f * scale, 0.f);

        //Face Arrière
        glTexCoord2f(0.0f, 0.0f);
        glVertex3d(0.f, 0.f, 0.15f * scale);
        glTexCoord2f(1.f, 0.0f);
        glVertex3d(0.3f * scale, 0.f, 0.15f * scale);
        glTexCoord2f(1.f, 1.f);
        glVertex3d(0.3f * scale, 0.3f, 0.15f * scale);
        glTexCoord2f(0.0f, 1.f);
        glVertex3d(0.f, 0.3f * scale, 0.15f * scale);

        //Face Dessous
        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.f, 0.f, 0.f);
        glTexCoord2f(1.f, 0.0f);
        glVertex3d(0.3f * scale, 0.f, 0.f);
        glTexCoord2f(1.f, 0.5f);
        glVertex3d(0.3f * scale, 0.f, 0.15f * scale);
        glTexCoord2f(0.0f, 0.5f);
        glVertex3d(0.f * scale, 0.f, 0.15f * scale);

        //Face côtés
        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.f, 0.f, 0.f);
        glTexCoord2f(0.5f, 0.0f);
        glVertex3d(0.f, 0.3f * scale, 0.f);
        glTexCoord2f(0.5f, 1.f);
        glVertex3d(0.f, 0.3f * scale, 0.15f * scale);
        glTexCoord2f(0.0f, 1.f);
        glVertex3d(0.f, 0.f, 0.15f * scale);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3d(0.3f * scale, 0.f, 0.f);
        glTexCoord2f(0.5f, 0.0f);
        glVertex3d(0.3f * scale, 0.3f * scale, 0.f);
        glTexCoord2f(0.5f, 1.f);
        glVertex3d(0.3f * scale, 0.3f * scale, 0.15f * scale);
        glTexCoord2f(0.0f, 1.f);
        glVertex3d(0.3f * scale, 0.f, 0.15f * scale);
    glEnd();

    glTranslatef(0.f, 0.3f * scale, 0.075f * scale);
    glRotatef(90, 0.f, 1.f, 0.f);
    gluCylinder(pObj, 0.075f * scale, 0.075f * scale, 0.3f * scale, 32, 32);
    // Définit et conserve une couleur courante
    glColor3f(0.5f, 0.5f, 0.3f);
    gluDisk(pObj, 0.f, 0.075f * scale, 32, 32);
    glTranslatef(0.f, 0.f, 0.3f * scale);
    gluDisk(pObj, 0.f, 0.075f * scale, 32, 32);

    glRotatef(-90, 0.f, 1.f, 0.f);
    glTranslatef(-0.3f * scale, -0.3f * scale, -0.075f * scale);

}

void Body::DrawExterior(GLUquadric *pObj) {

    // Définit et conserve une couleur courante
    glColor3f(1.0f, 1.0f, 1.0f);

    // Spécifie la texture
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    // Set les paramètres de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // dimension horizontale de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // dimension verticale de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Méthode d'agrandissement
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Méthode de réduction


    glBegin(GL_QUADS);

        //AVANT
        glTexCoord2f(0.f, 0.f);
        glVertex3d(-0.01f * scale, 0.f, -0.01f * scale);
        glTexCoord2f(0.5f, 0.f);
        glVertex3d(0.31f * scale, 0.f, -0.01f * scale);
        glTexCoord2f(0.5f, 0.5f);
        glVertex3d(0.31f * scale, 0.05f * scale, -0.01f * scale);
        glTexCoord2f(0.f, 0.5f);
        glVertex3d(-0.01f * scale, 0.05f * scale, -0.01f * scale);

        glTexCoord2f(0.f, 0.f);
        glVertex3d(-0.01f * scale, 0.05f * scale, -0.01f * scale);
        glTexCoord2f(1.f, 0.f);
        glVertex3d(0.31f * scale, 0.05f * scale, -0.01f * scale);
        glTexCoord2f(1.f, 1.f);
        glVertex3d(0.3f * scale, 0.3f * scale, -0.01f * scale);
        glTexCoord2f(0.f, 1.f);
        glVertex3d(0.f, 0.3f * scale, -0.01f * scale);

        //ARRIERE
        glTexCoord2f(0.f, 0.f);
        glVertex3d(-0.01f * scale, 0.f, 0.16f * scale);
        glTexCoord2f(0.5f, 0.f);
        glVertex3d(0.31f * scale, 0.f, 0.16f * scale);
        glTexCoord2f(0.5f, 0.5f);
        glVertex3d(0.31f * scale, 0.05f * scale, 0.16f * scale);
        glTexCoord2f(0.f, 0.5f);
        glVertex3d(-0.01f * scale, 0.05f * scale, 0.16f * scale);

        glTexCoord2f(0.f, 0.f);
        glVertex3d(-0.01f * scale, 0.05f * scale, 0.16f * scale);
        glTexCoord2f(1.f, 0.f);
        glVertex3d(0.31f * scale, 0.05f * scale, 0.16f * scale);
        glTexCoord2f(1.f, 1.f);
        glVertex3d(0.3f * scale, 0.3f * scale, 0.16f * scale);
        glTexCoord2f(0.f, 1.f);
        glVertex3d(0.f, 0.3f * scale, 0.16f * scale);

        //COTES BAS
        glTexCoord2f(0.f, 0.f);
        glVertex3d(-0.01f * scale, 0.f, -0.01f * scale);
        glTexCoord2f(0.5f, 0.f);
        glVertex3d(-0.01f * scale, 0.05f * scale, -0.01f * scale);
        glTexCoord2f(0.5f, 0.5f);
        glVertex3d(-0.01f * scale, 0.05f * scale, 0.16f * scale);
        glTexCoord2f(0.f, 0.5f);
        glVertex3d(-0.01f * scale, 0.f, 0.16f * scale);

        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.31f * scale, 0.f, -0.01f * scale);
        glTexCoord2f(0.5f, 0.f);
        glVertex3d(0.31f * scale, 0.05f * scale, -0.01f * scale);
        glTexCoord2f(0.5f, 0.5f);
        glVertex3d(0.31f * scale, 0.05f * scale, 0.16f * scale);
        glTexCoord2f(0.f, 0.5f);
        glVertex3d(0.31f * scale, 0.f, 0.16f * scale);

        // SURFACE BAS
        glTexCoord2f(0.f, 0.f);
        glVertex3d(-0.01f * scale, 0.05f * scale, -0.01f * scale);
        glTexCoord2f(1.f, 0.f);
        glVertex3d(0.31f * scale, 0.05f * scale, -0.01f * scale);
        glTexCoord2f(1.f, 1.f);
        glVertex3d(0.31f * scale, 0.05f * scale, 0.16f * scale);
        glTexCoord2f(0.f, 1.f);
        glVertex3d(-0.01f * scale, 0.05f * scale, 0.16f * scale);

    glEnd();

    //DESSUS EPAULE G
    glBegin(GL_QUAD_STRIP);
        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.f, 0.3f * scale, -0.01f * scale);
        glTexCoord2f(0.1f, 0.f);
        glVertex3d(0.06f * scale, 0.3f * scale, -0.01f * scale);

        glTexCoord2f(0.f, 0.1f);
        glVertex3d(0.f * scale, 0.32f * scale, -0.005f * scale);
        glTexCoord2f(0.1f, 0.1f);
        glVertex3d(0.06f * scale, 0.32f * scale, -0.005f * scale);

        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.f, 0.34f * scale, 0.005f * scale);
        glTexCoord2f(0.1f, 0.f);
        glVertex3d(0.06f * scale, 0.34f * scale, 0.005f * scale);

        glTexCoord2f(0.f, 0.1f);
        glVertex3d(0.f, 0.36f * scale, 0.02f* scale);
        glTexCoord2f(0.1f, 0.1f);
        glVertex3d(0.06f * scale, 0.36f * scale, 0.02f * scale);

        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.f, 0.37f * scale, 0.045f * scale);
        glTexCoord2f(0.1f, 0.f);
        glVertex3d(0.06f * scale, 0.37f * scale, 0.045f * scale);
    /////////////////////////////////////////////////////////
        glTexCoord2f(0.f, 0.1f);
        glVertex3d(0.f, 0.38f * scale, 0.075f * scale);
        glTexCoord2f(0.1f, 0.1f);
        glVertex3d(0.06f * scale, 0.38f * scale, 0.075f * scale);
    /////////////////////////////////////////////////////////
        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.f, 0.37f * scale, 0.105f * scale);
        glTexCoord2f(0.1f, 0.f);
        glVertex3d(0.06f * scale, 0.37f * scale, 0.105f * scale);

        glTexCoord2f(0.f, 0.1f);
        glVertex3d(0.f, 0.36f * scale, 0.13f * scale);
        glTexCoord2f(0.1f, 0.1f);
        glVertex3d(0.06f * scale, 0.36f * scale, 0.13f * scale);

        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.f, 0.34f * scale, 0.145f * scale);
        glTexCoord2f(0.1f, 0.f);
        glVertex3d(0.06f * scale, 0.34f * scale, 0.145f * scale);

        glTexCoord2f(0.f, 0.1f);
        glVertex3d(0.f, 0.32f * scale, 0.155f * scale);
        glTexCoord2f(0.1f, 0.1f);
        glVertex3d(0.06f * scale, 0.32f * scale, 0.155f * scale);

        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.f, 0.3f * scale, 0.16f * scale);
        glTexCoord2f(0.1f, 0.f);
        glVertex3d(0.06f * scale, 0.3f * scale, 0.16f * scale);
    glEnd();

    //DESSUS EPAULE D
    glBegin(GL_QUAD_STRIP);
        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.24f * scale, 0.3f * scale, -0.01f * scale);
        glTexCoord2f(0.1f, 0.f);
        glVertex3d(0.3f * scale, 0.3f * scale, -0.01f * scale);

        glTexCoord2f(0.f, 0.1f);
        glVertex3d(0.24f * scale, 0.32f * scale, -0.005f * scale);
        glTexCoord2f(0.1f, 0.1f);
        glVertex3d(0.3f * scale, 0.32f * scale, -0.005f * scale);

        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.24f * scale, 0.34f * scale, 0.005f * scale);
        glTexCoord2f(0.1f, 0.f);
        glVertex3d(0.3f * scale, 0.34f * scale, 0.005f * scale);

        glTexCoord2f(0.f, 0.1f);
        glVertex3d(0.24f * scale, 0.36f * scale, 0.02f * scale);
        glTexCoord2f(0.1f, 0.1f);
        glVertex3d(0.3f * scale, 0.36f * scale, 0.02f * scale);

        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.24f * scale, 0.37f * scale, 0.045f * scale);
        glTexCoord2f(0.1f, 0.f);
        glVertex3d(0.3f * scale, 0.37f * scale, 0.045f * scale);
    /////////////////////////////////////////////////////////
        glTexCoord2f(0.f, 0.1f);
        glVertex3d(0.24f * scale, 0.38f * scale, 0.075f * scale);
        glTexCoord2f(0.1f, 0.1f);
        glVertex3d(0.3f * scale, 0.38f * scale, 0.075f * scale);
    /////////////////////////////////////////////////////////
        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.24f * scale, 0.37f * scale, 0.105f * scale);
        glTexCoord2f(0.1f, 0.f);
        glVertex3d(0.3f * scale, 0.37f * scale, 0.105f * scale);

        glTexCoord2f(0.f, 0.1f);
        glVertex3d(0.24f * scale, 0.36f * scale, 0.13f * scale);
        glTexCoord2f(0.1f, 0.1f);
        glVertex3d(0.3f * scale, 0.36f * scale, 0.13f * scale);

        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.24f * scale, 0.34f * scale, 0.145f * scale);
        glTexCoord2f(0.1f, 0.f);
        glVertex3d(0.3f * scale, 0.34f * scale, 0.145f * scale);

        glTexCoord2f(0.f, 0.1f);
        glVertex3d(0.24f * scale, 0.32f * scale, 0.155f * scale);
        glTexCoord2f(0.1f, 0.1f);
        glVertex3d(0.3f * scale, 0.32f * scale, 0.155f * scale);

        glTexCoord2f(0.f, 0.f);
        glVertex3d(0.24f * scale, 0.3f * scale, 0.16f * scale);
        glTexCoord2f(0.1f, 0.f);
        glVertex3d(0.3f * scale, 0.3f * scale, 0.16f * scale);

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
