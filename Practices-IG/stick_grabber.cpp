/**
 * file: stick_grabber.cpp
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 01/2025
 */

#include "stick_grabber.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_stick_grabber :: _stick_grabber() {}

void _stick_grabber :: draw(_sphere & sphere){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // escalamos para mantener proporciones
    glScalef(0.55f, 0.30f, 0.55f);

    // RED MATERIAL (PLASTIC-RED)
    const _vertex4f AMBIENT_RED(0.0f,0.0f,0.0f,1.0f);
    const _vertex4f DIFFUSE_RED(0.5f,0.0f,0.0f,1.0f);
    const _vertex4f SPECULAR_RED(0.7f,0.6f,0.6f,1.0f);
    const float RED_SHININESS = 32.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *) & AMBIENT_RED);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *) & DIFFUSE_RED);
    glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) & SPECULAR_RED);
    glMaterialf(GL_FRONT, GL_SHININESS, RED_SHININESS);

    sphere.draw_flat();
    glPopMatrix();
}
