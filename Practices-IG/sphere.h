/**
 * file: sphere.h
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 10/2024
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "build_revolution.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _sphere : public _build_revolution
{
public:
    _sphere(float Size=1.0, int n=60);
private:
    vector<_vertex3f> create_profile(_vertex3f vertex, int n);
};

#endif // SPHERE_H
