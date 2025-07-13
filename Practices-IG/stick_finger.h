/**
 * file: stick_finger.h
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 01/2025
 */

#ifndef STICK_FINGER_H
#define STICK_FINGER_H

#include "object3d.h"

#include "stick_grabber.h"
#include "cube.h"
#include "sphere.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _stick_finger : public _object3D
{
private:
    _stick_grabber * grabber = nullptr;
public:
    _stick_finger();
    void draw(_cube & cube, _sphere & sphere);
};

#endif // STICK_FINGER_H
