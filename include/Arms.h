//
// Created by Unknow on 20/03/2020.
//

#ifndef SOIL_TEST_ARMS_H
#define SOIL_TEST_ARMS_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "SOIL.h"

class Arms {
public:
    Arms();

    Arms(float x, float y, float z, float posx, float posy, float posz);

    void Draw();

    void SetTexture(int index, GLuint texture);

    float getPosx() const;

    void setPosx(float posx);

    float getPosy() const;

    void setPosy(float posy);

    float getPosz() const;

    void setPosz(float posz);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);

    const GLuint *getTextures() const;

private:
    float posx;
    float posy;
    float posz;

    float x;
    float y;
    float z;

    GLuint textures[6];
};


#endif //SOIL_TEST_ARMS_H
