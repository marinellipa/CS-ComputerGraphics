/**
 * file: cube.cc
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 09/2024
 */

#include "cube.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cube :: _cube(float Size)
{
    Vertices.resize(8);

    // cara delantera
    Vertices[0]=_vertex3f(-Size/2, -Size/2, Size/2);
    Vertices[1]=_vertex3f( Size/2, -Size/2, Size/2);
    Vertices[2]=_vertex3f(-Size/2, Size/2,  Size/2);
    Vertices[3]=_vertex3f( Size/2, Size/2,  Size/2);
    // cara trasera
    Vertices[4]=_vertex3f(-Size/2, -Size/2, -Size/2);
    Vertices[5]=_vertex3f (Size/2, -Size/2, -Size/2);
    Vertices[6]=_vertex3f(-Size/2,  Size/2, -Size/2);
    Vertices[7]=_vertex3f( Size/2,  Size/2, -Size/2);

    Triangles.resize(12);

    // carla delantera
    Triangles[0]=_vertex3ui(2,0,1);
    Triangles[1]=_vertex3ui(1,3,2);

    // cara derecha
    Triangles[2]=_vertex3ui(3,1,5);
    Triangles[3]=_vertex3ui(5,7,3);

    // cara trasera
    Triangles[4]=_vertex3ui(7,5,4);
    Triangles[5]=_vertex3ui(4,6,7);

    // cara izquierda
    Triangles[6]=_vertex3ui(6,4,0);
    Triangles[7]=_vertex3ui(0,2,6);

    // cara inferior
    Triangles[8]=_vertex3ui(0,4,5);
    Triangles[9]=_vertex3ui(5,1,0);

    // cara superior
    Triangles[10]=_vertex3ui(6,2,3);
    Triangles[11]=_vertex3ui(3,7,6);

    Texture.resize(Triangles.size()*3);

    // max dimensions
    float max_x = Vertices[Vertices.size()-1].x * 2;
    float max_y = Vertices[Vertices.size()-1].y * 2;

    // generate texture coordinates
    for (unsigned int i = 0; i < Triangles.size(); i++){
        Texture[i*3] = _vertex2f(0.5+Vertices[Triangles[i]._0].x / max_x, 0.5+Vertices[Triangles[i]._0].y / max_y);
        Texture[i*3+1] = _vertex2f(0.5+Vertices[Triangles[i]._1].x / max_x, 0.5+Vertices[Triangles[i]._1].y / max_y);
        Texture[i*3+2] = _vertex2f(0.5+Vertices[Triangles[i]._2].x / max_x, 0.5+Vertices[Triangles[i]._2].y / max_y);
    }
}
