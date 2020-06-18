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
// Objet Clank
Clank *clank = new Clank(1.f, 0.f, -0.1f, 0.f, 0.f, 0.f, 0.f);

// Titre fenêtre
const char *windowTitle = "Clank";


/** GESTION FENETRE **/
void reshapeWindow(int w, int h) {
    if (h == 0)
        h = 1;

    float ratio = w * 1.0 / h;

    // Transformation de projection
    // Avant d'effectuer toute commande liée à la projection, il est faut changer d'état en exécutant ces commandes
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // La transformation de cadrage
    // glViewport(GLint x, GLint y, GLint largeur, GLint hauteur) sera utilisée pour définir une zone rectangulaire de
    // pixels dans la fenêtre dans laquelle l'image finale sera affichée.
    // Par défaut, les valeurs initiales du cadrage sont (0,0, largeurFenêtre, hauteurFenêtre)
    glViewport(0, 0, w, h);

    // gluPerspective(fov, rapport,proche,loin) Spécifie une matrice de projection perspective par un volume d’observation.
    gluPerspective(45.0f, ratio, 0.1f, 348.0f);

    // la pile des transformations point de vue est selectionnée
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
            clank->setDeltaForward(-1);
            clank->enableWalkingAnimation();
            break;
        case '2':
            clank->setDeltaForward(1);
            clank->enableWalkingAnimation();
            break;
        case '4':
            clank->setDeltaAngley(1);
            clank->setHeadRotationDelta(1);
            break;
        case '6':
            clank->setDeltaAngley(-1);
            clank->setHeadRotationDelta(-1);
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
            clank->disableWalkingAnimation();
            break;
        case '4':
        case '6':
            clank->setDeltaAngley(0);
            clank->setHeadRotationDelta(0);
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
    // Update la posx et posz, la position des membres et leurs animations
    clank->updatePos();
    // Update l'angle
    clank->updateRotation();
    // Rappel toutes les 10 millisecondes
    glutTimerFunc(10, clankPos, 0);
}

/** AFFICHAGE **/
void renderScene(void) {
    // Avant l'affichage d'une scène
    // GL_COLOR_BUFFER_BIT = Effacement des pixels du buffer d'affichage
    // GL_DEPTH_BUFFER_BIT = Effacement de l'information de profondeur associée à chaque pixel du buffer d'affichage
    //                       (information utilisée pour l'élimination des parties cachées)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initialisationde la transformation
    glLoadIdentity();

    // Définition de la caméra
    // modifie le GL_MODELVIEW (transformations point de vue) pour régler la transformation de la caméra
    gluLookAt(cam->posx, cam->posy, cam->posz,
              cam->posx + cam->dirx, cam->posy + cam->diry, cam->posz + cam->dirz,
              0.0f, 1.0f, 0.0f
    );

    // Dessin du sol, des boîtes et des boulons
    m->DrawGround(clank->getPosx(), clank->getPosz());
    // Dessin de la skybox
    m->DrawSkybox(cam);
    // Dessin de Clank
    clank->Draw();

    // Echange les buffers de la fenêtre courante
    // Le contenu du buffer arrière devient le contenu du buffer avant
    // Le contenu du buffer arrière devient indéfini
    // En plus simple : envoie l'image calculée à l'écran
    glutSwapBuffers();
}

void LoadTextures() {
    // Chargement des textures de la map
    m->LoadTextures();
    // Chargement des textures de Clank
    clank->LoadTextures();
}

int main(int argc, char **argv) {
    /** CREATION FENETRE **/
    // Initialise la bibliothèque GLUT et négocie une session avec le système defenêtrage
    glutInit(&argc, argv);

    // Mode d'affichage utilisé pour créer les fenêtres et les sous-fenêtres (param = masques de bits)
    // GLUT_RGBA = modèle de couleur RGB (par défaut si aucun n'est spécifié)
    // GLUT_DOUBLE = utilisation d'un double buffer
    // GLUT_DEPTH = fenêtre avec un tampon de profondeur
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    // Position du coin supérieur gauche
    glutInitWindowPosition(50, 50);
    // Taille de la fenêtre
    glutInitWindowSize(1600, 900);

    // Création de la fenêtre
    glutCreateWindow(windowTitle);

    // Prise en compte de l'éclairage
    glEnable(GL_LIGHTING);

    /** INIT TEXTURES **/
    // Chargement des textures (map + Clank)
    LoadTextures();

    /** FONCTIONS GLUT **/
    // Identifie la fonction de rappel d'affichage (callback)
    glutDisplayFunc(renderScene);
    // Action a exécuter quand la fenêtre est resizée
    glutReshapeFunc(reshapeWindow);

    // Etablit la fonction de rappel au repos de telle sorte que GLUT peut effectuer des tâches de traitement en arrière-plan
    // ou effectuer une animation continue lorsque aucun événement n'est reçu.
    // Continuellement appelée lorsque aucun événement n'est reçu.
    glutIdleFunc(renderScene);

    // Fonctions de déplacement appelées toutes les 10 millisecondes
    glutTimerFunc(10, computePos, 0);
    glutTimerFunc(10, clankPos, 0);

    /** GESTION CLAVIER **/
    // Désactive la répétitions d'évenements clavier
    glutIgnoreKeyRepeat(1);
    // Evénements liés aux touches du clavier
    glutKeyboardFunc(KeyboardDown);
    glutKeyboardUpFunc(KeyboardUp);
    glutSpecialFunc(SpecialDown);
    glutSpecialUpFunc(SpecialUp);

    /** GESTION SOURIS **/
    // Evénement de pression sur un bouton de la souris
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    /** INIT GL STATES **/
    // Active le test de profondeur
    glEnable(GL_DEPTH_TEST);
    // Active le placage de textures a deux dimensions
    glEnable(GL_TEXTURE_2D);

    // Boucle principale
    glutMainLoop();

    return (1);
}


