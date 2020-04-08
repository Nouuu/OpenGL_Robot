//
// Created by Unknow on 08/04/2020.
//

#ifndef ROBOT_CLANK_BODY_H
#define ROBOT_CLANK_BODY_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "SOIL.h"

class Body {
public:
    Body();

    Body(float scale, float posx, float posy, float posz, float rotx, float roty, float rotz);

    void ConstructDefault();

    void Draw();

    void DrawInterior(GLUquadric *pObj);

    void DrawExterior(GLUquadric *pObj);

    void UpdateAnimations();

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

    const GLuint *getTextures() const;

private:
    float posx;
    float posy;
    float posz;

    float rotx;
    float roty;
    float rotz;

    float scale;

    GLuint textures[6];
};

#endif //ROBOT_CLANK_BODY_H
