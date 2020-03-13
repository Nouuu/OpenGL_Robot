#include<windows.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include<stdlib.h>
#include<stdio.h>


float angle = 0.0;
float angle2 = 0.0;
float angleAlpha = 0.0;
float angleBeta = 0.0;
float X0 = 0.0;
float Y0 = 0.0;
float Z0 = 0.0;
float distanceR = 10.0;
bool coucou = false;
bool up;


/* prototypes de fonctions */
void initRendering();

void display(void);

void reshape(int w, int h);

void update(int value);

void keyboard(unsigned char key, int x, int y);

void moveCamera();


/* Programme principal */
int main(int argc, char **argv) {

    /* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("TP2: primitives 3D et illumination");

    /* Initialisation d'OpenGL */
    initRendering();

    /* Enregistrement des fonctions de rappel */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(20, update, 0);
    glutKeyboardFunc(keyboard);

    /* Entrée dans la boucle principale de glut, traitement des évènements */
    glutMainLoop();
    return 0;
}


/* Initialisation d'OpenGL pour le rendu de la scène */
void initRendering() {

    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);

    /* Activation des couleurs */
    glEnable(GL_COLOR_MATERIAL);

    /* définit la couleur d'effacement et la couleur de fond */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* Activation des lumières */
    //glEnable(GL_LIGHTING);          // Activation du mode
    //glEnable(GL_LIGHT0);            // Activation lumière n°0
    //glEnable(GL_LIGHT1);            // Activation lumière n°1
    //glEnable(GL_LIGHT2);            // Activation lumière n°2

    /* Les normales (crées par glNormal(*)) sont automatiquement unitaires */
    glEnable(GL_NORMALIZE);


    /* Activation du mode ombrage (shading) et lissage (smooth) des couleur */
    glShadeModel(GL_SMOOTH);

    /*  définit la taille d'un pixel*/
    glPointSize(2.0);

}

/* Création de la scène avec lampes */
void display(void) {

    /* Déclaration des couleurs et positions des lampes */
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};   // Color (0.2, 0.2, 0.2)

    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f};    // Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f};      // Positioned at (4, 0, 8)


    /* Déclaration des différents types de matière des sphères */
    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient_color[] = {0.8, 0.8, 0.2, 1.0};
    GLfloat mat_diffuse[] = {0.1, 0.5, 0.8, 1.0};
    GLfloat mat_diffuseB[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat no_shininess[] = {0.0};
    GLfloat low_shininess[] = {5.0};
    GLfloat high_shininess[] = {100.0};
    GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);


    glLoadIdentity();


//    glTranslatef(0.0f, 0.0f, -5.0f);                      // déplacement caméra
    gluLookAt(X0, Y0, Z0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glColor3f(1.0f, 1.0f, 1.0f);


    // Ajout lumière ambiante
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    // Ajout lumière positionnelle L0
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);        // lumière diffuse
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);         // position

    glPushMatrix();
    glTranslatef(-3, 0.5, 0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(1, -0.5, 0);
    glPushMatrix();
    glScalef(2, 1, 1);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.3, 0, -0.1);
    glutWireSphere(0.5, 10, 10);
    glPopMatrix();

    glTranslatef(1, 0.5, 0);
    glRotatef(angle2, 0, 0, 1);
    glTranslatef(1, -0.5, 0);

    glPushMatrix();
    glScalef(2, 1, 1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();


    glutSwapBuffers();

    /* On force l'affichage */
    glFlush();
}

void moveCamera() {
    X0 = distanceR * cos(angleBeta) * sin(angleAlpha);
    Y0 = distanceR * sin(angleBeta);
    Z0 = distanceR * cos(angleBeta) * cos(angleAlpha);
}


/* Fonction de mise à jour: mouvements des objets*/
void update(int value) {

    if (coucou) {
        if (up) {
            if (angle2 > 57)
                up = !up;
            else
                angle2 += 1.0;
        } else {
            if (angle2 < 0)
                up = !up;
            else
                angle2 -= 1.0;
        }
    } else {
        if (angle > 360 || angle < -360) {
            angle = 0;
        }
        if (angle2 > 57) {
            angle2 = 57;
        }
        if (angle2 < 0) {
            angle2 = 0;
        }
    }

    if (angleAlpha > 2 * M_PI) {
        angleAlpha = 0.01;
    }
    if (angleAlpha < 0.0) {
        angleAlpha = 2 * M_PI - 0.01;
    }
    if (angleBeta >= M_PI / 2) {
        angleBeta = M_PI / 2 - 0.01;
    }
    if (angleBeta <= -M_PI / 2) {
        angleBeta = -M_PI / 2 + 0.01;
    }

    moveCamera();

    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}


/*  Mise en forme de la scène pour l'affichage */
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 200.0);


}


/* Fonction de gestion au clavier des activations des lumières */
void keyboard(unsigned char key, int x, int y) {
    switch (key) {

        case 'z':
            angleAlpha += .05;
            break;
        case 's':
            angleAlpha -= .05;
            break;
        case 'q':
            angleBeta += .05;
            break;
        case 'd':
            angleBeta -= .05;
            break;
        case 'c':
            coucou = !coucou;
            up = true;
            break;
        case 'w':   /* Quitter le programme */
            printf("Exit program !\n");
            exit(0);
    }
}
