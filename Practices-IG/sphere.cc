/**
 * file: sphere.cc
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 10/2024
 */

#include "sphere.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_sphere :: _sphere(float Size, int n) : _build_revolution(create_profile
                                            (_vertex3f(Size/2,0,0),n), n) { }


/*****************************************************************************/

vector<_vertex3f> _sphere :: create_profile(_vertex3f vertex, int n){
    // contenedores del perfil
    vector<_vertex3f> sph_profile;
    vector<_vertex3f> final_profile;

    // el primer vertice es el parametro
    sph_profile.push_back(vertex);

    // calculamos los demas puntos por revolucion
    _build_revolution circle(sph_profile, n);

    // cambiamos el tam
    final_profile.resize((circle.Vertices.size()/2)+1);

    // aniadimos los nuevos puntos al vector
    for (unsigned long i = 0; i <= circle.Vertices.size()/2+1; i++){
        final_profile[i] = _vertex3f(circle.Vertices[i].z,circle.Vertices[i].x, 0.0);
    }
    return final_profile;
}
