//
// Created by Unknow on 07/04/2020.
//

#ifndef ROBOT_CLANK_CLANK_H
#define ROBOT_CLANK_CLANK_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "glut.h"
#include "SOIL.h"

#include "Arms.h"
#include "Body.h"
#include "Head.h"

#define MOVE_SPEED 0.01f
#define ROTATION_SPEED 1.f

class Clank {
public:
    Clank();

    Clank(float scale, float posx, float posy, float posz, float rotx, float roty, float rotz);

    void ConstructDefault();

    void Draw();

    void updatePos();

    void updateMembersPos();

    void updateRotation();

    void updateMemberAnimations();

    void enableWalkingAnimation();

    void disableWalkingAnimation();

    void setHeadRotationDelta(char delta);

    void LoadTextures(void);

    float getPosx() const;

    void setPosx(float posx);

    float getPosy() const;

    void setPosy(float posy);

    float getPosz() const;

    void setPosz(float posz);

    float getDirx() const;

    void setDirx(float dirx);

    float getDiry() const;

    void setDiry(float diry);

    float getDirz() const;

    void setDirz(float dirz);

    float getRotx() const;

    void setRotx(float rotx);

    float getRoty() const;

    void setRoty(float roty);

    float getRotz() const;

    void setRotz(float rotz);

    float getAngleh() const;

    void setAngleh(float angleh);

    float getAnglev() const;

    void setAnglev(float anglev);

    float getDeltaAnglex() const;

    void setDeltaAnglex(float deltaAnglex);

    float getDeltaAngley() const;

    void setDeltaAngley(float deltaAngley);

    char getDeltaForward() const;

    void setDeltaForward(char deltaForward);

    char getDeltaStrafe() const;

    void setDeltaStrafe(char deltaStrafe);

private:

    GLuint ListeTextures[20];
    float posx;
    float posy;
    float posz;

    float dirx;
    float diry;
    float dirz;

    float rotx;
    float roty;
    float rotz;

    float scale;

    float anglev;

    float deltaAngley;

    char deltaForward;
    char deltaStrafe;
    char walkingAnimation;

    Arms *rightArm;
    Arms *leftArm;
    Body *body;
    Head *head;
};

#endif //ROBOT_CLANK_CLANK_H
