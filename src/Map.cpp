#include "Map.h"
#include "Block.h"

#define GL_CLAMP_TO_EDGE 0x812F
#define SKY_DISTANCE 200.0f

Map::Map() {
    float randX;
    float randZ;
    for (int i = 0; i < 50; ++i) {
        randX = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 30)) - 15.f;
        randZ = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 30)) - 15.f;
        randomPos[i].posX = randX;
        randomPos[i].posZ = randZ;
    }
}

void Map::LoadTextures() {
    // Skybox
    Skybox[0] = SOIL_load_OGL_texture("img/bkg/lightblue/left.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
                                      SOIL_FLAG_COMPRESS_TO_DXT);
    Skybox[1] = SOIL_load_OGL_texture("img/bkg/lightblue/front.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
                                      SOIL_FLAG_COMPRESS_TO_DXT);
    Skybox[2] = SOIL_load_OGL_texture("img/bkg/lightblue/top.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
                                      SOIL_FLAG_COMPRESS_TO_DXT);
    Skybox[3] = SOIL_load_OGL_texture("img/bkg/lightblue/back.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
                                      SOIL_FLAG_COMPRESS_TO_DXT);
    Skybox[4] = SOIL_load_OGL_texture("img/bkg/lightblue/right.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
                                      SOIL_FLAG_COMPRESS_TO_DXT);
    Skybox[5] = SOIL_load_OGL_texture("img/bkg/lightblue/bot.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
                                      SOIL_FLAG_COMPRESS_TO_DXT);
    // Textures utilisables
    ListeTextures[0] = SOIL_load_OGL_texture("img/cliff.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    ListeTextures[1] = SOIL_load_OGL_texture("img/cobble.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    ListeTextures[2] = SOIL_load_OGL_texture("img/darkgrass.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);
    ListeTextures[3] = SOIL_load_OGL_texture("img/darkwoodplanks.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);
    ListeTextures[4] = SOIL_load_OGL_texture("img/darkwoodtiles.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);
    ListeTextures[5] = SOIL_load_OGL_texture("img/deadgrass.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);
    ListeTextures[6] = SOIL_load_OGL_texture("img/floorbrick.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);
    ListeTextures[7] = SOIL_load_OGL_texture("img/graybrick.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);
    ListeTextures[8] = SOIL_load_OGL_texture("img/graybricktiles.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);
    ListeTextures[9] = SOIL_load_OGL_texture("img/greybrick.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);
    ListeTextures[10] = SOIL_load_OGL_texture("img/greybricktiles.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                              SOIL_FLAG_INVERT_Y);
    ListeTextures[11] = SOIL_load_OGL_texture("img/lightgrass.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                              SOIL_FLAG_INVERT_Y);
    ListeTextures[12] = SOIL_load_OGL_texture("img/lightwoodplanks.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                              SOIL_FLAG_INVERT_Y);
    ListeTextures[13] = SOIL_load_OGL_texture("img/lightwoodtiles.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                              SOIL_FLAG_INVERT_Y);
    ListeTextures[14] = SOIL_load_OGL_texture("img/mossbricktiles.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                              SOIL_FLAG_INVERT_Y);
    ListeTextures[15] = SOIL_load_OGL_texture("img/pavement.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                              SOIL_FLAG_INVERT_Y);
    ListeTextures[16] = SOIL_load_OGL_texture("img/pebbles.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                              SOIL_FLAG_INVERT_Y);
    ListeTextures[17] = SOIL_load_OGL_texture("img/redbrick.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                              SOIL_FLAG_INVERT_Y);
    ListeTextures[18] = SOIL_load_OGL_texture("img/metalgate.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                              SOIL_FLAG_INVERT_Y);
    //ListeTextures[19] = SOIL_load_OGL_texture("img/betonurban.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[19] = SOIL_load_OGL_texture("img/terre.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    //ListeTextures[20] = Sol
    ListeTextures[20] = SOIL_load_OGL_texture("img/tiles.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                              SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
                                              SOIL_FLAG_COMPRESS_TO_DXT);
}

void Map::DrawGround() {
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, ListeTextures[20]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-15.0f, 0.0f, -15.0f);
    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(-15.0f, 0.0f, 15.0f);
    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(15.0f, 0.0f, 15.0f);
    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(15.0f, 0.0f, -15.0f);
    glEnd();
    glTranslatef(0.0f, 1.0f, 0.0f);

    DrawBox();
    DrawBolt();
}

void Map::DrawBox() {
    char metal[6] = "metal";
    char wood[5] = "wood";

    Box *boxMetal = new Box(0.7f, 0.f, 0.f, 0.f, 0.f, metal);
    Box *boxWood = new Box(0.7f, 0.f, 0.f, 0.f, 0.f, wood);

    DrawBoxPack1(5.f, 0.f, 30.f, boxMetal);
    DrawBoxPack1(-5.f, 0.f, 90.f, boxWood);
    DrawBoxPack1(0.f, 10.f, -20.f, boxWood);
    DrawBoxPack1(10.f, -10.f, 0.f, boxMetal);

    DrawBoxPack2(2.f, 2.f, 45.f, boxMetal);
    DrawBoxPack2(10.f, 10.f, 90.f, boxWood);
    DrawBoxPack2(-12.f, 2.f, 0.f, boxMetal);
    DrawBoxPack2(2.f, 10.f, -60.f, boxWood);
    DrawBoxPack2(0.f, -10.f, 45.f, boxMetal);
}

void Map::DrawBoxPack1(float x, float z, float rot, Box *box1) {
    glPushMatrix();
    glTranslatef(x, 0.f, z);
    glRotatef(rot, 0., 1.f, 0.f);

//    Box *box1 = new Box(0.7f, 0.f, -1.f, 0.f, 0.f, tex);
    box1->posx = 0.f;
    box1->posy = -1.f;
    box1->posz = 0.f;

    box1->Draw();

    box1->posz = 0.f;
    box1->posx = 1.f;
    box1->Draw();

    box1->posx = 0.4f;
    box1->posy = -0.3f;
    box1->Draw();

    glPopMatrix();
}

void Map::DrawBoxPack2(float x, float z, float rot, Box *box1) {
    glPushMatrix();
    glTranslatef(x, 0.f, z);
    glRotatef(rot, 0., 1.f, 0.f);

    box1->posx = 0.f;
    box1->posy = -1.f;
    box1->posz = 0.f;

    box1->Draw();
//    Box *box2 = new Box(0.7f, 1.1f, -1.f, 0.2f, 0.f, tex);

    box1->posx = 1.1f;
    box1->posz = 0.2f;
    box1->Draw();
//    Box *box5 = new Box(0.7f, 0.6f, -0.3f, 0.2f, 0.f, tex);

    box1->posx = 0.6f;
    box1->posy = -0.3f;
    box1->posz = 0.2f;
    box1->Draw();


//    Box *box3 = new Box(0.7f, 0.f, -1.f, 1.f, 0.f, tex);
    box1->posx = 0.f;
    box1->posy = -1.f;
    box1->posz = 1.f;
    box1->Draw();

//    Box *box4 = new Box(0.7f, 1.f, -1.f, 1.3f, 0.f, tex);
    box1->posx = 1.f;
    box1->posy = -1.f;
    box1->posz = 1.3f;
    box1->Draw();
//    Box *box6 = new Box(0.7f, 0.6f, -0.3f, 1.2f, 0.f, tex);

    box1->posx = 0.6f;
    box1->posy = -0.3f;
    box1->posz = 1.2f;
    box1->Draw();

//    Box *box7 = new Box(0.7f, 0.6f, 0.4f, 0.7f, 0.f, tex);
    box1->posx = 0.6f;
    box1->posy = 0.4f;
    box1->posz = 0.7f;

    box1->Draw();


    glPopMatrix();
}

void Map::DrawBolt() {
    Bolt *bolt = new Bolt(0.3f, 0.f, -0.7f, 0.f, -85.f, 0.f, 0.f);
    for (int i = 0; i < 50; ++i) {
        bolt->posx = randomPos[i].posX;
        bolt->posz = randomPos[i].posZ;
        bolt->Draw();
    }
}

void Map::DrawSkybox(Camera *cam) {
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    // Face
    glBindTexture(GL_TEXTURE_2D, Skybox[1]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 0);
    glVertex3f(-SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 1);
    glVertex3f(-SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(0, 1);
    glVertex3f(SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glEnd();

    // Render the left quad
    glBindTexture(GL_TEXTURE_2D, Skybox[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 0);
    glVertex3f(SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 1);
    glVertex3f(SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(0, 1);
    glVertex3f(SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glEnd();

    // Render the back quad
    glBindTexture(GL_TEXTURE_2D, Skybox[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 0);
    glVertex3f(SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 1);
    glVertex3f(SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(0, 1);
    glVertex3f(-SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);

    glEnd();

    // Render the right quad
    glBindTexture(GL_TEXTURE_2D, Skybox[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 0);
    glVertex3f(-SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 1);
    glVertex3f(-SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(0, 1);
    glVertex3f(-SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glEnd();

    // Render the top quad
    glBindTexture(GL_TEXTURE_2D, Skybox[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(-SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(0, 0);
    glVertex3f(-SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 0);
    glVertex3f(SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 1);
    glVertex3f(SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glEnd();

    // Render the bottom quad

    glBindTexture(GL_TEXTURE_2D, Skybox[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(-SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(0, 0);
    glVertex3f(-SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 0);
    glVertex3f(SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 1);
    glVertex3f(SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glEnd();
}