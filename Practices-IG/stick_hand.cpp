/**
 * file: stick_hand.cpp
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 01/2025
 */

#include "stick_hand.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_stick_hand :: _stick_hand() {
    finger = new _stick_finger();
}

void _stick_hand :: draw(_cube & cube, _sphere & sphere){
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glScalef(2, 0.25f, 0.25f);

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

    draw_pincer(cube, sphere, -0.79f, -0.61f, -degree);
    draw_pincer(cube, sphere, 0.79f, -0.61f, degree);

}

void _stick_hand :: draw_pincer(_cube & cube, _sphere & sphere, GLfloat xPos, GLfloat yPos, GLfloat angle){
    glPushMatrix();

    glTranslatef(xPos, yPos, 0);        // posicionamos dedo
    glTranslatef(-0.125f, 0.75f, 0);    // movemos al punto pivote
    glRotatef(angle, 0, 0, 1);          // rotamos
    glTranslatef(0.125f, -0.75f, 0);    // volvemos a la pos og

    finger->draw(cube, sphere);
    glPopMatrix();
}

void _stick_hand :: moveStick(bool shouldClose)
{
    if (shouldClose){
        degree = std::max(degree - incDegree, MIN_OPENNESS);
    } else {
        degree = std::min(degree + incDegree, MAX_OPENNESS);
    }
}

void _stick_hand :: adjust_moveStick(bool increase){
    // aseguramos que 1 < incDegree < 5
    incDegree = std::min(std::max(incDegree + (increase ? 1 : -1), 1), 5);
}

int _stick_hand :: getDegree(){
    return degree;
}

void _stick_hand :: update_stickState(bool shouldClose){
    moveStick(shouldClose);
}
