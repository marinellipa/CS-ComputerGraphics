/**
 * file: cone.cc
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 10/2024
 */

#include "cone.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cone :: _cone(float Size, int n) : _build_revolution (vector<_vertex3f>{
        _vertex3f(0, Size/2, 0),
        _vertex3f(Size/2, -Size/2, 0),
        _vertex3f(0, -Size/2, 0)
    }, n) { }
