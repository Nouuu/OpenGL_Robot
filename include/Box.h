#ifndef BOX_H
#define BOX_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "SOIL.h"

#define ANCHOR_FROM_ORIGIN 0
#define ANCHOR_FROM_CENTER 1

#define TEXTURE_SCALE 1.0f

class Box {
public:
    Box(float scale, float posx, float posy, float posz, float angle, char *texture);

    void Draw();

    float posx;
    float posy;
    float posz;

    float angle;

    float scale;
protected:

private:
    GLuint textures;
};

#endif // BOX_H
