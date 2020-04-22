#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "glut.h"
#include "SOIL.h"

class Head {
public:
    Head();

    Head(float scale, float posx, float posy, float posz, float rotx, float roty, float rotz);

    void Draw();

    void drawHalfSphere(int scaley, int scalex, GLfloat rayon);
private:
    float posx;
    float posy;
    float posz;

    float rotx;
    float roty;
    float rotz;

    float shoulderRotation;
    float forearmRotation;

    float scale;

    GLuint textures[6];
};
