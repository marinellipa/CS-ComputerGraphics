/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2023
 * GPL 3
 */


#include "glwidget.h"
#include "window.h"
#include "texture_manager.h"
#include <QImageReader>

using namespace std;
using namespace _gl_widget_ne;
using namespace _colors_ne;

GLfloat LIGHT_POS[] = {2.0f, 7.0f, 5.0f, 1.0f};
GLfloat LIGHT2_POS[] = {2.0f, 7.0f, 5.0f, 1.0f};
GLfloat INFINITE_LIGHT_POS[] = {-5.0f, -1.0f, 5.0f, 0.0f};
GLfloat INFINITE_LIGHT2_POS[] = {0.0f, 0.0f, 5.0f, 0.0f};

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_gl_widget::_gl_widget(_window *Window1):Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);
}


/*****************************************************************************//**
 * Evento tecla pulsada
 *
 *
 *
 *****************************************************************************/

void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{
  switch(Keyevent->key()){
  case Qt::Key_1:Object=OBJECT_TETRAHEDRON;break;
  case Qt::Key_2:Object=OBJECT_CUBE;break;
  case Qt::Key_3:Object=OBJECT_CONE;break;
  case Qt::Key_4:Object=OBJECT_CYLINDER;break;
  case Qt::Key_5:Object=OBJECT_SPHERE;break;
  case Qt::Key_6:Object=OBJECT_PLY;break;
  case Qt::Key_7:Object=OBJECT_STICK;break;
  case Qt::Key_8:Object=OBJECT_DASHBOARD;break;
  case Qt::Key_9:Object=OBJECT_PLY_REV;break;
  case Qt::Key_0:Object=OBJECT_MULTIPLE_PLY;break;

  case Qt::Key_A:animation=!animation;
      (animation) ? Timer->start() : Timer->stop();break;

  case Qt::Key_Q:Stick.moveStick(false);Stick.updateBallPos();break;
  case Qt::Key_W:Stick.moveStick(true);Stick.updateBallPos();break;

  case Qt::Key_S:Stick.moveArm_vertical(true);Stick.updateBallPos();break;
  case Qt::Key_D:Stick.moveArm_vertical(false);Stick.updateBallPos();break;

  case Qt::Key_Z:Stick.rotateArm(false);Stick.updateBallPos();break;
  case Qt::Key_X:Stick.rotateArm(true);Stick.updateBallPos();break;

  case Qt::Key_E:Stick.adjust_moveStick(false);break;
  case Qt::Key_R:Stick.adjust_moveStick(true);break;

  case Qt::Key_T:Stick.adjust_move(false);break;
  case Qt::Key_Y:Stick.adjust_move(true);break;

  case Qt::Key_U:Stick.adjust_moveArmRot(false);break;
  case Qt::Key_I:Stick.adjust_moveArmRot(true);break;

  case Qt::Key_P:Draw_point=!Draw_point;break;
  case Qt::Key_L:Draw_line=!Draw_line;break;
  case Qt::Key_F1:Draw_fill=!Draw_fill;break;
  case Qt::Key_F2:Draw_chess=!Draw_chess;break;
  case Qt::Key_F3:Draw_flat=!Draw_flat;break;
  case Qt::Key_F4:Draw_gouraud=!Draw_gouraud;break;
  case Qt::Key_F5:Draw_tex=!Draw_tex;break;
  case Qt::Key_F6:Draw_tex_flat=!Draw_tex_flat;break;
  case Qt::Key_F7:Draw_tex_gouraud=!Draw_tex_gouraud;break;
  case Qt::Key_F12:Draw_random=!Draw_random;break;

  case Qt::Key_J:light1=!light1;break;
  case Qt::Key_K:light2=!light2;break;
  case Qt::Key_M:material_type=(material_type+1)%3;break;

  case Qt::Key_C:Projection=_gl_widget_ne::PERSPECTIVE_PROJECTION;break;
  case Qt::Key_V:Projection=_gl_widget_ne::PARALLEL_PROJECTION;break;

  case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
  case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
  case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
  case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
  case Qt::Key_PageUp:Observer_distance*=1.2;break;
  case Qt::Key_PageDown:Observer_distance/=1.2;break;
  }

  update();
}


/*****************************************************************************//**
 * Limpiar ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}



/*****************************************************************************//**
 * Funcion para definir la transformación de proyeccion
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  // Front_plane>0  Back_plane>PlanoDelantero)

  switch (Projection) {
  case _gl_widget_ne::PERSPECTIVE_PROJECTION:
      // glFrustum defines a perspective projection matrix with specified near
      // and far planes, and left/right/top/bottom view frustum
      glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
      break;
  case _gl_widget_ne::PARALLEL_PROJECTION:
      int mult=Observer_distance*10.0;
      // glOrtho defines a parallel projection matrix, scaling the view box
      // based on Observer distance
      glOrtho(X_MIN*mult,X_MAX*mult,Y_MIN*mult,Y_MAX*mult,FRONT_PLANE_PARALLEL,BACK_PLANE_PARALLEL);
  }
}



/*****************************************************************************//**
 * Funcion para definir la transformación de vista (posicionar la camara)
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}


/*****************************************************************************//**
 * Funcion que dibuja los objetos
 *
 *
 *
 *****************************************************************************/

void _gl_widget::draw_objects()
{
  Axis.draw_line();

  if (Draw_point){
    glPointSize(5);
    glColor3fv((GLfloat *) &BLACK);

    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_point();break;
    case OBJECT_CUBE:Cube.draw_point();break;
    case OBJECT_CONE:Cone.draw_point();break;
    case OBJECT_CYLINDER:Cylinder.draw_point();break;
    case OBJECT_SPHERE:Sphere.draw_point();break;
    case OBJECT_PLY:ObjectPLY.draw_point();break;
    case OBJECT_DASHBOARD:Dashboard.draw_point();break;
    case OBJECT_PLY_REV:ObjectPLYrev.draw_point();break;
    case OBJECT_MULTIPLE_PLY:
        for (int i = 0; i < 6; i++) {
            float angle = (i / 6.0) * 2.0 * M_PI;
            float x = 10 * cos(angle);
            float y = 5.0;
            float z = 10 * sin(angle);

            glPushMatrix();
            glTranslatef(x, y, z);
            ObjectPLY.draw_point();
            glPopMatrix();
        };
        break;
    default:break;
    }
  }

  if (Draw_line){
    glLineWidth(3);
    glColor3fv((GLfloat *) &MAGENTA);

    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_line();break;
    case OBJECT_CUBE:Cube.draw_line();break;
    case OBJECT_CONE:Cone.draw_line();break;
    case OBJECT_CYLINDER:Cylinder.draw_line();break;
    case OBJECT_SPHERE:Sphere.draw_line();break;
    case OBJECT_PLY:ObjectPLY.draw_line();break;
    case OBJECT_DASHBOARD:Dashboard.draw_line();break;
    case OBJECT_PLY_REV:ObjectPLYrev.draw_line();break;
    case OBJECT_MULTIPLE_PLY:
        for (int i = 0; i < 6; i++) {
            float angle = (i / 6.0) * 2.0 * M_PI;
            float x = 10 * cos(angle);
            float y = 5.0;
            float z = 10 * sin(angle);

            glPushMatrix();
            glTranslatef(x, y, z);
            ObjectPLY.draw_line();
            glPopMatrix();
        };
        break;
    default:break;
    }
  }

  if (Draw_fill){
    glColor3fv((GLfloat *) &BLUE);

    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_fill();break;
    case OBJECT_CUBE:Cube.draw_fill();break;
    case OBJECT_CONE:Cone.draw_fill();break;
    case OBJECT_CYLINDER:Cylinder.draw_fill();break;
    case OBJECT_SPHERE:Sphere.draw_fill();break;
    case OBJECT_PLY:ObjectPLY.draw_fill();break;
    case OBJECT_DASHBOARD:Dashboard.draw_fill();break;
    case OBJECT_PLY_REV:ObjectPLYrev.draw_fill();break;
    case OBJECT_MULTIPLE_PLY:
        for (int i = 0; i < 6; i++) {
            float angle = (i / 6.0) * 2.0 * M_PI;
            float x = 10 * cos(angle);
            float y = 5.0;
            float z = 10 * sin(angle);

            glPushMatrix();
            glTranslatef(x, y, z);
            ObjectPLY.draw_fill();
            glPopMatrix();
        };
        break;
    default:break;
    }
  }

  if (Draw_chess){
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_chess();break;
    case OBJECT_CUBE:Cube.draw_chess();break;
    case OBJECT_CONE:Cone.draw_chess();break;
    case OBJECT_CYLINDER:Cylinder.draw_chess();break;
    case OBJECT_SPHERE:Sphere.draw_chess();break;
    case OBJECT_PLY:ObjectPLY.draw_chess();break;
    case OBJECT_DASHBOARD:Dashboard.draw_chess();break;
    case OBJECT_PLY_REV:ObjectPLYrev.draw_chess();break;
    case OBJECT_MULTIPLE_PLY:
        for (int i = 0; i < 6; i++) {
            float angle = (i / 6.0) * 2.0 * M_PI;
            float x = 10 * cos(angle);
            float y = 5.0;
            float z = 10 * sin(angle);

            glPushMatrix();
            glTranslatef(x, y, z);
            ObjectPLY.draw_chess();
            glPopMatrix();
        };
        break;
    default:break;
    }
  }

  if (Draw_random){
      switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron.draw_random();break;
      case OBJECT_CUBE:Cube.draw_random();break;
      case OBJECT_CONE:Cone.draw_random();break;
      case OBJECT_CYLINDER:Cylinder.draw_random();break;
      case OBJECT_SPHERE:Sphere.draw_random();break;
      case OBJECT_PLY:ObjectPLY.draw_random();break;
      case OBJECT_DASHBOARD:Dashboard.draw_random();break;
      case OBJECT_PLY_REV:ObjectPLYrev.draw_random();break;
      case OBJECT_MULTIPLE_PLY:
          for (int i = 0; i < 6; i++) {
              float angle = (i / 6.0) * 2.0 * M_PI;
              float x = 10 * cos(angle);
              float y = 5.0;
              float z = 10 * sin(angle);

              glPushMatrix();
              glTranslatef(x, y, z);
              ObjectPLY.draw_random();
              glPopMatrix();
          };
          break;
      default:break;
      }
  }

  if (Draw_flat){
      // enabling light 0 and 1
      light1 ? glEnable(GL_LIGHT0) : glDisable(GL_LIGHT0);
      light2 ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);

      white_infinite_light();
      magenta_non_infinite_light();

      change_material();

      switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron.draw_flat();break;
      case OBJECT_CUBE:Cube.draw_flat();break;
      case OBJECT_CONE:Cone.draw_flat();break;
      case OBJECT_CYLINDER:Cylinder.draw_flat();break;
      case OBJECT_SPHERE:Sphere.draw_flat();break;
      case OBJECT_PLY:ObjectPLY.draw_flat();break;
      case OBJECT_DASHBOARD:Dashboard.draw_flat();break;
      case OBJECT_PLY_REV:ObjectPLYrev.draw_flat();break;
      case OBJECT_STICK:Stick.draw();break;
      case OBJECT_MULTIPLE_PLY:
          for (int i = 0; i < 6; i++) {
              float angle = (i / 6.0) * 2.0 * M_PI;
              float x = 10 * cos(angle);
              float y = 5.0;
              float z = 10 * sin(angle);

              glPushMatrix();
              glTranslatef(x, y, z);
              ObjectPLY.draw_flat();
              glPopMatrix();
          };
          break;
      default:break;
      }
  }

  if (Draw_gouraud){
      // enabling light 0 and 1
      light1 ? glEnable(GL_LIGHT0) : glDisable(GL_LIGHT0);
      light2 ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);

      white_infinite_light();
      magenta_non_infinite_light();

      change_material();

      switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron.draw_gouraud();break;
      case OBJECT_CUBE:Cube.draw_gouraud();break;
      case OBJECT_CONE:Cone.draw_gouraud();break;
      case OBJECT_CYLINDER:Cylinder.draw_gouraud();break;
      case OBJECT_SPHERE:Sphere.draw_gouraud();break;
      case OBJECT_PLY:ObjectPLY.draw_gouraud();break;
      case OBJECT_DASHBOARD:Dashboard.draw_gouraud();break;
      case OBJECT_PLY_REV:ObjectPLYrev.draw_gouraud();break;
      case OBJECT_MULTIPLE_PLY:
          for (int i = 0; i < 6; i++) {
              float angle = (i / 6.0) * 2.0 * M_PI;
              float x = 10 * cos(angle);
              float y = 5.0;
              float z = 10 * sin(angle);

              glPushMatrix();
              glTranslatef(x, y, z);
              ObjectPLY.draw_gouraud();
              glPopMatrix();
          };
          break;
      default:break;
      }
  }

  if (Draw_tex){
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
      glColor3fv((GLfloat *) & WHITE);

      switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron.draw_texture();break;
      case OBJECT_CUBE:Cube.draw_texture();break;
      case OBJECT_CONE:Cone.draw_texture();break;
      case OBJECT_CYLINDER:Cylinder.draw_texture();break;
      case OBJECT_SPHERE:Sphere.draw_texture();break;
      case OBJECT_PLY:ObjectPLY.draw_texture();break;
      case OBJECT_DASHBOARD:Dashboard.draw_texture();break;
      case OBJECT_PLY_REV:ObjectPLYrev.draw_texture();break;
      case OBJECT_MULTIPLE_PLY:
          for (int i = 0; i < 6; i++) {
              float angle = (i / 6.0) * 2.0 * M_PI;
              float x = 10 * cos(angle);
              float y = 5.0;
              float z = 10 * sin(angle);

              glPushMatrix();
              glTranslatef(x, y, z);
              ObjectPLY.draw_texture();
              glPopMatrix();
          };
          break;
      default:break;
      }
  }

  if (Draw_tex_flat){
      // enabling light 0 and 1
      light1 ? glEnable(GL_LIGHT0) : glDisable(GL_LIGHT0);
      light2 ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);

      white_infinite_light();
      magenta_non_infinite_light();

      switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron.draw_texture_flat();break;
      case OBJECT_CUBE:Cube.draw_texture_flat();break;
      case OBJECT_CONE:Cone.draw_texture_flat();break;
      case OBJECT_CYLINDER:Cylinder.draw_texture_flat();break;
      case OBJECT_SPHERE:Sphere.draw_texture_flat();break;
      case OBJECT_PLY:ObjectPLY.draw_texture_flat();break;
      case OBJECT_DASHBOARD:Dashboard.draw_texture_flat();break;
      case OBJECT_PLY_REV:ObjectPLYrev.draw_texture_flat();break;
      case OBJECT_MULTIPLE_PLY:
          for (int i = 0; i < 6; i++) {
              float angle = (i / 6.0) * 2.0 * M_PI;
              float x = 10 * cos(angle);
              float y = 5.0;
              float z = 10 * sin(angle);

              glPushMatrix();
              glTranslatef(x, y, z);
              ObjectPLY.draw_texture_flat();
              glPopMatrix();
          };
          break;
      default:break;
      }
  }

  if (Draw_tex_gouraud){
      // enabling light 0 and 1
      light1 ? glEnable(GL_LIGHT0) : glDisable(GL_LIGHT0);
      light2 ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);

      white_infinite_light();
      magenta_non_infinite_light();

      switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron.draw_texture_gouraud();break;
      case OBJECT_CUBE:Cube.draw_texture_gouraud();break;
      case OBJECT_CONE:Cone.draw_texture_gouraud();break;
      case OBJECT_CYLINDER:Cylinder.draw_texture_gouraud();break;
      case OBJECT_SPHERE:Sphere.draw_texture_gouraud();break;
      case OBJECT_PLY:ObjectPLY.draw_texture_gouraud();break;
      case OBJECT_DASHBOARD:Dashboard.draw_texture_gouraud();break;
      case OBJECT_PLY_REV:ObjectPLYrev.draw_texture_gouraud();break;
      case OBJECT_MULTIPLE_PLY:
          for (int i = 0; i < 6; i++) {
              float angle = (i / 6.0) * 2.0 * M_PI;
              float x = 10 * cos(angle);
              float y = 5.0;
              float z = 10 * sin(angle);

              glPushMatrix();
              glTranslatef(x, y, z);
              ObjectPLY.draw_texture_gouraud();
              glPopMatrix();
          };
          break;
      default:break;
      }
  }

  if (Draw_selection){
      switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron.draw_selection();break;
      case OBJECT_CUBE:Cube.draw_selection();break;
      case OBJECT_CONE:Cone.draw_selection();break;
      case OBJECT_CYLINDER:Cylinder.draw_selection();break;
      case OBJECT_SPHERE:Sphere.draw_selection();break;
      case OBJECT_PLY:ObjectPLY.draw_selection();break;
      case OBJECT_DASHBOARD:Dashboard.draw_selection();break;
      case OBJECT_PLY_REV:ObjectPLYrev.draw_selection();break;
      case OBJECT_MULTIPLE_PLY:
          for (int i = 0; i < 6; i++) {
              float angle = (i / 6.0) * 2.0 * M_PI;
              float x = 10 * cos(angle);
              float y = 5.0;
              float z = 10 * sin(angle);

              glPushMatrix();
              glTranslatef(x, y, z);
              ObjectPLY.draw_selection();
              glPopMatrix();
          };
          break;
      default:break;
      }
  }
}

/*****************************************************************************//**
 * Evento de dibujado
 *
 *
 *
 *****************************************************************************/

void _gl_widget::paintGL()
{
  clear_window();
  change_projection();
  updateMagentaLight();
  change_observer();
  draw_objects();
}


/*****************************************************************************//**
 * Evento de cambio de tamaño de la ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::resizeGL(int Width1, int Height1)
{
  glViewport(0,0,Width1,Height1);
}

/*****************************************************************************//**
 * Funcion para poner luz blanca en el infinito
 *
 *
 *
 *****************************************************************************/

void _gl_widget :: white_infinite_light(){
    // components of light (ambient, diffuse, specular)
    const GLfloat ambient_light[]  = {0.2f, 0.2f, 0.2f, 0.0f}; // Soft ambient light
    const GLfloat diffuse_light[]  = {0.8f, 0.8f, 0.8f, 0.0f}; // Strong white diffuse light
    const GLfloat specular_light[] = {1.0f, 1.0f, 1.0f, 0.0f}; // Shiny specular reflection

    // light position (depends on current draw mode)
    const GLfloat *light_pos = (Draw_tex_flat || Draw_tex_gouraud) ? INFINITE_LIGHT2_POS : INFINITE_LIGHT_POS;

    // setting ambient, diffuse & specular components
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

    // set position of light
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

/*****************************************************************************//**
 * Funcion para poner luz megenta no en el infinito
 *
 *
 *
 *****************************************************************************/

void _gl_widget :: magenta_non_infinite_light(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    // components of light (ambient, diffuse, specular)
    const GLfloat ambient_light[]  = {0.2f, 0.2f, 0.2f, 1.0f}; // Soft magenta ambient light
    const GLfloat diffuse_light[]  = {0.6f, 0.2f, 0.8f, 1.0f}; // Strong magenta diffuse light
    const GLfloat specular_light[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Magenta specular highlight

    // position of light in 3D space (last component 1.0 means "positional light")
    const GLfloat light_pos[] = {2.0f, 5.0f, 3.0f, 1.0f};

    // setting ambient, diffuse & specular components
    glLightfv(GL_LIGHT1, GL_AMBIENT,  ambient_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  diffuse_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);

    glRotatef(light_rotation,0,1,0);
    // set position of light
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
    glPopMatrix();
}

/*****************************************************************************//**
 * Funcion para poner cambiar entre 3 materiales (PERLA, ESMERALDA, RUBI)
 *
 *
 *
 *****************************************************************************/

void _gl_widget :: change_material(){
    // PEARL MATERIAL
    const _vertex4f AMBIENT_PEARL(0.25, 0.20725, 0.20725, 0.922);
    const _vertex4f DIFFUSE_PEARL(1, 0.829, 0.829, 0.922);
    const _vertex4f SPECULAR_PEARL(0.296648, 0.296648, 0.296648, 0.922);
    const float PEARL_SHININESS = 11.264;
    // JADE MATERIAL
    const _vertex4f AMBIENT_JADE(0.135f, 0.2225f, 0.1575f, 0.95f);
    const _vertex4f DIFFUSE_JADE(0.54f, 0.89f, 0.63f, 0.95f);
    const _vertex4f SPECULAR_JADE(0.316228f, 0.316228f, 0.316228f, 0.95f);
    const float JADE_SHININESS = 12.8f;
    // RUBY MATERIAL
    const _vertex4f AMBIENT_RUBY(0.1745, 0.01175, 0.01175, 0.55);
    const _vertex4f DIFFUSE_RUBY(0.61424, 0.04136, 0.04136, 0.55);
    const _vertex4f SPECULAR_RUBY(0.727811, 0.626959, 0.626959, 0.55);
    const float RUBY_SHININESS = 76.8;

    switch(material_type){
    case 0:
        glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *) & AMBIENT_PEARL);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *) & DIFFUSE_PEARL);
        glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) & SPECULAR_PEARL);
        glMaterialf(GL_FRONT, GL_SHININESS, PEARL_SHININESS);
        break;
    case 1:
        glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *) & AMBIENT_JADE);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *) & DIFFUSE_JADE);
        glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) & SPECULAR_JADE);
        glMaterialf(GL_FRONT, GL_SHININESS, JADE_SHININESS);
        break;
    case 2:
        glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *) & AMBIENT_RUBY);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *) & DIFFUSE_RUBY);
        glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) & SPECULAR_RUBY);
        glMaterialf(GL_FRONT, GL_SHININESS, RUBY_SHININESS);
        break;
    }
}

/*****************************************************************************//**
 * Funcion para el calculo de normales a traves de la funcion del objeto3d
 *
 *
 *
 *****************************************************************************/

void _gl_widget :: normal_calculation() {
    Tetrahedron.normal_calculation();
    Cube.normal_calculation();
    Cone.normal_calculation();
    Cylinder.normal_calculation();
    Sphere.normal_calculation();
    ObjectPLY.normal_calculation();
    ObjectPLYrev.normal_calculation();
    Dashboard.normal_calculation();
    Stick.normal_calculation();
}

/*****************************************************************************//**
 * Funcion para cargar la textura
 *
 *
 *
 *****************************************************************************/
void _gl_widget :: load_texture(QString & file)
{
    string filePath = file.toStdString();
    GLuint textureID = texture_manager :: loadTexture(filePath);

    if (textureID == 0) {
        QMessageBox::warning(this, "Texture Error", "Failed to load texture.");
    } else {
        std::cout << "Texture loaded with ID: " << textureID << std::endl;
    }
}

/*****************************************************************************//**
 * Funcion para resaltar en amarillo el triangulo seleccionado
 *
 *
 *
 *****************************************************************************/
void _gl_widget :: pick()
{
    makeCurrent();

    // Framebuffer Object setup
    GLuint FBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    // Color texture
    GLuint Color_texture;
    glGenTextures(1, &Color_texture);
    glBindTexture(GL_TEXTURE_2D, Color_texture);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, window_width, window_height);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Depth texture
    GLuint Depth_texture;
    glGenTextures(1, &Depth_texture);
    glBindTexture(GL_TEXTURE_2D, Depth_texture);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, window_width, window_height);

    // Attach textures to FB0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, Color_texture, 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, Depth_texture, 0);

    static const GLenum Draw_buffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, Draw_buffers);

    // Draw the scene for selection
    clear_window();
    change_projection();
    change_observer();

    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_selection();break;
    case OBJECT_CUBE:Cube.draw_selection();break;
    case OBJECT_CONE:Cone.draw_selection();break;
    case OBJECT_CYLINDER:Cylinder.draw_selection();break;
    case OBJECT_SPHERE:Sphere.draw_selection();break;
    case OBJECT_PLY:ObjectPLY.draw_selection();break;
    case OBJECT_DASHBOARD:Dashboard.draw_selection();break;
    case OBJECT_PLY_REV:ObjectPLYrev.draw_selection();break;
    case OBJECT_MULTIPLE_PLY:
        for (int i = 0; i < 6; i++) {
            float angle = (i / 6.0) * 2.0 * M_PI;
            float x = 10 * cos(angle);
            float y = 5.0;
            float z = 10 * sin(angle);

            glPushMatrix();
            glTranslatef(x, y, z);
            ObjectPLY.draw_selection();
            glPopMatrix();
        };
        break;
    default:break;
    }

    // Read pixel from selection position
    unsigned char pixel[4];
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glReadPixels(current_selection_pos_x, current_selection_pos_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

    // Decode color to triangleID
    int selected_id = (pixel[0] << 16 ) | (pixel[1] << 8) | pixel[2];

    // Set selected triangle in object
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.update_selected_triangle(selected_id);break;
    case OBJECT_CUBE:Cube.update_selected_triangle(selected_id);break;
    case OBJECT_CONE:Cone.update_selected_triangle(selected_id);break;
    case OBJECT_CYLINDER:Cylinder.update_selected_triangle(selected_id);break;
    case OBJECT_SPHERE:Sphere.update_selected_triangle(selected_id);break;
    case OBJECT_PLY:ObjectPLY.update_selected_triangle(selected_id);break;
    case OBJECT_DASHBOARD:Dashboard.update_selected_triangle(selected_id);break;
    case OBJECT_PLY_REV:Dashboard.update_selected_triangle(selected_id);break;
    case OBJECT_MULTIPLE_PLY:
        for (int i = 0; i < 6; i++) {
            float angle = (i / 6.0) * 2.0 * M_PI;
            float x = 10 * cos(angle);
            float y = 5.0;
            float z = 10 * sin(angle);

            glPushMatrix();
            glTranslatef(x, y, z);
            ObjectPLY.update_selected_triangle(selected_id);
            glPopMatrix();
        };
        break;
    default:break;
    }

    // Cleanup
    glDeleteTextures(1, &Color_texture);
    glDeleteTextures(1, &Depth_texture);
    glDeleteFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
}

/*****************************************************************************//**
 * Funcion para manejar el evento click derecho del raton
 *
 *
 *
 *****************************************************************************/
void _gl_widget :: mousePressEvent(QMouseEvent *Mouseevent)
{
    if (Mouseevent->button() == Qt::RightButton){
        current_selection_pos_x = Mouseevent->pos().x();
        current_selection_pos_y = height() - Mouseevent->pos().y();
        Draw_fill = true;
    }
}

void _gl_widget :: mouseReleaseEvent(QMouseEvent *Mouseevent)
{
    if (Mouseevent->button() == Qt::RightButton){
        pick();
        update();
    }
}

/*****************************************************************************//**
 * Funcion para cambiar angulos en funcion del movimiento del raton
 *
 *
 *
 *****************************************************************************/
void _gl_widget :: mouseMoveEvent(QMouseEvent *Mouseevent)
{
    // get current x and y coordinates of the mouse pointer
    int new_x = Mouseevent->x();
    int new_y = Mouseevent->y();

    // check if the left mouse button is being pressed
    if (Mouseevent->buttons() & Qt::LeftButton)
    {
        // adjust the observer's angle on the y-axis based on horizontal movement
        if (last_x < new_x)      Observer_angle_y += MOUSE_STEP;
        else if (last_x > new_x) Observer_angle_y -= MOUSE_STEP;
        // adjust the observer's angle on the x-axis based on vertical movement
        if (last_y < new_y)      Observer_angle_x += MOUSE_STEP;
        else if (last_y > new_y) Observer_angle_x -= MOUSE_STEP;

        // update the last known mouse position to the current position
        last_x = new_x;
        last_y = new_y;
    }

    update();
}

/*****************************************************************************//**
 * Funcion para hacer zoom con la rueda del raton
 *
 *
 *
 *****************************************************************************/
void _gl_widget :: wheelEvent(QWheelEvent *Wheelevent)
{
    // get the angle change of the mouse wheel, in pixels, as a QPoint
    QPoint ptr = Wheelevent->angleDelta();
    // extract the vertical component of the wheel delta (y-axis movement)
    int y_pos = ptr.ry();

    // check if there was a non-zero movement (wheel was rotated)
    if (!ptr.isNull())
    {
        // if was rotated upwards (positive delta), zoom in (decrease distance)
        if (y_pos > 0)      Observer_distance /= CAMERA_FACTOR;
        // if was rotated downwards (negative delta), zoom out (increase distance)
        else if (y_pos < 0) Observer_distance *= CAMERA_FACTOR;
    }

    // mark the wheel event as handled
    Wheelevent->accept();
    // request an update to the widget to reflect the new zoom level
    update();
}

/*****************************************************************************//**
 * Funcion para la animacion del modelo jerarquico
 *
 *
 *
 *****************************************************************************/
void _gl_widget :: stick_animation(){
    timer_time++;
    Stick.updateBallPos();
    Stick.update();
    update();
}

/*****************************************************************************//**
 * Funcion para la animacion de la luz magenta
 *
 *
 *
 *****************************************************************************/
void _gl_widget :: updateMagentaLight()
{
    light_rotation += 2.0f;
    update();
}

/*****************************************************************************//**
 * Inicialización de OpenGL
 *
 *
 *
 *****************************************************************************/

void _gl_widget::initializeGL()
{
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";

  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";

  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
  }

  if (!glewInit()) {
      QMessageBox MsgBox(this);
      MsgBox.setText("Error: There is not OpenGL drivers\n\nPlease,\
        look for the information of your GPU\
        (AMD, INTEL or NVIDIA) and install the drivers");
          MsgBox.exec();
      Window->close();
  }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";

  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);

  Projection = _gl_widget_ne::PERSPECTIVE_PROJECTION;
  normal_calculation();

  Observer_angle_x=0;
  Observer_angle_y=0;
  Observer_distance=DEFAULT_DISTANCE;

  Draw_point=false;
  Draw_line=true;
  Draw_fill=false;
  Draw_chess=false;
  Draw_random=false;

  Draw_flat = false;
  Draw_gouraud = false;
  Draw_tex = false;
  Draw_tex_flat = false;
  Draw_tex_gouraud = false;

  Draw_selection = false;

  animation = false;

  Timer = new QTimer(this);
  Timer->setInterval(40);
  // animacion del modelo jerarquico
  connect(Timer, SIGNAL(timeout()), this, SLOT(stick_animation()));

  light1 = false;
  light2 = false;
  light_rotation = 0;

  material_type = 0;
  timer_time = 1;

  file = new QString("./chess_board.jpg");
  image = new QImage();

  load_texture(*file);

  window_height = height();
  window_width = width();

  last_x = 0;
  last_y = 0;
}
