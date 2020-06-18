#include "Box.h"
#include <string.h>

Box::Box(float scale, float posx, float posy, float posz, float angle, char *texture) {
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;

    this->angle = angle;

    this->scale = scale;

    if (!strcmp(texture, "wood")) {
        textures = SOIL_load_OGL_texture("img/caisse_bois.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    } else {
        textures = SOIL_load_OGL_texture("img/caisse_metal_2.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                         SOIL_FLAG_INVERT_Y);
    }

}

void Box::Draw() {
    glPushMatrix();
        // Active le placage de textures a deux dimensions
        glEnable(GL_TEXTURE_2D);

        // Définit et conserve une couleur courante
        glColor3f(1.0f, 1.0f, 1.0f);

        // Spécifie la texture
        glBindTexture(GL_TEXTURE_2D, textures);

        // Set les paramètres de la texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // dimension horizontale de la texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // dimension verticale de la texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Méthode d'agrandissement
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Méthode de réduction


        glTranslatef(posx, posy, posz);
        glRotatef(angle, 0.0f, 1.0f, 0.0f);

        /** FRONT **/

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glTexCoord2f(1.0f, 0.f);
            glVertex3f(0.0f, scale, 0.0f);
            glTexCoord2f(1.f, 1.f);
            glVertex3f(scale, scale, 0.0f);
            glTexCoord2f(0.f, 1.0f);
            glVertex3f(scale, 0.0f, 0.0f);

            /** BACK **/


            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, scale);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(0.0f, scale, scale);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(scale, scale, scale);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(scale, 0.0f, scale);

            /** TOP **/

            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(0.0f, scale, 0.0f);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(0.0f, scale, scale);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(scale, scale, scale);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(scale, scale, 0.0f);

            /** BOT **/

            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, scale);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(scale, 0.0f, scale);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(scale, 0.0f, 0.0f);

            /** LEFT **/

            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, scale);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(0.0f, scale, scale);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(0.0f, scale, 0.0f);

            /** RIGHT **/

            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(scale, 0.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(scale, 0.0f, scale);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(scale, scale, scale);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(scale, scale, 0.0f);
        glEnd();

    glPopMatrix();
}

