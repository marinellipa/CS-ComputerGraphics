/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "basic_object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _object3D:public _basic_object3D
{
  public:

  vector<_vertex3ui> Triangles;
  vector<_vertex2f> Texture;

  vector<_vertex3f> TrianglesNormal;
  vector<_vertex3f> VerticesNormal;

  int selected_triangle = -1;
  bool is_triangle_selected = false;

  void draw_line();
  void draw_fill();
  void draw_chess();
  void draw_random();

  void draw_flat();
  void draw_gouraud();

  void draw_texture();
  void draw_texture_flat();
  void draw_texture_gouraud();

  void normal_calculation();

  void draw_selection();
  void update_selected_triangle(int triangle_ID);

};

#endif // OBJECT3D_H
