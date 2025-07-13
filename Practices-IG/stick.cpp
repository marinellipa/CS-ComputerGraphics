/**
 * file: stick.cpp
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 01/2025
 */

#include "stick.h"
#include <cmath>
#include "QThread"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_stick :: _stick() {
    sphere = new _sphere();
    cube = new _cube();
    cylinder = new _cylinder();
    cone = new _cone();
    stick = new _stick_handle();
    arm = new _stick_arm();
}

void _stick :: draw(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, 5, 0);
    stick->draw(*cube, *sphere, *cylinder);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.6f, 1.6f, 1.6f);
    glRotatef(objectRotation, 0, 1, 0);
    glTranslatef(0, objectHeight, 0);
    sphere->draw_random();
    glPopMatrix();
}

void _stick :: moveStick(bool shouldClose){
    stick->moveStick(shouldClose);
}

void _stick :: moveArm_vertical(bool moveUp){
    stick->moveArm_vertical(moveUp);
}

void _stick :: rotateArm(bool rotateClockwise){
    stick->rotateArm(rotateClockwise);
}

void _stick :: adjust_move(bool increase){
    stick->adjust_armHeight(increase);
}

void _stick :: adjust_moveArmRot(bool increase){
    stick->adjust_armDegree(increase);
}

void _stick :: adjust_moveStick(bool increase){
    stick->adjust_moveStick(increase);
}

float _stick :: getHeight(){
    return objectHeight;
}

bool _stick :: isPicking(){
    return shouldPick;
}

void _stick :: updateBallPos(){
    float pickUpHeight = -3.9;

    if (stick->getArmHeight() == pickUpHeight){
        shouldPick = true;
    }

    if (shouldPick){
        float stickHeight = stick->getArmHeight();
        this->objectHeight = (stickHeight*0.59)-3.20;
        this->objectRotation = stick->getArmDegree();
    }

    // Verificar si la pelota está en la parte superior
    if (objectHeight >= -3.35){
        arm->update_stickState(true); // Abrir la mano al máximo
    }

    // Soltar la pelota cuando la mano esté completamente abierta
    if (arm->isHandFullOpen() and objectHeight >= -3.35){
        shouldPick = false;
        objectHeight = objectHeight-2.3;
    }
}

void _stick :: update(){
    stick->update();
}

void _stick :: normal_calculation(){
    sphere->normal_calculation();
    cube->normal_calculation();
    cylinder->normal_calculation();
    cone->normal_calculation();
}
