/**
 * file: stick_grabber.h
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 01/2025
 */

#ifndef STICK_GRABBER_H
#define STICK_GRABBER_H

#include "object3d.h"

#include "sphere.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _stick_grabber : public _object3D
{
public:
    _stick_grabber();
    void draw(_sphere & sphere);
};

#endif // STICK_GRABBER_H
