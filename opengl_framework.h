#ifndef OPENGL_FRAMEWORK_H
#define OPENGL_FRAMEWORK_H

#include <SOIL.h>

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>

#include <QKeyEvent>
#include <QResource>

#include <glm/glm.hpp>

#include "kamera_loader.h"
#include "shader_loader.h"
#include "obiekt_loader.h"
#include "model_loader.h"

struct pozycja{
    GLfloat _x, _y, _z;
    GLfloat _ro, _pi, _ya;
};

class opengl_framework : public QOpenGLWidget, protected QOpenGLExtraFunctions{
  public:
    opengl_framework(QWidget *parent);

    std::vector<pozycja> _wektor_pozycji;
    int _aktualna_klatka;

    void wyczysc_bufory();
    void zmien_kolor_tla(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

  protected:
    void keyPressEvent(QKeyEvent *key);
    void initializeGL();
    void paintGL();
    virtual void inicjalizuj_opengl_framework();
    virtual void renderuj();

  private:
    shader_loader *_shader;
    kamera_loader *_kamera;

    model_loader *_scena_model;
    model_loader *_dron_model;
    model_loader *_budynek_model;

    GLfloat _kolor_tla[4];
};

#endif // OPENGL_FRAMEWORK_H
