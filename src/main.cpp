#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

#include "Camera.h"
#include "Map.h"
#include "Clank.h"


// Objet Camera
Camera *cam = new Camera();
// Objet Scène
Map *m = new Map();
// Objet bras
Clank *clank = new Clank(.5f, 0.f, 0.2f, 0.f, 0.f, 0.f, 0.f);

// Titre fenêtre
const char *windowTitle = "Clank";


/** GESTION FENETRE **/
void reshapeWindow(int w, int h) {
    if (h == 0)
        h = 1;

    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 348.0f);
    glMatrixMode(GL_MODELVIEW);
}

/** FONCTIONS DE GESTION CLAVIER **/
void KeyboardDown(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'e': // Unlock Camera
            cam->locked = (cam->locked) ? 0 : 1;
            break;
        case 'z':
            cam->deltaForward = 1;
            break;
        case 's':
            cam->deltaForward = -1;
            break;
        case 'd':
            cam->deltaStrafe = -1;
            break;
        case 'q':
            cam->deltaStrafe = 1;
            break;
        case '8':
            clank->setDeltaForward(1);
            break;
        case '2':
            clank->setDeltaForward(-1);
            break;
        case '4':
            clank->setDeltaStrafe(1);
            break;
        case '6':
            clank->setDeltaStrafe(-1);
            break;
    }
}

void KeyboardUp(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'z':
        case 's':
            cam->deltaForward = 0;
            break;
        case 'q':
        case 'd':
            cam->deltaStrafe = 0;
            break;
        case '8':
        case '2':
            clank->setDeltaForward(0);
            break;
        case '4':
        case '6':
            clank->setDeltaStrafe(0);
            break;
    }
}

void SpecialDown(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_UP:
            cam->deltaForward = 1;
            break;
        case GLUT_KEY_DOWN:
            cam->deltaForward = -1;
            break;
        case GLUT_KEY_RIGHT:
            cam->deltaStrafe = -1;
            break;
        case GLUT_KEY_LEFT:
            cam->deltaStrafe = 1;
            break;
    }
}

void SpecialUp(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            cam->deltaForward = 0;
            break;
        case GLUT_KEY_RIGHT:
        case GLUT_KEY_LEFT:
            cam->deltaStrafe = 0;
            break;
    }
}

/** FONCTIONS DE GESTION SOURIS (ORIENTATION CAMERA) **/
void mouseMove(int x, int y) {
    // Rentres uniquement lors du clic
    cam->orienterCam(x, y);
}

void mouseButton(int button, int state, int x, int y) {
    // Gestion camera en fonction du clic souris
    if (button == GLUT_LEFT_BUTTON) {
        // Relacher la camera
        if (state == GLUT_UP) {
            cam->releaseCam();
        }
            // Mise à jour origine du clic
        else {
            cam->grabCam(x, y);
        }
    }
}

/** GESTION DEPLACEMENT CAMERA **/
void computePos(int inutile) {
    cam->updatePos();
    glutTimerFunc(10, computePos, 0);
}

void clankPos(int inutile) {
    clank->updatePos();
    glutTimerFunc(10, clankPos, 0);
}

/** AFFICHAGE **/
void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Définition de la caméra
    gluLookAt(cam->posx, cam->posy, cam->posz,
              cam->posx + cam->dirx, cam->posy + cam->diry, cam->posz + cam->dirz,
              0.0f, 1.0f, 0.0f
    );

    m->DrawGround();
    m->DrawSkybox(cam);
    clank->Draw();
    glutSwapBuffers();
}

void LoadTextures() {
    m->LoadTextures();
}

int main(int argc, char **argv) {
    /** CREATION FENETRE **/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow(windowTitle);

    /** INIT TEXTURES **/
    LoadTextures();

    /** FONCTIONS GLUT **/
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshapeWindow);
    glutIdleFunc(renderScene);
    glutTimerFunc(10, computePos, 0);
    glutTimerFunc(10, clankPos, 0);

    /** GESTION CLAVIER **/
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(KeyboardDown);
    glutKeyboardUpFunc(KeyboardUp);
    glutSpecialFunc(SpecialDown);
    glutSpecialUpFunc(SpecialUp);

    /** GESTION SOURIS **/
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    /** INIT GL STATES **/
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glutMainLoop();

    return (1);
}


