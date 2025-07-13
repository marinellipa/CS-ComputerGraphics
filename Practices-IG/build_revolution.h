/**
 * file: build_revolution.h
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 10/2024
 */


#ifndef OBJECTREVOLUTION_H
#define OBJECTREVOLUTION_H

#include "object3d.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/


class _build_revolution : public _object3D
{
public:

    _build_revolution(vector<_vertex3f> profile, int n);

};

#endif // OBJECTREVOLUTION_H
