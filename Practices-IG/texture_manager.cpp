/**
 * file: texture_manager.cc
 * Copyright Mabilia Stella Rinelli Padrón
 * email: mabilia@correo.ugr.es
 * 12/2024
 */

#include "texture_manager.h"

using namespace std;

unordered_map<std::string, GLuint> texture_manager::textures;

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

texture_manager :: texture_manager() {}

/*****************************************************************************//**
 *
 * LOAD TEXTURE
 *
 *****************************************************************************/

GLuint texture_manager :: loadTexture(const string & file)
{
    if (textures.find(file) != textures.end()) {
        return textures[file];  // Return existing texture ID
    }

    QImage image;
    QImageReader reader(QString::fromStdString(file));
    reader.setAutoTransform(true);
    image = reader.read();

    if (image.isNull()) {
        QMessageBox::information(nullptr, QGuiApplication::applicationDisplayName(),
                                 QString("Cannot load %1").arg(QString::fromStdString(file)));
        return 0;
    }

    image = image.mirrored();
    image = image.convertToFormat(QImage::Format_RGB888);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.bits());

    glBindTexture(GL_TEXTURE_2D, 0);

    textures[file] = textureID;  // Store the texture ID
    return textureID;
}


/*****************************************************************************//**
 *
 * GETTER -> TextureID
 *
 *****************************************************************************/

GLuint texture_manager :: getTextureID(const std::string& file)
{
    if (textures.find(file) != textures.end()) {
        return textures[file];
    }
    return 0;  // Texture not found
}
