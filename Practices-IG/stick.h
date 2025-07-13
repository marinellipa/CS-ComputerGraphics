/**
 * file: stick.h
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 01/2025
 */

#ifndef STICK_H
#define STICK_H

#include "object3d.h"
//#include "QObject"
#include "QTimer"

#include "sphere.h"
#include "cube.h"
#include "cylinder.h"
#include "cone.h"

#include "stick_handle.h"
#include "stick_arm.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _stick : public _object3D
{
private:
    _sphere     * sphere   = nullptr;
    _cube       * cube     = nullptr;
    _cylinder   * cylinder = nullptr;
    _cone       * cone     = nullptr;

    _stick_handle * stick = nullptr;
    _stick_arm * arm = nullptr;

    bool shouldPick = false;
    float objectHeight = -5.5f;
    int objectRotation = 0;

public:
    _stick();
    void draw();

    void moveStick(bool shouldClose);
    void moveArm_vertical(bool moveUp);
    void rotateArm(bool rotateClockwise);

    void adjust_move(bool increase);
    void adjust_moveArmRot(bool increase);
    void adjust_moveStick(bool increase);

    float getHeight();
    bool isPicking();
    void updateBallPos();
    void update();

    void normal_calculation();
};

#endif // STICK_H
