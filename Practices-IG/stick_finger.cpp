/**
 * file: stick_finger.cpp
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 01/2025
 */

#include "stick_finger.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_stick_finger :: _stick_finger() {
    grabber = new _stick_grabber();
}

void _stick_finger :: draw(_cube & cube, _sphere & sphere){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // escalamos y dibujamos el cubo
    glScalef(0.25f, 1.25f, 0.25f);

    // SILVER MATERIAL
    const _vertex4f AMBIENT_SILVER(0.19225f, 0.19225f, 0.19225f, 1.0f);
    const _vertex4f DIFFUSE_SILVER(0.50754f, 0.50754f, 0.50754f, 1.0f);
    const _vertex4f SPECULAR_SILVER(0.508273f, 0.508273f, 0.508273f, 1.0f);
    const float SILVER_SHININESS = 51.2f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *) & AMBIENT_SILVER);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *) & DIFFUSE_SILVER);
    glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) & SPECULAR_SILVER);
    glMaterialf(GL_FRONT, GL_SHININESS, SILVER_SHININESS);

    cube.draw_gouraud();

    glPopMatrix();
    glPushMatrix();

    // posicionamos y dibujamos la uña
    glTranslatef(0, -0.65f, 0);
    grabber->draw(sphere);

    glPopMatrix();

}
