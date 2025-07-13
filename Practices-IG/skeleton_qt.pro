DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x050F00

HEADERS += \
    PLY_revolution.h \
    build_revolution.h \
    chess_board.h \
  colors.h \
  basic_object3d.h \
    cone.h \
    cube.h \
    cylinder.h \
    file_ply_stl.h \
  object3d.h \
  axis.h \
    objectPLY.h \
    sphere.h \
    stick.h \
    stick_arm.h \
    stick_finger.h \
    stick_grabber.h \
    stick_hand.h \
    stick_handle.h \
  tetrahedron.h \
#  cube.h \
  glwidget.h \
    texture_manager.h \
  window.h

SOURCES += \
    PLY_revolution.cpp \
  basic_object3d.cc \
    build_revolution.cc \
    chess_board.cpp \
    cone.cc \
    cube.cc \
    cylinder.cc \
    file_ply_stl.cc \
  object3d.cc \
  axis.cc \
    objectPLY.cc \
    sphere.cc \
    stick.cpp \
    stick_arm.cpp \
    stick_finger.cpp \
    stick_grabber.cpp \
    stick_hand.cpp \
    stick_handle.cpp \
  tetrahedron.cc \
#  cube.cc \
  main.cc \
  glwidget.cc \
    texture_manager.cpp \
  window.cc


LIBS += -L/usr/X11R6/lib64 -lGLEW -lGL
INCLUDEPATH += /usr/include/GL

CONFIG += c++14
QT += widgets opengl openglwidgets
