/**
 * file: stick_handle.cpp
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 01/2025
 */

#include "stick_handle.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_stick_handle :: _stick_handle() {
    arm = new _stick_arm();
}

void _stick_handle :: draw(_cube & cube, _sphere & sphere, _cylinder & cylinder){
    glMatrixMode(GL_MODELVIEW);

    // cilindro manillar
    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);

    // RED MATERIAL (PLASTIC-RED)
    const _vertex4f AMBIENT_RED(0.0f,0.0f,0.0f,1.0f);
    const _vertex4f DIFFUSE_RED(0.5f,0.0f,0.0f,1.0f);
    const _vertex4f SPECULAR_RED(0.7f,0.6f,0.6f,1.0f);
    const float RED_SHININESS = 32.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *) & AMBIENT_RED);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *) & DIFFUSE_RED);
    glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) & SPECULAR_RED);
    glMaterialf(GL_FRONT, GL_SHININESS, RED_SHININESS);

    cylinder.draw_flat();

    glPopMatrix();

    // seccion del middle arm (donde se "guarda" el palo que se extiende)
    glPushMatrix();
    glScalef(0.25f, 8.0f, 0.25f);
    glTranslatef(0, -0.45f, 0);

    // SILVER MATERIAL
    const _vertex4f AMBIENT_SILVER(0.19225f, 0.19225f, 0.19225f, 1.0f);
    const _vertex4f DIFFUSE_SILVER(0.50754f, 0.50754f, 0.50754f, 1.0f);
    const _vertex4f SPECULAR_SILVER(0.508273f, 0.508273f, 0.508273f, 1.0f);
    const float SILVER_SHININESS = 51.2f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *) & AMBIENT_SILVER);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *) & DIFFUSE_SILVER);
    glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) & SPECULAR_SILVER);
    glMaterialf(GL_FRONT, GL_SHININESS, SILVER_SHININESS);

    cylinder.draw_gouraud();

    glPopMatrix();

    // dibujamos el brazo
    glPushMatrix();
    glTranslatef(0, armHeight, 0);
    glRotatef(armDegree, 0, 1, 0);
    arm->draw(cube, sphere, cylinder);
    glPopMatrix();
}

void _stick_handle :: moveStick(bool shouldClose){
    arm->moveStick(shouldClose);
}

void _stick_handle :: moveArm_vertical(bool moveUp){
    armHeight = std::min(std::max(armHeight + (moveUp ? incArmHeight : -incArmHeight), MIN_ARM_HEIGHT), MAX_ARM_HEIGHT);
}

void _stick_handle :: rotateArm(bool rotateClockwise){
    // modificamos el valor de armDegree
    armDegree += (rotateClockwise ? incDegree : -incDegree);
    // lo restringimos
    armDegree = std::max(std::min(static_cast<int>(armDegree), MAX_ARM_ROTATION), MIN_ARM_ROTATION);
}

void _stick_handle :: adjust_armHeight(bool increase) {
    // 0.1 < incArmHeight < 1.0
    if (increase) {
        incArmHeight = (incArmHeight < 1.0f) ? incArmHeight + 0.1f : 1.0f;
    } else {
        incArmHeight = (incArmHeight > 0.1f) ? incArmHeight - 0.1f : 0.1f;
    }
}

void _stick_handle :: adjust_armDegree(bool increase) {
    // 1 < incDegree < 5
    if (increase) {
        incDegree = (incDegree < 5) ? incDegree + 1 : 5;
    } else {
        incDegree = (incDegree > 1) ? incDegree - 1 : 1;
    }
}

void _stick_handle :: adjust_moveStick(bool increase){
    arm->adjust_moveStick(increase);
}

float _stick_handle :: getArmHeight(){
    return armHeight;
}

int _stick_handle :: getArmDegree(){
    return armDegree;
}

int _stick_handle :: getStickDegree(){
    return arm->getDegree();
}

void _stick_handle :: update(){
    {
        // Cerrar la mano si el brazo está en un ángulo entre 10 y 40 grados y no está en la altura mínima
        if (arm->getDegree() > 10 && arm->getDegree() < 40 && armHeight != MIN_ARM_HEIGHT)
        {
            arm->update_stickState(false);
        }

        // Mover el brazo hacia abajo si está en la posición superior
        if (armHeight > MIN_ARM_HEIGHT && arm->getDegree() == 40)
        {
            moveArm_vertical(false);
        }
        // Mover el brazo hacia arriba si está en la posición inferior
        else if (arm->getDegree() == 10 && armHeight < MAX_ARM_HEIGHT)
        {
            moveArm_vertical(true);
        }

        // Oscilar la rotación del brazo entre MIN_ARM_ROTATION y MAX_ARM_ROTATION
        if (armDegree < MAX_ARM_ROTATION && !isRotatingClockwise)
        {
            rotateArm(true); // Rotar en sentido horario
            if (armDegree == MAX_ARM_ROTATION)
                isRotatingClockwise = true; // Cambiar dirección al llegar al máximo
        }
        else if (armDegree > MIN_ARM_ROTATION && isRotatingClockwise)
        {
            rotateArm(false); // Rotar en sentido antihorario
            if (armDegree == MIN_ARM_ROTATION)
                isRotatingClockwise = false; // Cambiar dirección al llegar al mínimo
        }

        // Abrir la mano si el brazo está en la posición más alta
        if (armHeight == MAX_ARM_HEIGHT)
        {
            arm->update_stickState(false);
        }

        // Cerrar la mano si el brazo está en la posición más baja
        if (armHeight == MIN_ARM_HEIGHT)
        {
            arm->update_stickState(true);
        }
    }
}

