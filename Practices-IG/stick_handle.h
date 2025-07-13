/**
 * file: stick_handle.h
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 01/2025
 */

#ifndef STICK_HANDLE_H
#define STICK_HANDLE_H

#include "object3d.h"

#include "stick_arm.h"
#include "cube.h"
#include "sphere.h"
#include "cylinder.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _stick_handle : public _object3D
{
private:
    _stick_arm * arm = nullptr;

    const int MAX_ARM_ROTATION = 180;
    const int MIN_ARM_ROTATION = -180;

    const float MAX_ARM_HEIGHT = -0.1;
    const float MIN_ARM_HEIGHT = -4;

    float incArmHeight = 0.1;
    float incDegree = 1;

    float armHeight = 0;
    float armDegree = 0;

    bool isRotatingClockwise = false;
    bool isMovingUp = false;
public:
    _stick_handle();
    void draw(_cube & cube, _sphere & sphere, _cylinder & cylinder);

    void moveStick(bool shouldClose);

    void moveArm_vertical(bool moveUp);
    void rotateArm(bool rotateClockwise);
    void adjust_armHeight(bool increase);
    void adjust_armDegree(bool increase);
    void adjust_moveStick(bool increase);

    float getArmHeight();
    int getArmDegree();
    int getStickDegree();

    void update();
};

#endif // STICK_HANDLE_H
