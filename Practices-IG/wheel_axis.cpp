/**
 * file: objectPLY.cc
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 10/2024
 */

#include "wheel_axis.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_wheel_axis :: _wheel_axis() {}

void _wheel_axis :: draw() {
    glMatrixMode(GL_MODELVIEW);
    // axis
    glPushMatrix();
    glTranslatef(0,1.1,0);
    glRotatef(90,0,0,1);
    glScalef(0.1,2,0.1); //0.2,2,0.2
    cylinder.draw_fill();
    glPopMatrix();
    // first wheel
    glPushMatrix();
    glTranslatef(-1.1,1,0);
    wheel.draw();
    glPopMatrix();
    // second wheel: same process
    glPushMatrix();
    glTranslatef(1.1,1,0);
    wheel.draw();
    glPopMatrix();
}

/*
 * Como he rotado antes de escalar, los ejes x y z deben tener el mismo
 * valor para no deformar la figura
 *
 */
