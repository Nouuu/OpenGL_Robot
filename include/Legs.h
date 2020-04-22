#ifndef SOIL_TEST_LEGS_H
#define SOIL_TEST_LEGS_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "SOIL.h"

typedef struct {
    char isWalking;
    char walkingShoulderWay;
    float walkingMaxRotation;
    float walkingMinRotation;
    float walkingCurrentRotation;
    float animationSpeed;
} WalkingLegs;

class Legs {
public:
    Legs();

    Legs(float scale, float posx, float posy, float posz, float roty);

    void ConstructDefault();

    void Draw();

    void setWalkingAnimationActive();

    void setWalkingAnimationInactive();

    void UpdateWalkingAnimation();

    void UpdateAnimation();

    void StopWalking();

    void InverseWalkingAnimationWay();


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

    float getScale() const;

    void setScale(float scale);

    const GLuint *getTextures() const;

    void SetTexture(int index, GLuint texture);

protected:
private:
    float posx;
    float posy;
    float posz;

    float rotx;
    float roty;
    float rotz;

    float scale;

    GLuint textures[6];

    float thighLength;
    float calfLength;
    float legGirth;
    float legGap;

// FOOT
    float footLength;
    float footWidth;
    float footHeight;
    float heelLength;
    float toeLength;

// ARTICULATION
    float kneeWidth;
    float kneeGirth;
    float ankleWidth;
    float ankleGirth;

    WalkingLegs walkingLegs;

};


#endif //SOIL_TEST_LEGS_H
