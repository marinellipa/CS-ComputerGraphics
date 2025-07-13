/**
 * file: stick_arm.h
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 01/2025
 */

#ifndef STICK_ARM_H
#define STICK_ARM_H

#include "object3d.h"

#include "stick_hand.h"
#include "cube.h"
#include "sphere.h"
#include "cylinder.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _stick_arm : public _object3D
{
private:
    _stick_hand * hand = nullptr;
public:
    _stick_arm();
    void draw(_cube & cube, _sphere & sphere, _cylinder & cylinder);

    void moveStick(bool shouldClose);
    void adjust_moveStick(bool increase);

    int getDegree();
    void update_stickState(bool shouldClose);

    bool isHandFullOpen();
};

#endif // STICK_ARM_H
