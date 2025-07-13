/**
 * file: stick_arm.cpp
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 01/2025
 */

#include "stick_arm.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_stick_arm :: _stick_arm() {
    hand = new _stick_hand();
}

void _stick_arm :: draw(_cube & cube, _sphere & sphere, _cylinder & cylinder){
    glMatrixMode(GL_MODELVIEW);

    // dibujamos brazo
    glPushMatrix();
    glScalef(0.25f, 6, 0.25f);
    glTranslatef(0, -1, 0);

    // SILVER MATERIAL
    const _vertex4f AMBIENT_SILVER(0.19225f, 0.19225f, 0.19225f, 1.0f);
    const _vertex4f DIFFUSE_SILVER(0.50754f, 0.50754f, 0.50754f, 1.0f);
    const _vertex4f SPECULAR_SILVER(0.508273f, 0.508273f, 0.508273f, 1.0f);
    const float SILVER_SHININESS = 51.2f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *) & AMBIENT_SILVER);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *) & DIFFUSE_SILVER);
    glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) & SPECULAR_SILVER);
    glMaterialf(GL_FRONT, GL_SHININESS, SILVER_SHININESS);

    cylinder.draw_flat();

    glPopMatrix();

    // dibujamos primera mano
    glPushMatrix();
    glTranslatef(0, -9, 0);
    hand->draw(cube, sphere);
    glPopMatrix();

    // dibujamos segunda mano rotada 90 grados
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, -9, 0);
    hand->draw(cube, sphere);
    glPopMatrix();
}

void _stick_arm :: moveStick(bool shouldClose){
    hand->moveStick(shouldClose);
}

void _stick_arm :: adjust_moveStick(bool increase){
    hand->adjust_moveStick(increase);
}

int _stick_arm :: getDegree(){
    return hand->getDegree();
}

void _stick_arm :: update_stickState(bool shouldClose){
    hand->update_stickState(shouldClose);
}

bool _stick_arm :: isHandFullOpen(){
    // max openness
    return (hand->getDegree() == 22 or hand->getDegree() == 10);
}
