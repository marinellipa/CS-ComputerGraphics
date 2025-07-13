/**
 * file: PLY_revolution.cpp
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 02/2025
 */

#include "PLY_revolution.h"
#include "file_ply_stl.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_ply_revolution :: _ply_revolution(int n) : _build_revolution(read_PLY_profile(), n) {

}

vector<_vertex3f> _ply_revolution :: read_PLY_profile(){
    const string route = "./cocktail_glass.ply";

    _file_ply ply;
    vector<float> flt_vertices;
    vector<unsigned int> flt_triangles;

    ply.open(route);
    ply.read(flt_vertices, flt_triangles);
    ply.close();

    vector<_vertex3f> vertices(flt_vertices.size() / 3);

    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i] = _vertex3f(flt_vertices[i * 3], flt_vertices[i * 3 + 1], flt_vertices[i * 3 + 2]);
    }

    return vertices;
}
