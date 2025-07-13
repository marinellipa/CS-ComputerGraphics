/**
 * file: objectPLY.cc
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 10/2024
 */

#include "objectPLY.h"
#include "file_ply_stl.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/


_object_ply :: _object_ply() {

    const string route = "./cow.ply";

    _file_ply ply;
    vector<float> flt_vertices;
    vector<unsigned int> flt_triangles;

    ply.open(route);
    ply.read(flt_vertices, flt_triangles);
    ply.close();

    Vertices.resize(flt_vertices.size()/3);

    for (size_t i = 0; i < Vertices.size(); i++){
        Vertices[i] = _vertex3f(flt_vertices[i*3], flt_vertices[i*3+1], flt_vertices[i*3+2]);
    }

    Triangles.resize(flt_triangles.size()/3);

    for (size_t i = 0; i < Triangles.size(); i++){
        Triangles[i] = _vertex3ui(flt_triangles[i*3], flt_triangles[i*3+1], flt_triangles[i*3+2]);
    }
}

