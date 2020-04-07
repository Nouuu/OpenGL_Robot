#ifndef MAP_H
#define MAP_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "SOIL.h"

#include "Camera.h"

class Map {
public:
    Map();

    // Stockage des références aux textures
    GLuint ListeTextures[21];
    GLuint Skybox[6];
    GLuint ArmsTextures[6];

    void LoadTextures(void);

    void DrawGround(void);

    void DrawSkybox(Camera *cam);

protected:
private:
};

#endif // MAP_H
