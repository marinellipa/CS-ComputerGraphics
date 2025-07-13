/**
 * file: build_revolution.cc
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 10/2024
 */

#include "build_revolution.h"
#include <cmath>

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/


_build_revolution :: _build_revolution(vector<_vertex3f> profile, int n)
{
    unsigned int ver_new_size = profile.size() * n;
    Vertices.resize(ver_new_size);

    float g_jump = 360.0/n;
    float r_jump = (g_jump * M_PI) / 180.0;

    int current_vertex = 0;

    for (unsigned int i=0; i < profile.size(); i++){
        for (int j=0; j < n; j++){
            float jump = r_jump * j;
            Vertices[current_vertex].x = profile[i].x * cos(jump);
            Vertices[current_vertex].y = profile[i].y;
            Vertices[current_vertex].z = -profile[i].x * sin(jump);
            current_vertex++;
        }
    }

    // el tam del vector sera: numero de divisiones 'n' * numero de vertices
    // del perfil 'profile.size()' * 2 (el numero de triangulos de cada cara)
    unsigned int tri_new_size = n * profile.size() * 2;
    Triangles.resize(tri_new_size);

    int current_triangle = 0;

    for (unsigned int i = 0; i < profile.size() - 1; i++) {
        for (int j = 0; j < n; j++) {
            int current = j + i * n;
            int next = (j + 1) % n + i * n;
            int next_row = j + (i + 1) * n;
            int next_row_next = (j + 1) % n + (i + 1) * n;

            // Triángulo superior
            Triangles[current_triangle++] = _vertex3ui(current, next, next_row_next);
            // Triángulo inferior
            Triangles[current_triangle++] = _vertex3ui(current, next_row_next, next_row);
        }
    }
}

/*
 * current: vertice actual en el anillo i, multiplicamos el numero de anillo por n (el
 * numero de vertices por anillo) y sumando el indice del vertice dentro de ese anillo
 *
 * next: siguiente vertice en el mismo anillo, j+1 es el siguiente vertice, el modulo
 * es para la conexion ciclica (el ultimo vertice de un anillo se conecta con el primero)
 *
 * next_row: siguiente vertice en el siguiente anillo con i+1, mantenemos el mismo vertice
 * pero en el siguiente anillo
 *
 * next_row_next: siguiente vertice en el siguiente anillo, i+1 para ir al siguiente
 * anillo y j+1%n oara ir al siguiente vertice
 */

