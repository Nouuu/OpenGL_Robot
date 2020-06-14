#ifndef BOLT_H
#define BOLT_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "SOIL.h"

#define ANCHOR_FROM_ORIGIN 0
#define ANCHOR_FROM_CENTER 1

#define TEXTURE_SCALE 1.0f

class Bolt
{
    public:
        Bolt(float scale, float posx, float posy, float posz, float angleX,float angleY, float angleZ);
        void Draw();

        float posx;
        float posy;
        float posz;

        float angleX;
        float angleY;
        float angleZ;

        float scale;
};

#endif // BOLT_H
