/**
 * file: stick_hand.h
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 01/2025
 */

#ifndef STICK_HAND_H
#define STICK_HAND_H

#include "object3d.h"

#include "stick_finger.h"
#include "cube.h"
#include "sphere.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _stick_hand : public _object3D
{
private:
    _stick_finger * finger = nullptr;

    const int MAX_OPENNESS = 40;
    const int MIN_OPENNESS = 10;

    int incDegree = 1;
    int degree = 40;

public:
    _stick_hand();
    void draw(_cube & cube, _sphere & sphere);
    void draw_pincer(_cube & cube, _sphere & sphere, GLfloat xPos, GLfloat yPos, GLfloat angle);

    void moveStick(bool shouldClose);
    void adjust_moveStick(bool increase);

    int getDegree();
    void update_stickState(bool shouldClose);
};

#endif // STICK_HAND_H
