/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>

#include <GL/gl.h>
#include <QWindow>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include <iostream>
#include "vertex.h"
#include "axis.h"

#include "tetrahedron.h"
#include "cube.h"
#include "objectPLY.h"
#include "PLY_revolution.h"
#include "cone.h"
#include "cylinder.h"
#include "sphere.h"
#include "chess_board.h"

#include "stick.h"

namespace _gl_widget_ne {

  const float X_MIN=-.1;
  const float X_MAX=.1;
  const float Y_MIN=-.1;
  const float Y_MAX=.1;
  const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
  const float BACK_PLANE_PERSPECTIVE=1000;
  const float FRONT_PLANE_PARALLEL=-10000;
  const float BACK_PLANE_PARALLEL=10000;
  const float DEFAULT_DISTANCE=2;
  const float ANGLE_STEP=1;

  const float MOUSE_STEP=2;
  const float CAMERA_FACTOR=1.5;

  typedef enum {MODE_DRAW_POINT,MODE_DRAW_LINE,MODE_DRAW_FILL,MODE_DRAW_CHESS, MODE_DRAW_RANDOM, MODE_DRAW_FLAT, MODE_DRAW_GOURAUD, MODE_DRAW_TEX, MODE_DRAW_TEX_FLAT, MODE_DRAW_TEX_GOURAUD, MODE_DRAW_SELECTION} _mode_draw;
  typedef enum {OBJECT_TETRAHEDRON,OBJECT_CUBE,OBJECT_PLY,OBJECT_PLY_REV,OBJECT_CONE,OBJECT_CYLINDER,OBJECT_SPHERE, OBJECT_DASHBOARD, OBJECT_STICK, OBJECT_MULTIPLE_PLY} _object;
  typedef enum {PERSPECTIVE_PROJECTION, PARALLEL_PROJECTION} _projection;
}

class _window;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _gl_widget : public QOpenGLWidget
{
Q_OBJECT
public:
  _gl_widget(_window *Window1);

  void clear_window();
  void change_projection();
  void change_observer();

  void draw_axis();
  void draw_objects();

  void normal_calculation();

  void pick();

protected:
  void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *Keyevent) Q_DECL_OVERRIDE;

  void white_infinite_light();
  void magenta_non_infinite_light();
  void change_material();

  void light_animation();
  void updateMagentaLight();

  void load_texture(QString & file);

  void mousePressEvent(QMouseEvent *Mouseevent) override;
  void mouseMoveEvent(QMouseEvent *Mouseevent) override;
  void mouseReleaseEvent(QMouseEvent * Mouseevent) override;
  void wheelEvent(QWheelEvent *Wheelevent) override;

private slots:

  void stick_animation();

private:
  _window *Window;

  _axis Axis;

  _tetrahedron     Tetrahedron;
  _cube            Cube;
  _object_ply      ObjectPLY;
  _ply_revolution  ObjectPLYrev;
  _cone            Cone;
  _cylinder        Cylinder;
  _sphere          Sphere;
  _stick           Stick;
  _chess_board     Dashboard;

  QTimer * Timer;

  _gl_widget_ne::_object Object;
  _gl_widget_ne::_projection Projection;

  bool Draw_point;
  bool Draw_line;
  bool Draw_fill;
  bool Draw_chess;
  bool Draw_random;

  bool Draw_flat;
  bool Draw_gouraud;
  bool Draw_tex;
  bool Draw_tex_flat;
  bool Draw_tex_gouraud;

  bool Draw_selection;

  bool animation;

  bool light1, light2;

  int material_type;
  float timer_time;

  float light_rotation;

  QString * file;
  QImage * image;

  float Observer_angle_x;
  float Observer_angle_y;
  float Observer_distance;

  int window_width, window_height;
  int last_x, last_y;
  int current_selection_pos_x, current_selection_pos_y;

  void clear_variables(){
      Draw_point=false;
      Draw_line=false;
      Draw_fill=false;
      Draw_chess=false;
      Draw_random=false;
      Draw_flat = false;
      Draw_gouraud = false;
      Draw_tex = false;
      Draw_tex_flat = false;
      Draw_tex_gouraud = false;
      Draw_selection = false;
  }
};

#endif
