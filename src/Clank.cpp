//
// Created by Unknow on 07/04/2020.
//

#include "Clank.h"

Clank::Clank() {
    deltaForward = 0;
    deltaStrafe = 0;

    posx = 0.0f;
    posy = 1.5f;
    posz = 5.0f;

    dirx = 0.0f;
    diry = 0.0f;
    dirz = -1.0f;

    angleh = 0.0f;
    anglev = 0.0f;

    deltaAnglex = 0.0f;
    deltaAngley = 0.0f;

    locked = 1;

    arms = new Arms(1.f, posx, posy, posz, 0.f, 0.f, 0.f);
}

Clank::Clank(float scale, float posx, float posy, float posz, float rotx, float roty, float rotz) {
    deltaForward = 0;
    deltaStrafe = 0;

    this->posx = posx;
    this->posy = posy;
    this->posz = posz;

    dirx = 0.0f;
    diry = 0.0f;
    dirz = -1.0f;

    angleh = 0.0f;
    anglev = 0.0f;

    deltaAnglex = 0.0f;
    deltaAngley = 0.0f;

    arms = new Arms(1.f, this->posx, this->posy, this->posz, 0.f, 0.f, 0.f);
}

void Clank::updatePos() {

    if (deltaForward || deltaStrafe) {
        if (locked) {
            posx += deltaForward * (dirx / cos(anglev + deltaAngley)) * MOVE_SPEED;
            posy = 1.5f;
            posz += deltaForward * (dirz / cos(anglev + deltaAngley)) * MOVE_SPEED;
            posx += deltaStrafe * (dirz / cos(anglev + deltaAngley)) * MOVE_SPEED;
            posz -= deltaStrafe * (dirx / cos(anglev + deltaAngley)) * MOVE_SPEED;

        } else {
            posx += deltaForward * dirx * MOVE_SPEED;
            posy += deltaForward * diry * MOVE_SPEED;
            posz += deltaForward * dirz * MOVE_SPEED;
            posx += deltaStrafe * dirz * MOVE_SPEED;
            posz -= deltaStrafe * dirx * MOVE_SPEED;
        }
    }
    updateMembersPos();
}

void Clank::updateMembersPos() {
    arms->setPosx(posx);
    arms->setPosy(posy);
    arms->setPosz(posz);
}

void Clank::Draw() {
    arms->Draw();
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

char Clank::getLocked() const {
    return locked;
}

void Clank::setLocked(char locked) {
    Clank::locked = locked;
}
