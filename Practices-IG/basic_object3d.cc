/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2023
 * GPL 3
 */


#include "basic_object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _basic_object3D::draw_point()
{
  glBegin(GL_POINTS);
  for (unsigned int i = 0; i < Vertices.size(); i++){
    // con la v se manda el vector, y no las 3 coordenadas
    glVertex3fv( (GLfloat *) & Vertices[i] );
  }
  glEnd();
}
