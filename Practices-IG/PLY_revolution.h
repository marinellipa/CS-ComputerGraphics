/**
 * file: PLY_revolution.h
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 10/2024
 */

#ifndef PLY_REVOLUTION_H
#define PLY_REVOLUTION_H

#include "build_revolution.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _ply_revolution : public _build_revolution
{
public:
    _ply_revolution(int n=32);
private:
    vector<_vertex3f> read_PLY_profile();
};

#endif // PLY_REVOLUTION_H
