//
// Created by Unknow on 07/04/2020.
//

#include "Clank.h"

void Clank::LoadTextures() {
    ListeTextures[0] = SOIL_load_OGL_texture("img/concrete-21_s100-g100.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);
    ListeTextures[1] = SOIL_load_OGL_texture("img/concrete-19_b005.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);

    body->SetTexture(0, ListeTextures[0]);
    body->SetTexture(1, ListeTextures[1]);
}

Clank::Clank() {

    posx = 0.0f;
    posy = 1.5f;
    posz = 5.0f;
    scale = 1.f;

    ConstructDefault();

}

Clank::Clank(float scale, float posx, float posy, float posz, float rotx, float roty, float rotz) {

    this->posx = posx;
    this->posy = posy;
    this->posz = posz;
    this->scale = scale;
    ConstructDefault();
}

void Clank::ConstructDefault() {
    deltaForward = 0;
    deltaStrafe = 0;

    dirx = 0.0f;
    diry = 0.0f;
    dirz = 1.0f;

    anglev = 0.0f;

    deltaAngley = 0.0f;


    rightArm = new Arms(scale * 0.55f, posx, posy, posz, anglev + 90.f);
    leftArm = new Arms(scale * 0.55f, posx, posy, posz, anglev + 90.f);
    leftArm->InverseWalkingAnimationWay();
    body = new Body(scale, posx, posy, posz, anglev + 0.f);
}

void Clank::updatePos() {

    if (deltaForward) {
        posx += deltaForward * sin(anglev * M_PI / 180.f) * MOVE_SPEED;
        posz += deltaForward * cos(anglev * M_PI / 180.f) * MOVE_SPEED;
    }
    updateMembersPos();
    updateMemberAnimations();
}

void Clank::updateRotation() {
    if (deltaAngley != 0) {
        anglev += deltaAngley * ROTATION_SPEED;
    }
}

void Clank::updateMembersPos() {
    rightArm->setPosx(0.32f - 0.1f);
    rightArm->setPosy(0.3f);
    rightArm->setPosz(0.07f);

    leftArm->setPosx(-0.06f - 0.1f);
    leftArm->setPosy(0.3f);
    leftArm->setPosz(0.07f);

    body->setPosx(-0.1f);
    body->setPosy(0);
    body->setPosz(0);
}

void Clank::Draw() {
    glTranslatef(posx, posy, posz);
    glRotatef(anglev, 0.f, 1.f, 0.f);

    rightArm->Draw();
    leftArm->Draw();
    body->Draw();
}

void Clank::enableWalkingAnimation() {
    rightArm->setWalkingAnimationgActive();
    leftArm->setWalkingAnimationgActive();
}

void Clank::disableWalkingAnimation() {
    rightArm->setWalkingAnimationInactive();
    leftArm->setWalkingAnimationInactive();
}

void Clank::updateMemberAnimations() {
    rightArm->UpdateAnimations();
    leftArm->UpdateAnimations();
}

float Clank::getPosx() const {
    return posx;
}

void Clank::setPosx(float posx) {
    Clank::posx = posx;
}

float Clank::getPosy() const {
    return posy;
}

void Clank::setPosy(float posy) {
    Clank::posy = posy;
}

float Clank::getPosz() const {
    return posz;
}

void Clank::setPosz(float posz) {
    Clank::posz = posz;
}

float Clank::getDirx() const {
    return dirx;
}

void Clank::setDirx(float dirx) {
    Clank::dirx = dirx;
}

float Clank::getDiry() const {
    return diry;
}

void Clank::setDiry(float diry) {
    Clank::diry = diry;
}

float Clank::getDirz() const {
    return dirz;
}

void Clank::setDirz(float dirz) {
    Clank::dirz = dirz;
}

float Clank::getRotx() const {
    return rotx;
}

void Clank::setRotx(float rotx) {
    Clank::rotx = rotx;
}

float Clank::getRoty() const {
    return roty;
}

void Clank::setRoty(float roty) {
    Clank::roty = roty;
}

float Clank::getRotz() const {
    return rotz;
}

void Clank::setRotz(float rotz) {
    Clank::rotz = rotz;
}

float Clank::getDeltaAngley() const {
    return deltaAngley;
}

void Clank::setDeltaAngley(float deltaAngley) {
    Clank::deltaAngley = deltaAngley;
}

char Clank::getDeltaForward() const {
    return deltaForward;
}

void Clank::setDeltaForward(char deltaForward) {
    Clank::deltaForward = deltaForward;
}

char Clank::getDeltaStrafe() const {
    return deltaStrafe;
}

void Clank::setDeltaStrafe(char deltaStrafe) {
    Clank::deltaStrafe = deltaStrafe;
}
