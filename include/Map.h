#ifndef MAP_H
#define MAP_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "SOIL.h"

#include "Camera.h"
class Map
{
    public:
        Map();
        // Stockage des r�f�rences aux textures
        GLuint ListeTextures[21];
        GLuint Skybox[6];
        void LoadTextures(void);
        void DrawGround(void);
        void DrawSkybox(Camera *cam);
    protected:
    private:
        GLuint textures[6];
};

#endif // MAP_H
