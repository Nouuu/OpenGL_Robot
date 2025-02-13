#ifndef MAP_H
#define MAP_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <cstring>

#include "glut.h"
#include "SOIL.h"
#include <stdio.h>

#include "Camera.h"
#include "Box.h"
#include "Bolt.h"

typedef struct {
    float posX;
    float posZ;
    float rot;
    char checked;
} RandomPos;

class Map {
public:
    Map();

    // Stockage des r�f�rences aux textures
    GLuint ListeTextures[21];
    GLuint Skybox[6];

    void LoadTextures(void);

    void DrawGround(float clankX, float clankZ);

    void DrawSkybox(Camera *cam);

    void DrawBox();

    void DrawBoxPack1(float x, float z, float rot, Box *box1);

    void DrawBoxPack2(float x, float z, float rot, Box *box1);

    void DrawBolt(float clankX, float clankZ);

    char checkCollision(float clankX, float clankZ, float boltX, float boltZ);

protected:
private:
    GLuint textures[6];
    RandomPos randomPos[50];
};

#endif // MAP_H
