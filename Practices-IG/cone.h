/**
 * file: cone.h
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 10/2024
 */

#ifndef CONE_H
#define CONE_H

#include "build_revolution.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _cone : public _build_revolution
{
public:
    _cone(float Size=1.0, int n=15);
};

#endif // CONE_H
