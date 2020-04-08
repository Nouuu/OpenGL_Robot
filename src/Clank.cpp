//
// Created by Unknow on 07/04/2020.
//

#include "Clank.h"

void Clank::LoadTextures() {
    ListeTextures[0] = SOIL_load_OGL_texture("img/concrete-21_s100-g100.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    ListeTextures[1] = SOIL_load_OGL_texture("img/concrete-19_b005.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

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
    dirz = -1.0f;

    angleh = 0.0f;
    anglev = 0.0f;

    deltaAnglex = 0.0f;
    deltaAngley = 0.0f;


    arms = new Arms(scale, posx, posy, posz, 0.f, 0.f, 0.f);
    body = new Body(scale, posx, posy, posz, 0.f, 0.f, 0.f);
}

void Clank::updatePos() {

    if (deltaForward || deltaStrafe) {
        posx += deltaForward * (dirx / cos(anglev + deltaAngley)) * MOVE_SPEED;
        posz += deltaForward * (dirz / cos(anglev + deltaAngley)) * MOVE_SPEED;
        posx += deltaStrafe * (dirz / cos(anglev + deltaAngley)) * MOVE_SPEED;
        posz -= deltaStrafe * (dirx / cos(anglev + deltaAngley)) * MOVE_SPEED;
    }
    updateMembersPos();
    updateMemberAnimations();
}

void Clank::updateMembersPos() {
    arms->setPosx(posx);
    arms->setPosy(posy);
    arms->setPosz(posz);
    body->setPosx(posx);
    body->setPosy(posy);
    body->setPosz(posz);
}

void Clank::Draw() {
//    arms->Draw();
    body->Draw();
}

void Clank::enableWalkingAnimation() {
    arms->setWalkingAnimationgActive();
}

void Clank::disableWalkingAnimation() {
    arms->setWalkingAnimationInactive();
}

void Clank::updateMemberAnimations() {
    arms->UpdateAnimations();
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

float Clank::getAngleh() const {
    return angleh;
}

void Clank::setAngleh(float angleh) {
    Clank::angleh = angleh;
}

float Clank::getAnglev() const {
    return anglev;
}

void Clank::setAnglev(float anglev) {
    Clank::anglev = anglev;
}

float Clank::getDeltaAnglex() const {
    return deltaAnglex;
}

void Clank::setDeltaAnglex(float deltaAnglex) {
    Clank::deltaAnglex = deltaAnglex;
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
