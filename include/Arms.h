//
// Created by Unknow on 20/03/2020.
//

#ifndef SOIL_TEST_ARMS_H
#define SOIL_TEST_ARMS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "glut.h"
#include "SOIL.h"

class Arms {
public:
    Arms();

    Arms(float scale, float posx, float posy, float posz, float rotx, float roty, float rotz);

    void Draw();

    void DrawShoulder(GLUquadric *pObj);

    void DrawUpperarm(GLUquadric *pObj);

    void DrawElbow(GLUquadric *pObj);

    void DrawForearm(GLUquadric *pObj);

    void DrawHand(GLUquadric *pObj);

    void SetTexture(int index, GLuint texture);

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

    float getShoulderRotation() const;

    void setShoulderRotation(float shoulderRotation);

    float getForearmRotation() const;

    void setForearmRotation(float forearmRotation);

    const GLuint *getTextures() const;

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


#endif //SOIL_TEST_ARMS_H
