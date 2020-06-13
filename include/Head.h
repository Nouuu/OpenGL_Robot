#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "glut.h"
#include "SOIL.h"

typedef struct {
    char deltaHeadJaw;
    char deltaRotation;
    char isWalking;
    float currentRotation;
    float headJawCurrentRotation;
    float headJawMaxRotation;
    float headJawSpeed;
    float maxRotation;
    float rotationSpeed;
} headAnimation;

class Head {
public:
    Head();

    Head(float scale, float posx, float posy, float posz, float roty);

    void Draw();

    void drawHalfSphere(int scaley, int scalex, GLfloat rayon);

private:
    float posx;
    float posy;
    float posz;

    float rotx;
    float roty;
    float rotz;

    headAnimation headAnimation1;
public:
    void defaultConstruct();

    void setDeltaRotation(char delta);

    void setWalkingAnimationActive();

    void setWalkingAnimationInactive();

    void updateHeadWalkingAnimation();

    void updateHeadRotation();

    void updateAnimation();

    float getPosx() const;

    void setPosx(float posx);

    float getPosy() const;

    void setPosy(float posy);

    float getPosz() const;

    void setPosz(float posz);

    float getRotx() const;

    void setRotx(float rotx);

    float getRoty() const;

    void setRoty(float roty);

    float getRotz() const;

    void setRotz(float rotz);

private:
    float scale;

    GLuint textures[6];
};
