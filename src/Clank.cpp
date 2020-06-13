//
// Created by Unknow on 07/04/2020.
//

#include "Clank.h"

void Clank::LoadTextures() {
    ListeTextures[0] = SOIL_load_OGL_texture("img/black_metal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);
    ListeTextures[1] = SOIL_load_OGL_texture("img/grey_metal.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);
    ListeTextures[2] = SOIL_load_OGL_texture("img/black.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);

    body->SetTexture(0, ListeTextures[0]);
    body->SetTexture(1, ListeTextures[1]);
    head->SetTexture(0, ListeTextures[0]);
    head->SetTexture(1, ListeTextures[1]);
    head->SetTexture(2, ListeTextures[2]);
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
    body = new Body(scale * 2.f, posx, posy, posz, anglev + 0.f);
    head = new Head(0.04f * scale, posx, posy, posz, anglev + 90.f);

    leftLeg = new Legs(scale * 0.7f, posx, posy, posz, anglev + 180.f);
    leftLeg->InverseWalkingAnimationWay();
    rightLeg = new Legs(scale * 0.7f, posx, posy, posz, anglev + 180.f);
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
    rightArm->setPosx((0.32f - 0.1f) * scale * 2);
    rightArm->setPosy(posy + 0.3f * scale * 2);
    rightArm->setPosz(0.07f * scale * 2);

    leftArm->setPosx((-0.06f - 0.1f) * scale * 2);
    leftArm->setPosy(posy + 0.3f * scale * 2);
    leftArm->setPosz(0.07f * scale * 2);

    body->setPosx(-0.1f * scale * 2);
    body->setPosy(posy + 0.f * scale * 2);
    body->setPosz(0.f * scale * 2);

    head->setPosx(0.05f * scale * 2);
    head->setPosy(posy + 0.47f * scale * 2);
    head->setPosz(-0.07f * scale * 2);

    leftLeg->setPosx(-0.05f * scale * 2);
    leftLeg->setPosy(posy - 0.37f * scale * 2);
    leftLeg->setPosz(0.05f * scale * 2);

    rightLeg->setPosx(0.15f * scale * 2);
    rightLeg->setPosy(posy - 0.37f * scale * 2);
    rightLeg->setPosz(0.07f * scale * 2);
}

void Clank::Draw() {
    glTranslatef(posx, posy, posz);
    glRotatef(anglev, 0.f, 1.f, 0.f);

    rightArm->Draw();
    leftArm->Draw();
    body->Draw();
    head->Draw();
    leftLeg->Draw();
    rightLeg->Draw();
}

void Clank::enableWalkingAnimation() {
    rightArm->setWalkingAnimationgActive();
    leftArm->setWalkingAnimationgActive();
    leftLeg->setWalkingAnimationActive();
    rightLeg->setWalkingAnimationActive();
    head->setWalkingAnimationActive();
}

void Clank::disableWalkingAnimation() {
    rightArm->setWalkingAnimationInactive();
    leftArm->setWalkingAnimationInactive();
    leftLeg->setWalkingAnimationInactive();
    rightLeg->setWalkingAnimationInactive();
    head->setWalkingAnimationInactive();
}

void Clank::updateMemberAnimations() {
    rightArm->UpdateAnimations();
    leftArm->UpdateAnimations();
    head->updateAnimation();
    leftLeg->UpdateAnimation();
    rightLeg->UpdateAnimation();
}

void Clank::setHeadRotationDelta(char delta) {
    head->setDeltaRotation(delta);
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
