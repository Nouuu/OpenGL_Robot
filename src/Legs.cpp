#include "Legs.h"

float scale = 1.0f;

// LEG
float thighLength = 0.5f * scale;
float calfLength = 0.5f * scale;
float legGirth = 0.06f * scale;

// FOOT
float footLength = 0.5f * scale;
float footWidth = 0.1f * scale;
float footHeight = 0.2f * scale;
float heelLength = 0.0f * scale;
float toeLength = footLength + footLength * 0.25f;

// ARTICULATION
float kneeWidth = footWidth * 2.3f;
float kneeGirth = 0.05f;
float ankleWidth = footWidth * 2.3f;
float ankleGirth = 0.05f;


Legs::Legs()
{

}

void Legs::DrawLeg() {
    GLUquadric *pObj = gluNewQuadric();
    gluQuadricTexture(pObj, GL_TRUE);

    // Thigh
    glPushMatrix();
        glTranslatef(0, footHeight + calfLength + thighLength, 0);
        glRotatef(90, 1, 0, 0);
        gluCylinder(pObj, legGirth, legGirth, thighLength, 32, 32);
    glPopMatrix();

    // Knee
    glPushMatrix();
        glTranslatef(-kneeWidth/2, footHeight + calfLength, 0);
        glRotatef(90, 0, 1, 0);
        gluCylinder(pObj, kneeGirth, kneeGirth, kneeWidth, 32, 32);
        gluDisk (pObj, 0, kneeGirth, 32, 32);
        glTranslatef(0, 0, kneeWidth);
        gluDisk (pObj, 0, kneeGirth, 32, 32);
    glPopMatrix();

    // Calf
    glPushMatrix();
        glTranslatef(0, footHeight + calfLength, 0);
        glRotatef(90, 1, 0, 0);
        gluCylinder(pObj, legGirth, legGirth, calfLength, 32, 32);
    glPopMatrix();

    // Ankle
    glPushMatrix();
        glTranslatef(-ankleWidth/2, footHeight, 0);
        glRotatef(90, 0, 1, 0);
        gluCylinder(pObj, ankleGirth, ankleGirth, ankleWidth, 32, 32);
        gluDisk (pObj, 0, ankleGirth, 32, 32);
        glTranslatef(0, 0, ankleWidth);
        gluDisk (pObj, 0, ankleGirth, 32, 32);
    glPopMatrix();

    // Foot
    glPushMatrix();
        // BASE OF THE FOOT
        glBegin(GL_QUADS);
            // Top face
            glVertex3f(footWidth, footHeight, -heelLength);       // back right
            glVertex3f(-footWidth, footHeight, -heelLength);       // back left
            glVertex3f(-footWidth, footHeight,  footLength);       // front left
            glVertex3f(footWidth, footHeight,  footLength);       // front right

            // Bottom face
            glVertex3f(footWidth, 0.0f,  footLength);          // front right
            glVertex3f(-footWidth, 0.0f,  footLength);          // front left
            glVertex3f(-footWidth, 0.0f, -heelLength);          // back left
            glVertex3f(footWidth, 0.0f, -heelLength);          // back right

            // Back face
            glVertex3f(footWidth, 0.0f, -heelLength);          // bottom right
            glVertex3f(-footWidth, 0.0f, -heelLength);          // bottom left
            glVertex3f(-footWidth,  footHeight, -heelLength);      // top left
            glVertex3f(footWidth,  footHeight, -heelLength);      // top right

            // Left face
            glVertex3f(-footWidth,  footHeight,  footLength);      // top right
            glVertex3f(-footWidth,  footHeight, -heelLength);      // top left
            glVertex3f(-footWidth, 0.0f, -heelLength);          // bottom left
            glVertex3f(-footWidth, 0.0f,  footLength);          // bottom right

            // Right face
            glVertex3f(footWidth,  footHeight, -heelLength);       // top right
            glVertex3f(footWidth,  footHeight,  footLength);       // top left
            glVertex3f(footWidth, 0.0f,  footLength);           // bottom left
            glVertex3f(footWidth, 0.0f, -heelLength);           // bottom right
        glEnd();

        // TOES
        glBegin(GL_TRIANGLES);
            // Top face
            glVertex3f(footWidth, footHeight,  footLength);       // base right
            glVertex3f(-footWidth, footHeight, footLength);       // base left
            glVertex3f(0, 0.0f, toeLength);                 // point

            // Bottom face
            glVertex3f(footWidth, 0.0f,  footLength);          // base right
            glVertex3f(-footWidth, 0.0f, footLength);          // base left
            glVertex3f(0, 0.0f, toeLength);                 // point

            // Left face
            glVertex3f(-footWidth,  footHeight,  footLength);      // base top
            glVertex3f(-footWidth,  0.0f, footLength);          // base bottom
            glVertex3f(0, 0.0f, toeLength);                 // point

            // Right face
            glVertex3f(footWidth,  footHeight,  footLength);        // base top
            glVertex3f(footWidth,  0.0f, footLength);           // base bottom
            glVertex3f(0, 0.0f, toeLength);                 // point
        glEnd();

    glPopMatrix();

    gluDeleteQuadric (pObj);
}
