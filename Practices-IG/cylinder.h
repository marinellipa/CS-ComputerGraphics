/**
 * file: cylinder.h
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 10/2024
 */

#ifndef CYLINDER_H
#define CYLINDER_H

#include "build_revolution.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _cylinder : public _build_revolution
{
public:
    _cylinder(float Size=1.0, int n=32);
};

#endif // CYLINDER_H
