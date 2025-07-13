/**
 * file: texture_manager.h
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 12/2024
 */

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <unordered_map>
#include <string>
#include <GL/gl.h>
#include <QImage>
#include <QImageReader>
#include <QMessageBox>
#include <QGuiApplication>

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class texture_manager
{
public:
    texture_manager();
    static GLuint loadTexture(const std::string& file);
    static GLuint getTextureID(const std::string& file);
private:
    static std::unordered_map<std::string, GLuint> textures; // Map from file name to texture ID
};

#endif // TEXTURE_MANAGER_H
